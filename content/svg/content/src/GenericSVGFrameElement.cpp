/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set tw=80 expandtab softtabstop=2 ts=2 sw=2: */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "nsSVGElement.h"
#include "GenericSVGFrameElement.h"
#include "nsIInterfaceRequestorUtils.h"
#include "nsContentUtils.h"
#include "mozilla/Preferences.h"
#include "nsIAppsService.h"
#include "nsServiceManagerUtils.h"
#include "nsIDOMApplicationRegistry.h"
#include "nsIPermissionManager.h"

using namespace mozilla;
using namespace mozilla::dom;

/*
NS_IMPL_CYCLE_COLLECTION_TRAVERSE_BEGIN_INHERITED(GenericSVGFrameElement,
                                                  nsSVGElement)
  NS_IMPL_CYCLE_COLLECTION_TRAVERSE(mFrameLoader)
NS_IMPL_CYCLE_COLLECTION_TRAVERSE_END

NS_INTERFACE_TABLE_HEAD(GenericSVGFrameElement)
  NS_INTERFACE_TABLE_INHERITED3(GenericSVGFrameElement,
                                nsIFrameLoaderOwner,
                                nsIDOMMozBrowserFrame,
                                nsIMozBrowserFrame)
  NS_INTERFACE_TABLE_TO_MAP_SEGUE_CYCLE_COLLECTION(GenericSVGFrameElement)
NS_INTERFACE_MAP_END_INHERITING(nsSVGElement)

NS_IMPL_BOOL_ATTR(GenericSVGFrameElement, Mozbrowser, mozbrowser)
*/
NS_IMPL_CYCLE_COLLECTION_TRAVERSE_BEGIN_INHERITED(GenericSVGFrameElement,
                                                  nsSVGElement)
  NS_IMPL_CYCLE_COLLECTION_TRAVERSE(mFrameLoader)
NS_IMPL_CYCLE_COLLECTION_TRAVERSE_END
NS_IMPL_ISUPPORTS_INHERITED1(GenericSVGFrameElement, GenericSVGFrameElementBase,
                             nsIFrameLoaderOwner)
                             //                             nsIDOMMozBrowserFrame,
                             //nsIMozBrowserFrame)
//NS_IMPL_BOOL_ATTR(GenericSVGFrameElement, Mozbrowser, mozbrowser)


//int32_t
//GenericSVGFrameElement::TabIndexDefault()
//{
//  return 0;
//}

GenericSVGFrameElement::~GenericSVGFrameElement()
{
  if (mFrameLoader) {
    mFrameLoader->Destroy();
  }
}

nsresult
GenericSVGFrameElement::GetContentDocument(nsIDOMDocument** aContentDocument)
{
  NS_PRECONDITION(aContentDocument, "Null out param");
  nsCOMPtr<nsIDOMDocument> document = do_QueryInterface(GetContentDocument());
  document.forget(aContentDocument);
  return NS_OK;
}

nsIDocument*
GenericSVGFrameElement::GetContentDocument()
{
  nsCOMPtr<nsPIDOMWindow> win = GetContentWindow();
  if (!win) {
    return nullptr;
  }

  return win->GetDoc();
}

nsresult
GenericSVGFrameElement::GetContentWindow(nsIDOMWindow** aContentWindow)
{
  NS_PRECONDITION(aContentWindow, "Null out param");
  nsCOMPtr<nsPIDOMWindow> window = GetContentWindow();
  window.forget(aContentWindow);
  return NS_OK;
}

already_AddRefed<nsPIDOMWindow>
GenericSVGFrameElement::GetContentWindow()
{
  EnsureFrameLoader();

  if (!mFrameLoader) {
    return nullptr;
  }

  bool depthTooGreat = false;
  mFrameLoader->GetDepthTooGreat(&depthTooGreat);
  if (depthTooGreat) {
    // Claim to have no contentWindow
    return nullptr;
  }

  nsCOMPtr<nsIDocShell> doc_shell;
  mFrameLoader->GetDocShell(getter_AddRefs(doc_shell));

  nsCOMPtr<nsPIDOMWindow> win = do_GetInterface(doc_shell);

  if (!win) {
    return nullptr;
  }

  NS_ASSERTION(win->IsOuterWindow(),
               "Uh, this window should always be an outer window!");

  return win.forget();
}

