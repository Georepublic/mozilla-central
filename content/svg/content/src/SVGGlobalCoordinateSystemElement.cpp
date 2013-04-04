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
#include "nsSVGElement.h"

NS_IMPL_NS_NEW_NAMESPACED_SVG_ELEMENT(GlobalCoordinateSystem)

namespace mozilla {
namespace dom {

//--------------- GlobalCoordinateSystem ------------------

JSObject*
SVGGlobalCoordinateSystemElement::WrapNode(JSContext *aCx, JSObject *aScope)
{
  return SVGGlobalCoordinateSystemElementBinding::Wrap(aCx, aScope, this);
}

nsSVGElement::StringInfo SVGGlobalCoordinateSystemElement::sStringInfo[1] =
{
  { &nsGkAtoms::href, kNameSpaceID_XLink, true }
};

//----------------------------------------------------------------------
// Implementation

SVGGlobalCoordinateSystemElement::SVGGlobalCoordinateSystemElement(already_AddRefed<nsINodeInfo> aNodeInfo)
  : SVGGlobalCoordinateSystemElementBase(aNodeInfo)
{
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

} // namespace dom
} // namespace mozilla

