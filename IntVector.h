#ifndef INTVECTOR
#define INTVECTOR

#include "HsFFI.h"


typedef struct {
  HsInt32   c_intVectorSize;
  HsInt32* c_intVectorPtr;
} C_IntVector;

#endif
