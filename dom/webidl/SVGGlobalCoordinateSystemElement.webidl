/* -*- Mode: IDL; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * The origin of this IDL file is
 * http://www.w3.org/Graphics/SVG/WG/wiki/Proposals/IFrame_Like_Syntax#7.13.1_The_.27globalCoordinateSystem.27_element
 * (Currentry no IDL file)
 *
 * Copyright © 2013 KDDI, Inc.
 */

interface SVGGlobalCoordinateSystemElement : SVGElement {
  readonly attribute SVGAnimatedTransformList transform;
};

SVGGlobalCoordinateSystemElement implements SVGURIReference;
