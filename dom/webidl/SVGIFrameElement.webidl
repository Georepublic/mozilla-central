/* -*- Mode: IDL; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * The origin of this IDL file is
 * http://www.w3.org/Graphics/SVG/WG/wiki/Proposals/IFrame_Like_Syntax#5.8_The_.27iframe.27_element
 * but based
 * http://www.whatwg.org/specs/web-apps/current-work/#the-iframe-element
 *
 * © Copyright 2004-2011 Apple Computer, Inc., Mozilla Foundation, and
 * Opera Software ASA. You are granted a license to use, reproduce
 * and create derivative works of this document.
 * Copyright © 2013 KDDI, Inc.
 */

interface SVGIFrameElement : SVGGraphicsElement {
  [Constant]
  readonly attribute SVGAnimatedLength x;
  [Constant]
  readonly attribute SVGAnimatedLength y;
  [Constant]
  readonly attribute SVGAnimatedLength width;
  [Constant]
  readonly attribute SVGAnimatedLength height;
  [Constant]
  readonly attribute SVGAnimatedPreserveAspectRatio preserveAspectRatio;

  [Constant]
  readonly attribute SVGAnimatedString media;
  [Constant]
  readonly attribute SVGAnimatedString name;
  [Constant]
  readonly attribute SVGAnimatedString src;
  [Constant]
  readonly attribute SVGAnimatedString srcdoc;
  // maybe to use DOMSettableTokenList
  [Constant]
  readonly attribute SVGAnimatedString sandbox;

  // not implement yet
  //[Constant]
  //readonly attribute SVGAnimatedBoolean seamless;
};
