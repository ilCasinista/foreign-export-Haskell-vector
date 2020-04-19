#ifndef DOUBLEVECTOR_H
#define DOUBLEVECTOR_H

#include "HsFFI.h"
#include "../DoubleVector.h"

typedef struct {
  C_DoubleVector c_doubleVector;
  HsStablePtr    c_doubleVectorStablePtr;
} C_DoubleVector_H;

#endif
