/*
 * Simple implementation
 *
 * 15-122 Principles of Imperative Computation */

#include <limits.h>
#include "lib/contracts.h"
#include "simple.h"

int absval(int x) {
  REQUIRES(x > INT_MIN);
  int res = x < 0 ? -x : x;
  ENSURES(res >= 0);
  return res;
}
