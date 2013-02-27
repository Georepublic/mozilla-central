/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/SVGGlobalCoordinateSystemElement.h"

#include "DOMSVGAnimatedTransformList.h"
#include "mozilla/dom/SVGGlobalCoordinateSystemElementBinding.h"
#include "mozilla/Util.h"
#include "nsCOMPtr.h"
#include "nsGkAtoms.h"
#include "nsIURI.h"
#include "nsIDOMSVGURIReference.h"
#include "nsSVGElement.h"

NS_IMPL_NS_NEW_NAMESPACED_SVG_ELEMENT(GlobalCoordinateSystem)

namespace mozilla {
namespace dom {

//--------------- GlobalCoordinateSystem ------------------

JSObject*
SVGGlobalCoordinateSystemElement::WrapNode(JSContext *aCx, JSObject *aScope, bool *aTriedToWrap)
{
  return SVGGlobalCoordinateSystemElementBinding::Wrap(aCx, aScope, this, aTriedToWrap);
}

nsSVGElement::StringInfo SVGGlobalCoordinateSystemElement::sStringInfo[1] =
{
  { &nsGkAtoms::href, kNameSpaceID_XLink, true }
};

//----------------------------------------------------------------------
// nsISupports methods

NS_IMPL_ISUPPORTS_INHERITED4(SVGGlobalCoordinateSystemElement, SVGGlobalCoordinateSystemElementBase,
                             nsIDOMNode, nsIDOMElement,
                             nsIDOMSVGElement,
                             nsIDOMSVGURIReference)
  
//----------------------------------------------------------------------
// Implementation

SVGGlobalCoordinateSystemElement::SVGGlobalCoordinateSystemElement(already_AddRefed<nsINodeInfo> aNodeInfo)
  : SVGGlobalCoordinateSystemElementBase(aNodeInfo)
{
	SetIsDOMBinding();
}

//----------------------------------------------------------------------
// nsIDOMNode methods

NS_IMPL_ELEMENT_CLONE_WITH_INIT(SVGGlobalCoordinateSystemElement)

//----------------------------------------------------------------------
// nsSVGElement methods

nsSVGElement::StringAttributesInfo
SVGGlobalCoordinateSystemElement::GetStringInfo()
{
  return StringAttributesInfo(mStringAttributes, sStringInfo,
                              ArrayLength(sStringInfo));
}

SVGAnimatedTransformList*
SVGGlobalCoordinateSystemElement::GetAnimatedTransformList(uint32_t aFlags)
{
  if (!mTransform && (aFlags & DO_ALLOCATE)) {
    mTransform = new SVGAnimatedTransformList();
  }
  return mTransform;
}

//----------------------------------------------------------------------

/* readonly attribute SVGAnimatedTransformList transform; */
already_AddRefed<DOMSVGAnimatedTransformList>
SVGGlobalCoordinateSystemElement::Transform()
{
  // We're creating a DOM wrapper, so we must tell GetAnimatedTransformList
  // to allocate the SVGAnimatedTransformList if it hasn't already done so:
  return DOMSVGAnimatedTransformList::GetDOMWrapper(
           GetAnimatedTransformList(DO_ALLOCATE), this);
}

//----------------------------------------------------------------------
// nsIDOMSVGURIReference methods:

/* readonly attribute nsIDOMSVGAnimatedString href; */
already_AddRefed<nsIDOMSVGAnimatedString>
SVGGlobalCoordinateSystemElement::Href()
{
  nsCOMPtr<nsIDOMSVGAnimatedString> href;
  mStringAttributes[HREF].ToDOMAnimatedString(getter_AddRefs(href), this);
  return href.forget();
}

NS_IMETHODIMP
SVGGlobalCoordinateSystemElement::GetHref(nsIDOMSVGAnimatedString * *aHref)
{
  *aHref = Href().get();
  return NS_OK;
}

} // namespace dom
} // namespace mozilla