nsresult
GenericSVGFrameElement::EnsureFrameLoader()
{
  if (!GetParent())
    NS_WARNING("can't get Parent");
  if (!IsInDoc())
    NS_WARNING("is not doc");
  
  // if (!GetParent() || !IsInDoc() || mFrameLoader || mFrameLoaderCreationDisallowed) {
  if (mFrameLoader || mFrameLoaderCreationDisallowed) {
    // If frame loader is there, we just keep it around, cached
    return NS_OK;
  }

  mFrameLoader = nsFrameLoader::Create(this, mNetworkCreated);
  if (!mFrameLoader) {
    // Strangely enough, this method doesn't actually ensure that the
    // frameloader exists.  It's more of a best-effort kind of thing.
    return NS_OK;
  }

  return NS_OK;
}
/*
nsresult
GenericSVGFrameElement::CreateRemoteFrameLoader(nsITabParent* aTabParent)
{
  MOZ_ASSERT(!mFrameLoader);
  EnsureFrameLoader();
  NS_ENSURE_STATE(mFrameLoader);
  mFrameLoader->SetRemoteBrowser(aTabParent);
  return NS_OK;
}
*/
NS_IMETHODIMP
GenericSVGFrameElement::GetFrameLoader(nsIFrameLoader **aFrameLoader)
{
  NS_IF_ADDREF(*aFrameLoader = mFrameLoader);
  return NS_OK;
}

NS_IMETHODIMP_(already_AddRefed<nsFrameLoader>)
GenericSVGFrameElement::GetFrameLoader()
{
  nsRefPtr<nsFrameLoader> loader = mFrameLoader;
  return loader.forget();
}

NS_IMETHODIMP
GenericSVGFrameElement::SwapFrameLoaders(nsIFrameLoaderOwner* aOtherOwner)
{
  // We don't support this yet
  return NS_ERROR_NOT_IMPLEMENTED;
}

nsresult
GenericSVGFrameElement::LoadSrc()
{
  nsresult rv = EnsureFrameLoader();
  NS_ENSURE_SUCCESS(rv, rv);

  if (!mFrameLoader) {
    return NS_OK;
  }

  rv = mFrameLoader->LoadFrame();
#ifdef DEBUG
  if (NS_FAILED(rv)) {
    NS_WARNING("failed to load URL");
  }
#endif

  return rv;
}

nsresult
GenericSVGFrameElement::BindToTree(nsIDocument* aDocument,
                                      nsIContent* aParent,
                                      nsIContent* aBindingParent,
                                      bool aCompileEventHandlers)
{
  nsresult rv = nsSVGElement::BindToTree(aDocument, aParent,
                                                 aBindingParent,
                                                 aCompileEventHandlers);
  NS_ENSURE_SUCCESS(rv, rv);

  if (aDocument) {
    NS_ASSERTION(!nsContentUtils::IsSafeToRunScript(),
                 "Missing a script blocker!");
    // We're in a document now.  Kick off the frame load.
    LoadSrc();
  }

  // We're now in document and scripts may move us, so clear
  // the mNetworkCreated flag.
  mNetworkCreated = false;
  return rv;
}

void
GenericSVGFrameElement::UnbindFromTree(bool aDeep, bool aNullParent)
{
  if (mFrameLoader) {
    // This iframe is being taken out of the document, destroy the
    // iframe's frame loader (doing that will tear down the window in
    // this iframe).
    // XXXbz we really want to only partially destroy the frame
    // loader... we don't want to tear down the docshell.  Food for
    // later bug.
    mFrameLoader->Destroy();
    mFrameLoader = nullptr;
  }

  nsSVGElement::UnbindFromTree(aDeep, aNullParent);
}

nsresult
GenericSVGFrameElement::SetAttr(int32_t aNameSpaceID, nsIAtom* aName,
                                   nsIAtom* aPrefix, const nsAString& aValue,
                                   bool aNotify)
{
  nsresult rv = nsSVGElement::SetAttr(aNameSpaceID, aName, aPrefix,
                                              aValue, aNotify);
  NS_ENSURE_SUCCESS(rv, rv);

  if (aNameSpaceID == kNameSpaceID_None && aName == nsGkAtoms::src) {
    // Don't propagate error here. The attribute was successfully set, that's
    // what we should reflect.
    LoadSrc();
  }

  return NS_OK;
}

void
GenericSVGFrameElement::DestroyContent()
{
  if (mFrameLoader) {
    mFrameLoader->Destroy();
    mFrameLoader = nullptr;
  }

  nsSVGElement::DestroyContent();
}

nsresult
GenericSVGFrameElement::CopyInnerTo(Element* aDest)
{
  nsresult rv = nsSVGElement::CopyInnerTo(aDest);
  NS_ENSURE_SUCCESS(rv, rv);

  nsIDocument* doc = aDest->OwnerDoc();
  if (doc->IsStaticDocument() && mFrameLoader) {
    GenericSVGFrameElement* dest =
      static_cast<GenericSVGFrameElement*>(aDest);
    nsFrameLoader* fl = nsFrameLoader::Create(dest, false);
    NS_ENSURE_STATE(fl);
    dest->mFrameLoader = fl;
    static_cast<nsFrameLoader*>(mFrameLoader.get())->CreateStaticClone(fl);
  }

  return rv;
}

