/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/Util.h"

#include "mozilla/dom/SVGIFrameElement.h"
#include "nsCOMPtr.h"
#include "nsGkAtoms.h"
#include "nsIDOMSVGDocument.h"
#include "mozilla/dom/SVGIFrameElementBinding.h"

//DOMCI_NODE_DATA(SVGIFrameElement, mozilla::dom::SVGIFrameElement)

NS_IMPL_NS_NEW_NAMESPACED_SVG_ELEMENT_CHECK_PARSER(IFrame)

namespace mozilla {
namespace dom {

JSObject*
SVGIFrameElement::WrapNode(JSContext *aCx, JSObject *aScope, bool *aTriedToWrap)
{
  return SVGIFrameElementBinding::Wrap(aCx, aScope, this, aTriedToWrap);
}

  
//--------------------- IFrame ------------------------

nsSVGElement::LengthInfo SVGIFrameElement::sLengthInfo[4] =
{
  { &nsGkAtoms::x, 0, nsIDOMSVGLength::SVG_LENGTHTYPE_NUMBER, SVGContentUtils::X },
  { &nsGkAtoms::y, 0, nsIDOMSVGLength::SVG_LENGTHTYPE_NUMBER, SVGContentUtils::Y },
  { &nsGkAtoms::width, 0, nsIDOMSVGLength::SVG_LENGTHTYPE_NUMBER, SVGContentUtils::X },
  { &nsGkAtoms::height, 0, nsIDOMSVGLength::SVG_LENGTHTYPE_NUMBER, SVGContentUtils::Y },
};

nsSVGElement::StringInfo SVGIFrameElement::sStringInfo[5] =
{
  { &nsGkAtoms::media, 0, true },
  { &nsGkAtoms::name, 0, true },
  { &nsGkAtoms::src, 0, true },
  { &nsGkAtoms::srcdoc, 0, true },
  { &nsGkAtoms::sandbox, 0, true },
};

//----------------------------------------------------------------------
// nsISupports methods

/*
NS_IMPL_ADDREF_INHERITED(SVGIFrameElement, nsSVGElement)
NS_IMPL_RELEASE_INHERITED(SVGIFrameElement, nsSVGElement)

NS_INTERFACE_TABLE_HEAD(SVGIFrameElement)
  NS_NODE_INTERFACE_TABLE4(SVGIFrameElement, nsIDOMNode, nsIDOMElement,
                           nsIDOMSVGElement,
						   nsIDOMGetSVGDocument)
  NS_DOM_INTERFACE_MAP_ENTRY_CLASSINFO(SVGIFrameElement)
NS_INTERFACE_MAP_END_INHERITING(SVGIFrameElementBase)
*/
/*
NS_IMPL_ADDREF_INHERITED(SVGIFrameElement, nsSVGElement)
NS_IMPL_RELEASE_INHERITED(SVGIFrameElement, nsSVGElement)
*/
NS_IMPL_ISUPPORTS_INHERITED3(SVGIFrameElement, SVGIFrameElementBase,
                             nsIDOMNode, nsIDOMElement,
                             nsIDOMSVGElement)

//----------------------------------------------------------------------
// Implementation

SVGIFrameElement::SVGIFrameElement(already_AddRefed<nsINodeInfo> aNodeInfo,
                                       FromParser aFromParser)
  : SVGIFrameElementBase(aNodeInfo, aFromParser)
{
	SetIsDOMBinding();
}

SVGIFrameElement::~SVGIFrameElement()
{
}

//----------------------------------------------------------------------
// nsIDOMNode methods

nsresult
SVGIFrameElement::Clone(nsINodeInfo *aNodeInfo, nsINode **aResult) const
{
  *aResult = nullptr;
  nsCOMPtr<nsINodeInfo> ni = aNodeInfo;
  SVGIFrameElement *it = new SVGIFrameElement(ni.forget(), NOT_FROM_PARSER);

  nsCOMPtr<nsINode> kungFuDeathGrip = it;
  nsresult rv1 = it->Init();
  nsresult rv2 = const_cast<SVGIFrameElement*>(this)->CopyInnerTo(it);
  if (NS_SUCCEEDED(rv1) && NS_SUCCEEDED(rv2)) {
    kungFuDeathGrip.swap(*aResult);
  }

  return NS_FAILED(rv1) ? rv1 : rv2;
}

//NS_IMPL_ELEMENT_CLONE_WITH_INIT(SVGIFrameElement)
  
//----------------------------------------------------------------------
// nsSVGElement methods

nsSVGElement::LengthAttributesInfo
SVGIFrameElement::GetLengthInfo()
{
  return LengthAttributesInfo(mLengthAttributes, sLengthInfo,
                              ArrayLength(sLengthInfo));
}

SVGAnimatedPreserveAspectRatio *
SVGIFrameElement::GetPreserveAspectRatio()
{
  return &mPreserveAspectRatio;
}

nsSVGElement::StringAttributesInfo
SVGIFrameElement::GetStringInfo()
{
  return StringAttributesInfo(mStringAttributes, sStringInfo,
                              ArrayLength(sStringInfo));
}

//----------------------------------------------------------------------
// nsIDOMSVGIFrameElement methods:

/* readonly attribute nsIDOMSVGAnimatedLength x; */
/*NS_IMETHODIMP SVGIFrameElement::GetX(nsIDOMSVGAnimatedLength * *aX)
{
  *aX = X().get();
  return NS_OK;
}*/

already_AddRefed<SVGAnimatedLength>
SVGIFrameElement::X()
{
  return mLengthAttributes[ATTR_X].ToDOMAnimatedLength(this);
}

/* readonly attribute nsIDOMSVGAnimatedLength y; */
/*NS_IMETHODIMP SVGIFrameElement::GetY(nsIDOMSVGAnimatedLength * *aY)
{
  *aY = Y().get();
  return NS_OK;
}*/

already_AddRefed<SVGAnimatedLength>
SVGIFrameElement::Y()
{
  return mLengthAttributes[ATTR_Y].ToDOMAnimatedLength(this);
}

/* readonly attribute nsIDOMSVGAnimatedLength width; */
/*NS_IMETHODIMP SVGIFrameElement::GetWidth(nsIDOMSVGAnimatedLength * *aWidth)
{
  *aWidth = Width().get();
  return NS_OK;
}*/

already_AddRefed<SVGAnimatedLength>
SVGIFrameElement::Width()
{
  return mLengthAttributes[ATTR_WIDTH].ToDOMAnimatedLength(this);
}

/* readonly attribute nsIDOMSVGAnimatedLength height; */
/*NS_IMETHODIMP SVGIFrameElement::GetHeight(nsIDOMSVGAnimatedLength * *aHeight)
{
  *aHeight = Height().get();
  return NS_OK;
}*/

already_AddRefed<SVGAnimatedLength>
SVGIFrameElement::Height()
{
  return mLengthAttributes[ATTR_HEIGHT].ToDOMAnimatedLength(this);
}

/* readonly attribute SVGPreserveAspectRatio preserveAspectRatio; */
/*NS_IMETHODIMP
SVGIFrameElement::GetPreserveAspectRatio(nsISupports
                                        **aPreserveAspectRatio)
{
  *aPreserveAspectRatio = PreserveAspectRatio().get();
  return NS_OK;
  }*/

already_AddRefed<DOMSVGAnimatedPreserveAspectRatio>
SVGIFrameElement::PreserveAspectRatio()
{
  nsRefPtr<DOMSVGAnimatedPreserveAspectRatio> ratio;
  mPreserveAspectRatio.ToDOMAnimatedPreserveAspectRatio(getter_AddRefs(ratio), this);
  return ratio.forget();
}

/* readonly attribute nsIDOMSVGAnimatedString media; */
/*NS_IMETHODIMP
SVGIFrameElement::GetMedia(nsIDOMSVGAnimatedString * *aMedia)
{
  *aMedia = Media().get();
  return NS_OK;
}*/

already_AddRefed<nsIDOMSVGAnimatedString>
SVGIFrameElement::Media()
{
  nsCOMPtr<nsIDOMSVGAnimatedString> media;
  mStringAttributes[MEDIA].ToDOMAnimatedString(getter_AddRefs(media), this);
  return media.forget();
}

/* readonly attribute nsIDOMSVGAnimatedString name; */
/*NS_IMETHODIMP
SVGIFrameElement::GetName(nsIDOMSVGAnimatedString * *aName)
{
  *aName = Name().get();
  return NS_OK;
}*/

already_AddRefed<nsIDOMSVGAnimatedString>
SVGIFrameElement::Name()
{
  nsCOMPtr<nsIDOMSVGAnimatedString> name;
  mStringAttributes[NAME].ToDOMAnimatedString(getter_AddRefs(name), this);
  return name.forget();
}

/* readonly attribute nsIDOMSVGAnimatedString src; */
/*NS_IMETHODIMP
SVGIFrameElement::GetSrc(nsIDOMSVGAnimatedString * *aSrc)
{
  *aSrc = Src().get();
  return NS_OK;
}*/

already_AddRefed<nsIDOMSVGAnimatedString>
SVGIFrameElement::Src()
{
  nsCOMPtr<nsIDOMSVGAnimatedString> src;
  mStringAttributes[SRC].ToDOMAnimatedString(getter_AddRefs(src), this);
  return src.forget();
}

/* readonly attribute nsIDOMSVGAnimatedString srcdoc; */
/*NS_IMETHODIMP
SVGIFrameElement::GetSrcdoc(nsIDOMSVGAnimatedString * *aSrcdoc)
{
  *aSrcdoc = Srcdoc().get();
  return NS_OK;
}*/

already_AddRefed<nsIDOMSVGAnimatedString>
SVGIFrameElement::Srcdoc()
{
  nsCOMPtr<nsIDOMSVGAnimatedString> srcdoc;
  mStringAttributes[SRCDOC].ToDOMAnimatedString(getter_AddRefs(srcdoc), this);
  return srcdoc.forget();
}

already_AddRefed<nsIDOMSVGAnimatedString>
SVGIFrameElement::Sandbox()
{
  nsCOMPtr<nsIDOMSVGAnimatedString> sandbox;
  mStringAttributes[SANDBOX].ToDOMAnimatedString(getter_AddRefs(sandbox), this);
  return sandbox.forget();
}

  
/* attribute DOMString sandbox; */
//NS_IMPL_STRING_ATTR(SVGIFrameElement, Sandbox, sandbox)

void
SVGIFrameElement::SetSandbox(const nsAString& aSandbox, ErrorResult& rv)
{
  rv = SetAttr(kNameSpaceID_None, nsGkAtoms::sandbox, aSandbox, true);
}

//void
//SVGIFrameElement::GetItemValueText(nsAString& aValue)
//{
//  GetSrc(aValue);
//}
//
//void
//SVGIFrameElement::SetItemValueText(const nsAString& aValue)
//{
//  SetSrc(aValue);
//}

/*
NS_IMETHODIMP
SVGIFrameElement::GetContentDocument(nsIDOMDocument** aContentDocument)
{
  return GenericSVGFrameElement::GetContentDocument(aContentDocument);
}

NS_IMETHODIMP
SVGIFrameElement::GetContentWindow(nsIDOMWindow** aContentWindow)
{
  return GenericSVGFrameElement::GetContentWindow(aContentWindow);
}
*/
NS_IMETHODIMP
SVGIFrameElement::GetSVGDocument(nsIDOMDocument **aResult)
{
  return SVGIFrameElementBase::GetContentDocument(aResult);
}

//bool
//SVGIFrameElement::ParseAttribute(int32_t aNamespaceID,
//                                    nsIAtom* aAttribute,
//                                    const nsAString& aValue,
//                                    nsAttrValue& aResult)
//{
//  if (aNamespaceID == kNameSpaceID_None) {
//    if (aAttribute == nsGkAtoms::marginwidth) {
//      return aResult.ParseSpecialIntValue(aValue);
//    }
//    if (aAttribute == nsGkAtoms::marginheight) {
//      return aResult.ParseSpecialIntValue(aValue);
//    }
//    if (aAttribute == nsGkAtoms::width) {
//      return aResult.ParseSpecialIntValue(aValue);
//    }
//    if (aAttribute == nsGkAtoms::height) {
//      return aResult.ParseSpecialIntValue(aValue);
//    }
//    if (aAttribute == nsGkAtoms::frameborder) {
//      return ParseFrameborderValue(aValue, aResult);
//    }
//    if (aAttribute == nsGkAtoms::scrolling) {
//      return ParseScrollingValue(aValue, aResult);
//    }
//    if (aAttribute == nsGkAtoms::align) {
//      return ParseAlignValue(aValue, aResult);
//    }
//  }
//
//  return nsGenericSVGFrameElement::ParseAttribute(aNamespaceID, aAttribute,
//                                                   aValue, aResult);
//}

//static void
//MapAttributesIntoRule(const nsMappedAttributes* aAttributes,
//                      nsRuleData* aData)
//{
//  if (aData->mSIDs & NS_STYLE_INHERIT_BIT(Border)) {
//    // frameborder: 0 | 1 (| NO | YES in quirks mode)
//    // If frameborder is 0 or No, set border to 0
//    // else leave it as the value set in html.css
//    const nsAttrValue* value = aAttributes->GetAttr(nsGkAtoms::frameborder);
//    if (value && value->Type() == nsAttrValue::eEnum) {
//      int32_t frameborder = value->GetEnumValue();
//      if (NS_STYLE_FRAME_0 == frameborder ||
//          NS_STYLE_FRAME_NO == frameborder ||
//          NS_STYLE_FRAME_OFF == frameborder) {
//        nsCSSValue* borderLeftWidth = aData->ValueForBorderLeftWidthValue();
//        if (borderLeftWidth->GetUnit() == eCSSUnit_Null)
//          borderLeftWidth->SetFloatValue(0.0f, eCSSUnit_Pixel);
//        nsCSSValue* borderRightWidth = aData->ValueForBorderRightWidthValue();
//        if (borderRightWidth->GetUnit() == eCSSUnit_Null)
//          borderRightWidth->SetFloatValue(0.0f, eCSSUnit_Pixel);
//        nsCSSValue* borderTopWidth = aData->ValueForBorderTopWidth();
//        if (borderTopWidth->GetUnit() == eCSSUnit_Null)
//          borderTopWidth->SetFloatValue(0.0f, eCSSUnit_Pixel);
//        nsCSSValue* borderBottomWidth = aData->ValueForBorderBottomWidth();
//        if (borderBottomWidth->GetUnit() == eCSSUnit_Null)
//          borderBottomWidth->SetFloatValue(0.0f, eCSSUnit_Pixel);
//      }
//    }
//  }
//  if (aData->mSIDs & NS_STYLE_INHERIT_BIT(Position)) {
//    // width: value
//    nsCSSValue* width = aData->ValueForWidth();
//    if (width->GetUnit() == eCSSUnit_Null) {
//      const nsAttrValue* value = aAttributes->GetAttr(nsGkAtoms::width);
//      if (value && value->Type() == nsAttrValue::eInteger)
//        width->SetFloatValue((float)value->GetIntegerValue(), eCSSUnit_Pixel);
//      else if (value && value->Type() == nsAttrValue::ePercent)
//        width->SetPercentValue(value->GetPercentValue());
//    }
//
//    // height: value
//    nsCSSValue* height = aData->ValueForHeight();
//    if (height->GetUnit() == eCSSUnit_Null) {
//      const nsAttrValue* value = aAttributes->GetAttr(nsGkAtoms::height);
//      if (value && value->Type() == nsAttrValue::eInteger)
//        height->SetFloatValue((float)value->GetIntegerValue(), eCSSUnit_Pixel);
//      else if (value && value->Type() == nsAttrValue::ePercent)
//        height->SetPercentValue(value->GetPercentValue());
//    }
//  }
//
//  nsSVGElement::MapScrollingAttributeInto(aAttributes, aData);
//  nsSVGElement::MapImageAlignAttributeInto(aAttributes, aData);
//  nsSVGElement::MapCommonAttributesInto(aAttributes, aData);
//}
//
//NS_IMETHODIMP_(bool)
//SVGIFrameElement::IsAttributeMapped(const nsIAtom* aAttribute) const
//{
//  static const MappedAttributeEntry attributes[] = {
//    { &nsGkAtoms::width },
//    { &nsGkAtoms::height },
//    { &nsGkAtoms::frameborder },
//    { nullptr },
//  };
//
//  static const MappedAttributeEntry* const map[] = {
//    attributes,
//    sScrollingAttributeMap,
//    sImageAlignAttributeMap,
//    sCommonAttributeMap,
//  };
//  
//  return FindAttributeDependence(aAttribute, map);
//}



//nsMapRuleToAttributesFunc
//SVGIFrameElement::GetAttributeMappingFunction() const
//{
//  return &MapAttributesIntoRule;
//}

//nsresult
//nsSVGIFrameElement::AfterSetAttr(int32_t aNameSpaceID, nsIAtom* aName,
//                                  const nsAttrValue* aValue,
//                                  bool aNotify)
//{
//  if (aName == nsGkAtoms::sandbox && aNameSpaceID == kNameSpaceID_None) {
//    // Parse the new value of the sandbox attribute, and if we have a docshell
//    // set its sandbox flags appropriately.
//    if (mFrameLoader) {
//      nsCOMPtr<nsIDocShell> docshell = mFrameLoader->GetExistingDocShell();
//
//      if (docshell) {
//        uint32_t newFlags = 0;
//        // If a NULL aValue is passed in, we want to clear the sandbox flags
//        // which we will do by setting them to 0.
//        if (aValue) {
//          nsAutoString strValue;
//          aValue->ToString(strValue);
//          newFlags = nsContentUtils::ParseSandboxAttributeToFlags(
//            strValue);
//        }   
//        docshell->SetSandboxFlags(newFlags);
//      }
//    }
//  }
//  return nsSVGElement::AfterSetAttr(aNameSpaceID, aName, aValue,
//                                            aNotify);
//
//}


uint32_t
SVGIFrameElement::GetSandboxFlags()
{
  nsAutoString sandboxAttr;

  if (GetAttr(kNameSpaceID_None, nsGkAtoms::sandbox, sandboxAttr)) {
    return nsContentUtils::ParseSandboxAttributeToFlags(sandboxAttr);
  }

  // No sandbox attribute, no sandbox flags.
  return 0;
}

} // namespace dom
} // namespace mozilla
