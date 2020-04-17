#ifndef DOUBLEVECTOR
#define DOUBLEVECTOR

#include "HsFFI.h"


typedef struct {
  HsInt32   c_doubleVectorSize;
  HsDouble* c_doubleVectorPtr;
} C_DoubleVector;

#endif
