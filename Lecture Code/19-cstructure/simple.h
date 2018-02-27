/*
 * Simple interface
 *
 * 15-122 Principles of Imperative Computation */

#ifndef _SIMPLE_H_
#define _SIMPLE_H_

int absval(int x)
  /*@requires x >= INT_MIN; @*/
  /*@ensures \result >= 0;  @*/ ;

struct point2d {
  int x;
  int y;
};

#endif
