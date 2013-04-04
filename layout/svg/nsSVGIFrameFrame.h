/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef NS_SVGIFRAMEFRAME_H
#define NS_SVGIFRAMEFRAME_H

#include "mozilla/Attributes.h"
#include "nsIPresShell.h"
#include "nsISVGChildFrame.h"
#include "nsRegion.h"
#include "nsSubDocumentFrame.h"
#include "nsSVGUtils.h"
//#include "nsSVGIFrameForeignObjectFrame.h"
#include "nsContainerFrame.h"

class nsRenderingContext;
class nsSVGOuterSVGFrame;

typedef nsSubDocumentFrame nsSVGIFrameFrameBase;

class nsSVGIFrameFrame : public nsSVGIFrameFrameBase,
                         public nsISVGChildFrame
{
  friend nsIFrame*
  NS_NewSVGIFrameFrame(nsIPresShell* aPresShell, nsStyleContext* aContext);
protected:
  nsSVGIFrameFrame(nsStyleContext* aContext);

public:
  NS_DECL_QUERYFRAME
  NS_DECL_FRAMEARENA_HELPERS

  // nsIFrame methods
  virtual void  Init(nsIContent* aContent,
                     nsIFrame*   aParent,
                     nsIFrame*   aPrevInFlow) MOZ_OVERRIDE;
  NS_IMETHOD SetInitialChildList(ChildListID  aListID,
                                 nsFrameList& aChildList) MOZ_OVERRIDE;
  NS_IMETHOD AppendFrames(ChildListID  aListID,
                          nsFrameList& aFrameList);
  NS_IMETHOD InsertFrames(ChildListID aListID,
                          nsIFrame* aPrevFrame,
                          nsFrameList& aFrameList);
  NS_IMETHOD RemoveFrame(ChildListID aListID,
                         nsIFrame* aOldFrame) MOZ_OVERRIDE;


  
  virtual void DestroyFrom(nsIFrame* aDestructRoot);

  NS_IMETHOD  AttributeChanged(int32_t         aNameSpaceID,
                               nsIAtom*        aAttribute,
                               int32_t         aModType);

  virtual void DidSetStyleContext(nsStyleContext* aOldStyleContext) MOZ_OVERRIDE;

  /*
  virtual nsIFrame* GetContentInsertionFrame() {
    nsIFrame *frame = GetFirstPrincipalChild();
    if (!frame)
      return nullptr;
    return frame->GetContentInsertionFrame();
    }*/

  virtual nsIFrame* GetSubdocumentRootFrame();  

  NS_IMETHOD Reflow(nsPresContext*           aPresContext,
                    nsHTMLReflowMetrics&     aDesiredSize,
                    const nsHTMLReflowState& aReflowState,
                    nsReflowStatus&          aStatus);

  // void BuildDisplayList(nsDisplayListBuilder*   aBuilder,
  //                       const nsRect&           aDirtyRect,
  //                       const nsDisplayListSet& aLists);

  /**
   * Get the "type" of the frame
   *
   * @see nsGkAtoms::svgIFrameFrame
   */
  virtual nsIAtom* GetType() const;

  virtual bool IsFrameOfType(uint32_t aFlags) const
  {
    return nsSVGIFrameFrameBase::IsFrameOfType(aFlags &
      ~(nsIFrame::eSVG | nsIFrame::eSVGForeignObject));
  }

  virtual bool IsSVGTransformed(gfxMatrix *aOwnTransform,
                                gfxMatrix *aFromParentTransform) const;

  /* from nsContainerFrame */
  virtual const nsFrameList& GetChildList(ChildListID aList) const MOZ_OVERRIDE;
  virtual void GetChildLists(nsTArray<ChildList>* aLists) const MOZ_OVERRIDE;

  
  /**
   * Invokes the WillReflow() function, positions the frame and its view (if
   * requested), and then calls Reflow(). If the reflow succeeds and the child
   * frame is complete, deletes any next-in-flows using DeleteNextInFlowChild()
   *
   * Flags:
   * NS_FRAME_NO_MOVE_VIEW - don't position the frame's view. Set this if you
   *    don't want to automatically sync the frame and view
   * NS_FRAME_NO_MOVE_FRAME - don't move the frame. aX and aY are ignored in this
   *    case. Also implies NS_FRAME_NO_MOVE_VIEW
   */
  nsresult ReflowChild(nsIFrame*                      aKidFrame,
                       nsPresContext*                 aPresContext,
                       nsHTMLReflowMetrics&           aDesiredSize,
                       const nsHTMLReflowState&       aReflowState,
                       nscoord                        aX,
                       nscoord                        aY,
                       uint32_t                       aFlags,
                       nsReflowStatus&                aStatus,
                       nsOverflowContinuationTracker* aTracker = nullptr);

  /**
   * The second half of frame reflow. Does the following:
   * - sets the frame's bounds
   * - sizes and positions (if requested) the frame's view. If the frame's final
   *   position differs from the current position and the frame itself does not
   *   have a view, then any child frames with views are positioned so they stay
   *   in sync
   * - sets the view's visibility, opacity, content transparency, and clip
   * - invoked the DidReflow() function
   *
   * Flags:
   * NS_FRAME_NO_MOVE_FRAME - don't move the frame. aX and aY are ignored in this
   *    case. Also implies NS_FRAME_NO_MOVE_VIEW
   * NS_FRAME_NO_MOVE_VIEW - don't position the frame's view. Set this if you
   *    don't want to automatically sync the frame and view
   * NS_FRAME_NO_SIZE_VIEW - don't size the frame's view
   */
  static nsresult FinishReflowChild(nsIFrame*                  aKidFrame,
                                    nsPresContext*             aPresContext,
                                    const nsHTMLReflowState*   aReflowState,
                                    const nsHTMLReflowMetrics& aDesiredSize,
                                    nscoord                    aX,
                                    nscoord                    aY,
                                    uint32_t                   aFlags);

  static void PositionChildViews(nsIFrame* aFrame);

  // Positions the frame's view based on the frame's origin
  static void PositionFrameView(nsIFrame* aKidFrame);

  // Set the view's size and position after its frame has been reflowed.
  //
  // Flags:
  // NS_FRAME_NO_MOVE_VIEW - don't position the frame's view. Set this if you
  //    don't want to automatically sync the frame and view
  // NS_FRAME_NO_SIZE_VIEW - don't size the view
  static void SyncFrameViewAfterReflow(nsPresContext* aPresContext,
                                       nsIFrame*       aFrame,
                                       nsView*        aView,
                                       const nsRect&   aVisualOverflowArea,
                                       uint32_t        aFlags = 0);

  // ==========================================================================
  /* Overflow containers are continuation frames that hold overflow. They
   * are created when the frame runs out of computed height, but still has
   * too much content to fit in the availableHeight. The parent creates a
   * continuation as usual, but marks it as NS_FRAME_IS_OVERFLOW_CONTAINER
   * and adds it to its next-in-flow's overflow container list, either by
   * adding it directly or by putting it in its own excess overflow containers
   * list (to be drained by the next-in-flow when it calls
   * ReflowOverflowContainerChildren). The parent continues reflow as if
   * the frame was complete once it ran out of computed height, but returns
   * either an NS_FRAME_NOT_COMPLETE or NS_FRAME_OVERFLOW_INCOMPLETE reflow
   * status to request a next-in-flow. The parent's next-in-flow is then
   * responsible for calling ReflowOverflowContainerChildren to (drain and)
   * reflow these overflow continuations. Overflow containers do not affect
   * other frames' size or position during reflow (but do affect their
   * parent's overflow area).
   *
   * Overflow container continuations are different from normal continuations
   * in that
   *   - more than one child of the frame can have its next-in-flow broken
   *     off and pushed into the frame's next-in-flow
   *   - new continuations may need to be spliced into the middle of the list
   *     or deleted continuations slipped out
   *     e.g. A, B, C are all fixed-size containers on one page, all have
   *      overflow beyond availableHeight, and content is dynamically added
   *      and removed from B
   * As a result, it is not possible to simply prepend the new continuations
   * to the old list as with the overflowProperty mechanism. To avoid
   * complicated list splicing, the code assumes only one overflow containers
   * list exists for a given frame: either its own overflowContainersProperty
   * or its prev-in-flow's excessOverflowContainersProperty, not both.
   *
   * The nsOverflowContinuationTracker helper class should be used for tracking
   * overflow containers and adding them to the appropriate list.
   * See nsBlockFrame::Reflow for a sample implementation.
   */

  friend class nsOverflowContinuationTracker;

  
#ifdef DEBUG
  NS_IMETHOD GetFrameName(nsAString& aResult) const
  {
    return MakeFrameName(NS_LITERAL_STRING("SVGIFrame"), aResult);
  }
#endif

  // nsISVGChildFrame interface:
  NS_IMETHOD PaintSVG(nsRenderingContext *aContext,
                      const nsIntRect *aDirtyRect);
  NS_IMETHOD_(nsIFrame*) GetFrameForPoint(const nsPoint &aPoint) MOZ_OVERRIDE;
  NS_IMETHOD_(nsRect) GetCoveredRegion() MOZ_OVERRIDE;
  virtual void ReflowSVG() MOZ_OVERRIDE;
  virtual void NotifySVGChanged(uint32_t aFlags) MOZ_OVERRIDE;
  virtual SVGBBox GetBBoxContribution(const gfxMatrix &aToBBoxUserspace,
                                      uint32_t aFlags) MOZ_OVERRIDE;
  NS_IMETHOD_(bool) IsDisplayContainer() MOZ_OVERRIDE { return true; }

  gfxMatrix GetCanvasTM(uint32_t aFor);

  nsRect GetInvalidRegion();

protected:
  friend class AsyncSVGFrameInit;

  
  // implementation helpers:
  void DoReflow();
  void RequestReflow(nsIPresShell::IntrinsicDirty aType);

  // If width or height is less than or equal to zero we must disable rendering
  bool IsDisabled() const { return mRect.width <= 0 || mRect.height <= 0; }

  nsAutoPtr<gfxMatrix> mCanvasTM;

  bool mInReflow;

  // implementation from nsContainerFrame
  void BuildDisplayListForNonBlockChildren(nsDisplayListBuilder*   aBuilder,
                                           const nsRect&           aDirtyRect,
                                           const nsDisplayListSet& aLists,
                                           uint32_t                aFlags = 0);

  nsFrameList mFrames;

  //nsSVGIFrameForeignObjectFrame* mForeignObject;

  // Show our document viewer. The document viewer is hidden via a script
  // runner, so that we can save and restore the presentation if we're
  // being reframed.
  void ShowViewer();

  
};

#endif
