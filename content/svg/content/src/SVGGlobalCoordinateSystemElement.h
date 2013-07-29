/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_SVGGlobalCoordinateSystemElement_h
#define mozilla_dom_SVGGlobalCoordinateSystemElement_h

#include "nsSVGElement.h"
#include "nsSVGString.h"
#include "nsSVGAnimatedTransformList.h"

nsresult
NS_NewSVGGlobalCoordinateSystemElement(nsIContent **aResult,
                                       already_AddRefed<nsINodeInfo> aNodeInfo);

namespace mozilla {
namespace dom {

class SVGAnimatedTransformList;

typedef nsSVGElement SVGGlobalCoordinateSystemElementBase;

class SVGGlobalCoordinateSystemElement : public SVGGlobalCoordinateSystemElementBase
{
protected:
  SVGGlobalCoordinateSystemElement(already_AddRefed<nsINodeInfo> aNodeInfo);
  virtual JSObject*
    WrapNode(JSContext *aCx, JS::Handle<JSObject*> aScope) MOZ_OVERRIDE;
  friend nsresult
	(::NS_NewSVGGlobalCoordinateSystemElement(nsIContent **aResult,
                                              already_AddRefed<nsINodeInfo> aNodeInfo));

public:

  virtual nsresult Clone(nsINodeInfo *aNodeInfo, nsINode **aResult) const;

  virtual nsSVGAnimatedTransformList*
    GetAnimatedTransformList(uint32_t aFlags = 0);
  virtual nsIAtom* GetTransformListAttrName() const {
    return nsGkAtoms::transform;
  }

  // WebIDL
  already_AddRefed<SVGAnimatedTransformList> Transform();
  already_AddRefed<SVGAnimatedString> Href();

protected:
  virtual StringAttributesInfo GetStringInfo();

  enum { HREF };
  nsSVGString mStringAttributes[1];
  static StringInfo sStringInfo[1];

  // SVGGlobalCoordinateSystemElement values
  nsAutoPtr<nsSVGAnimatedTransformList> mTransform;
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_SVGGlobalCoordinateSystemElement_h
