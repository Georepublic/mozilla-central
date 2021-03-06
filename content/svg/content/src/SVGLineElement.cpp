/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/SVGAnimatedLength.h"
#include "mozilla/dom/SVGLineElement.h"
#include "mozilla/dom/SVGLineElementBinding.h"
#include "gfxContext.h"

NS_IMPL_NS_NEW_NAMESPACED_SVG_ELEMENT(Line)

namespace mozilla {
namespace dom {

JSObject*
SVGLineElement::WrapNode(JSContext *aCx, JSObject *aScope, bool *aTriedToWrap)
{
  return SVGLineElementBinding::Wrap(aCx, aScope, this, aTriedToWrap);
}

nsSVGElement::LengthInfo SVGLineElement::sLengthInfo[4] =
{
  { &nsGkAtoms::x1, 0, nsIDOMSVGLength::SVG_LENGTHTYPE_NUMBER, SVGContentUtils::X },
  { &nsGkAtoms::y1, 0, nsIDOMSVGLength::SVG_LENGTHTYPE_NUMBER, SVGContentUtils::Y },
  { &nsGkAtoms::x2, 0, nsIDOMSVGLength::SVG_LENGTHTYPE_NUMBER, SVGContentUtils::X },
  { &nsGkAtoms::y2, 0, nsIDOMSVGLength::SVG_LENGTHTYPE_NUMBER, SVGContentUtils::Y },
};

//----------------------------------------------------------------------
// nsISupports methods

NS_IMPL_ISUPPORTS_INHERITED3(SVGLineElement, SVGLineElementBase,
                             nsIDOMNode, nsIDOMElement,
                             nsIDOMSVGElement)

//----------------------------------------------------------------------
// Implementation

SVGLineElement::SVGLineElement(already_AddRefed<nsINodeInfo> aNodeInfo)
  : SVGLineElementBase(aNodeInfo)
{
  SetIsDOMBinding();
}

//----------------------------------------------------------------------
// nsIDOMNode methods

NS_IMPL_ELEMENT_CLONE_WITH_INIT(SVGLineElement)

//----------------------------------------------------------------------

already_AddRefed<SVGAnimatedLength>
SVGLineElement::X1()
{
  return mLengthAttributes[ATTR_X1].ToDOMAnimatedLength(this);
}

already_AddRefed<SVGAnimatedLength>
SVGLineElement::Y1()
{
  return mLengthAttributes[ATTR_Y1].ToDOMAnimatedLength(this);
}

already_AddRefed<SVGAnimatedLength>
SVGLineElement::X2()
{
  return mLengthAttributes[ATTR_X2].ToDOMAnimatedLength(this);
}

already_AddRefed<SVGAnimatedLength>
SVGLineElement::Y2()
{
  return mLengthAttributes[ATTR_Y2].ToDOMAnimatedLength(this);
}

//----------------------------------------------------------------------
// nsIContent methods

NS_IMETHODIMP_(bool)
SVGLineElement::IsAttributeMapped(const nsIAtom* name) const
{
  static const MappedAttributeEntry* const map[] = {
    sMarkersMap
  };

  return FindAttributeDependence(name, map) ||
    SVGLineElementBase::IsAttributeMapped(name);
}

//----------------------------------------------------------------------
// nsSVGElement methods

nsSVGElement::LengthAttributesInfo
SVGLineElement::GetLengthInfo()
{
  return LengthAttributesInfo(mLengthAttributes, sLengthInfo,
                              ArrayLength(sLengthInfo));
}

//----------------------------------------------------------------------
// nsSVGPathGeometryElement methods

void
SVGLineElement::GetMarkPoints(nsTArray<nsSVGMark> *aMarks) {
  float x1, y1, x2, y2;

  GetAnimatedLengthValues(&x1, &y1, &x2, &y2, nullptr);

  float angle = atan2(y2 - y1, x2 - x1);

  aMarks->AppendElement(nsSVGMark(x1, y1, angle));
  aMarks->AppendElement(nsSVGMark(x2, y2, angle));
}

void
SVGLineElement::ConstructPath(gfxContext *aCtx)
{
  float x1, y1, x2, y2;

  GetAnimatedLengthValues(&x1, &y1, &x2, &y2, nullptr);

  aCtx->MoveTo(gfxPoint(x1, y1));
  aCtx->LineTo(gfxPoint(x2, y2));
}

} // namespace dom
} // namespace mozilla
