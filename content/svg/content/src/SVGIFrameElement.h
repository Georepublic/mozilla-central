/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_SVGIFrameElement_h
#define mozilla_dom_SVGIFrameElement_h

#include "GenericSVGFrameElement.h"
#include "nsContentUtils.h"
#include "nsSVGLength2.h"
#include "nsSVGString.h"
#include "nsSVGElement.h"
#include "SVGAnimatedPreserveAspectRatio.h"
#include "nsIDocument.h"

nsresult NS_NewSVGIFrameElement(nsIContent **aResult,
                                already_AddRefed<nsINodeInfo> aNodeInfo,
                                mozilla::dom::FromParser aFromParser);

class nsSVGIFrameFrame;

namespace mozilla {
namespace dom {
class DOMSVGAnimatedPreserveAspectRatio;

class SVGIFrameElement MOZ_FINAL : public GenericSVGFrameElement
{
  friend class ::nsSVGIFrameFrame;

protected:
  SVGIFrameElement(already_AddRefed<nsINodeInfo> aNodeInfo,
	                 mozilla::dom::FromParser aFromParser);
  virtual JSObject* WrapNode(JSContext *aCx, JS::Handle<JSObject*> aScope) MOZ_OVERRIDE;
  virtual ~SVGIFrameElement();

  friend nsresult (::NS_NewSVGIFrameElement(nsIContent **aResult,
                                            already_AddRefed<nsINodeInfo> aNodeInfo,
                                            mozilla::dom::FromParser aFromParser));

public:
  /*
  NS_IMPL_FROMCONTENT_WITH_TAG(SVGIFrameElement, kNameSpaceID_SVG, iframe)

  // nsISupports
  NS_DECL_ISUPPORTS_INHERITED

  // nsIDOMElement
  NS_FORWARD_NSIDOMELEMENT_TO_GENERIC

  // nsIDOMSVGElement
  NS_FORWARD_NSIDOMSVGELEMENT(GenericSVGFrameElement::)
  */
  // interface
  NS_DECL_ISUPPORTS_INHERITED

  NS_DECL_CYCLE_COLLECTION_CLASS_INHERITED(SVGIFrameElement,
                                           GenericSVGFrameElement)
    
  // nsSVGElement specializations:
  virtual gfxMatrix PrependLocalTransformsTo(const gfxMatrix &aMatrix,
                                             TransformTypes aWhich = eAllTransforms) const;
  
  // nsIContent
  //virtual bool ParseAttribute(int32_t aNamespaceID,
  //                              nsIAtom* aAttribute,
  //                              const nsAString& aValue,
  //                              nsAttrValue& aResult);
  //NS_IMETHOD_(bool) IsAttributeMapped(const nsIAtom* aAttribute) const;
  //virtual nsMapRuleToAttributesFunc GetAttributeMappingFunction() const;

  virtual nsresult Clone(nsINodeInfo *aNodeInfo, nsINode **aResult) const;
  //virtual nsXPCClassInfo* GetClassInfo();

  // WebIDL
  already_AddRefed<SVGAnimatedLength> X();
  already_AddRefed<SVGAnimatedLength> Y();
  already_AddRefed<SVGAnimatedLength> Width();
  already_AddRefed<SVGAnimatedLength> Height();
  already_AddRefed<DOMSVGAnimatedPreserveAspectRatio> PreserveAspectRatio();
  already_AddRefed<SVGAnimatedString> Media();
  already_AddRefed<SVGAnimatedString> Name();
  already_AddRefed<SVGAnimatedString> Src();
  already_AddRefed<SVGAnimatedString> Srcdoc();
  already_AddRefed<SVGAnimatedString> Sandbox();
  nsIDocument* GetContentDocument();
  already_AddRefed<nsIDOMWindow> GetContentWindow();
  void SetSandbox(const nsAString & aSandbox, ErrorResult& rv);
  nsIDocument* GetSVGDocument();

  //virtual nsresult AfterSetAttr(int32_t aNameSpaceID, nsIAtom* aName,
  //                              const nsAttrValue* aValue,
  //                              bool aNotify);

  uint32_t GetSandboxFlags();

protected:
  virtual LengthAttributesInfo GetLengthInfo();
  virtual SVGAnimatedPreserveAspectRatio *GetPreserveAspectRatio();
  virtual StringAttributesInfo GetStringInfo();

  enum { ATTR_X, ATTR_Y, ATTR_WIDTH, ATTR_HEIGHT };
  nsSVGLength2 mLengthAttributes[4];
  static LengthInfo sLengthInfo[4];

  SVGAnimatedPreserveAspectRatio mPreserveAspectRatio;

  enum { MEDIA, NAME, SRC, SRCDOC, SANDBOX };
  nsSVGString mStringAttributes[5];
  static StringInfo sStringInfo[5];

  //virtual void GetItemValueText(nsAString& text);
  //virtual void SetItemValueText(const nsAString& text);
};

} // namespace dom
} // namespace mozilla
#endif // mozilla_dom_SVGIFrameElement_h
