/*
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/licenses/publicdomain/
 * Contributor: Jason Orendorff
 */

var cx = evalcx("");
evalcx("function f() { return this; }", cx);
f = cx.f;
assertEq(f(), cx);
reportCompare(0, 0, "");