//bool
//GenericSVGFrameElement::IsHTMLFocusable(bool aWithMouse,
//                                           bool *aIsFocusable,
//                                           int32_t *aTabIndex)
//{
//  if (nsSVGElement::IsHTMLFocusable(aWithMouse, aIsFocusable, aTabIndex)) {
//    return true;
//  }
//
//  *aIsFocusable = nsContentUtils::IsSubDocumentTabbable(this);
//
//  if (!*aIsFocusable && aTabIndex) {
//    *aTabIndex = -1;
//  }
//
//  return false;
//}

/**
 * Return true if this frame element really is a mozbrowser or mozapp.  (It
 * needs to have the right attributes, and its creator must have the right
 * permissions.)
 */
/* [infallible] */
/*nsresult
GenericSVGFrameElement::GetReallyIsBrowserOrApp(bool *aOut)
{
  *aOut = false;

  // Fail if browser frames are globally disabled.
  //if (!Preferences::GetBool("dom.mozBrowserFramesEnabled")) {
  //  return NS_OK;
  //}

  // // Fail if this frame doesn't have the mozbrowser attribute.
  // bool hasMozbrowser = false;
  // GetMozbrowser(&hasMozbrowser);
  // if (!hasMozbrowser) {
  //   return NS_OK;
  // }

  // Fail if the node principal isn't trusted.
  nsIPrincipal *principal = NodePrincipal();
  nsCOMPtr<nsIPermissionManager> permMgr =
    do_GetService(NS_PERMISSIONMANAGER_CONTRACTID);
  NS_ENSURE_TRUE(permMgr, NS_OK);

  uint32_t permission = nsIPermissionManager::DENY_ACTION;
  nsresult rv = permMgr->TestPermissionFromPrincipal(principal, "browser", &permission);
  NS_ENSURE_SUCCESS(rv, NS_OK);
  *aOut = permission == nsIPermissionManager::ALLOW_ACTION;
  return NS_OK;
}
*/
/* [infallible] */
/* NS_IMETHODIMP
GenericSVGFrameElement::GetReallyIsApp(bool *aOut)
{
  nsAutoString manifestURL;
  GetAppManifestURL(manifestURL);

  *aOut = !manifestURL.IsEmpty();
  return NS_OK;
  }*/

/* [infallible] */
/*NS_IMETHODIMP
GenericSVGFrameElement::GetIsExpectingSystemMessage(bool *aOut)
{
  *aOut = false;

  if (!nsIMozBrowserFrame::GetReallyIsApp()) {
    return NS_OK;
  }

  *aOut = HasAttr(kNameSpaceID_None, nsGkAtoms::expectingSystemMessage);
  return NS_OK;
  }*/

/*
NS_IMETHODIMP
GenericSVGFrameElement::GetAppManifestURL(nsAString& aOut)
{
  aOut.Truncate();

  // At the moment, you can't be an app without being a browser.
  if (!nsIMozBrowserFrame::GetReallyIsBrowserOrApp()) {
    return NS_OK;
  }

  // Check permission.
  nsIPrincipal *principal = NodePrincipal();
  nsCOMPtr<nsIPermissionManager> permMgr =
    do_GetService(NS_PERMISSIONMANAGER_CONTRACTID);
  NS_ENSURE_TRUE(permMgr, NS_OK);

  uint32_t permission = nsIPermissionManager::DENY_ACTION;
  nsresult rv = permMgr->TestPermissionFromPrincipal(principal,
                                                     "embed-apps",
                                                     &permission);
  NS_ENSURE_SUCCESS(rv, NS_OK);
  if (permission != nsIPermissionManager::ALLOW_ACTION) {
    return NS_OK;
  }

  nsAutoString manifestURL;
  GetAttr(kNameSpaceID_None, nsGkAtoms::mozapp, manifestURL);
  if (manifestURL.IsEmpty()) {
    return NS_OK;
  }

  nsCOMPtr<nsIAppsService> appsService = do_GetService(APPS_SERVICE_CONTRACTID);
  NS_ENSURE_TRUE(appsService, NS_OK);

  nsCOMPtr<mozIDOMApplication> app;
  appsService->GetAppByManifestURL(manifestURL, getter_AddRefs(app));
  if (app) {
    aOut.Assign(manifestURL);
  }

  return NS_OK;
  }*/
/*
NS_IMETHODIMP
GenericSVGFrameElement::DisallowCreateFrameLoader()
{
  MOZ_ASSERT(!mFrameLoader);
  MOZ_ASSERT(!mFrameLoaderCreationDisallowed);
  mFrameLoaderCreationDisallowed = true;
  return NS_OK;
}

NS_IMETHODIMP
GenericSVGFrameElement::AllowCreateFrameLoader()
{
  MOZ_ASSERT(!mFrameLoader);
  MOZ_ASSERT(mFrameLoaderCreationDisallowed);
  mFrameLoaderCreationDisallowed = false;
  return NS_OK;
}
*/
