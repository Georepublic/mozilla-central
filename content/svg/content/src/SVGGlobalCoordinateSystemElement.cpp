/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/SVGGlobalCoordinateSystemElement.h"

#include "mozilla/dom/SVGAnimatedTransformList.h"
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
SVGGlobalCoordinateSystemElement::WrapNode(JSContext *aCx, JS::Handle<JSObject*> aScope)
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

nsSVGAnimatedTransformList*
SVGGlobalCoordinateSystemElement::GetAnimatedTransformList(uint32_t aFlags)
{
  if (!mTransform && (aFlags & DO_ALLOCATE)) {
    mTransform = new nsSVGAnimatedTransformList();
  }
  return mTransform;
}

//----------------------------------------------------------------------

/* readonly attribute SVGAnimatedTransformList transform; */
already_AddRefed<SVGAnimatedTransformList>
SVGGlobalCoordinateSystemElement::Transform()
{
  // We're creating a DOM wrapper, so we must tell GetAnimatedTransformList
  // to allocate the SVGAnimatedTransformList if it hasn't already done so:
  return SVGAnimatedTransformList::GetDOMWrapper(
           GetAnimatedTransformList(DO_ALLOCATE), this);
}

//----------------------------------------------------------------------
// nsIDOMSVGURIReference methods:

/* readonly attribute SVGAnimatedString href; */
already_AddRefed<SVGAnimatedString>
SVGGlobalCoordinateSystemElement::Href()
{
  return mStringAttributes[HREF].ToDOMAnimatedString(this);
}

} // namespace dom
} // namespace mozilla

