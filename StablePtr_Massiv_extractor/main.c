#include <stdio.h>
#include <stdlib.h>

#include "HsFFI.h"

#include "StablePtr_Massiv_extractor/DoubleVector.h"
#include "StablePtr_Massiv_extractor/IntVector.h"
#include "StablePtr_Massiv_extractor/Lib_stub.h"
#include "StablePtr_Massiv_extractor/SomethingToMassiv_stub.h"

// Only to be used for arrays built in C.
void vector_double_free_c(C_DoubleVector* doubleVector) {free((void*)(doubleVector->c_doubleVectorPtr));free((void*)(doubleVector));}

// Only to be used for arrays built in C.
void vector_int_free_c   (C_IntVector*    intVector)    {free((void*)(intVector->c_intVectorPtr));      free((void*)(intVector));}




C_DoubleVector* doubleVector_enum(const int n)
{ HsDouble* cDoubleVector_ = (HsDouble*) malloc(sizeof(HsDouble) * n);
  if(cDoubleVector_ == NULL) {printf("\nNOT ENOUGH MEMORY.\n");  exit(2);};
  int cDoubleVecIndex = 0; while (cDoubleVecIndex < n)
      { cDoubleVector_[cDoubleVecIndex] = ((HsDouble) cDoubleVecIndex); cDoubleVecIndex++; }
  C_DoubleVector* vec_double = (C_DoubleVector*) malloc(sizeof(C_DoubleVector));
  vec_double->c_doubleVectorSize = (HsInt32) n;
  vec_double->c_doubleVectorPtr  = cDoubleVector_;
  return vec_double;
}


C_IntVector* intVector_enum(const int n)
{ HsInt32* cIntVector_ = (HsInt32*) malloc(sizeof(HsInt32) * n);
  if(cIntVector_ == NULL) {printf("\nNOT ENOUGH MEMORY.\n");  exit(2);};
  int cIntVecIndex = 0; while (cIntVecIndex < n)
      { cIntVector_[cIntVecIndex] = ((HsInt32) cIntVecIndex); cIntVecIndex++; }
  C_IntVector* vec_int = (C_IntVector*) malloc(sizeof(C_IntVector));
  vec_int->c_intVectorSize = (HsInt32) n;
  vec_int->c_intVectorPtr  = cIntVector_;
  return vec_int;
}


void int_show   (HsInt32 c_int)     {printf("%d",c_int);}

void double_show(HsDouble c_double) {printf("%f",c_double);}


void doubleVecPtr_show(C_DoubleVector c_DoubleVector_Massiv)
{ HsInt32   c_doubleVectorSize = c_DoubleVector_Massiv.c_doubleVectorSize;
  HsDouble* c_doubleVectorPtr  = c_DoubleVector_Massiv.c_doubleVectorPtr;

  printf("C_DoubleVector(size="); int_show(c_doubleVectorSize); printf(",[");
  int j = 0; while(j < (int)c_doubleVectorSize) {double_show(c_doubleVectorPtr[j]); printf(","); j++;}
  printf("END])\n");
}

void intVecPtr_show(C_IntVector c_intVector)
{ HsInt32   c_intVectorSize = c_intVector.c_intVectorSize;
  HsInt32* c_intVectorPtr  = c_intVector.c_intVectorPtr;

  printf("C_IntVector(size="); int_show(c_intVectorSize); printf(",[");
  int j = 0; while(j < (int)c_intVectorSize) {int_show(c_intVectorPtr[j]); printf(","); j++;}
  printf("END])\n");
}


// Wrapper
C_DoubleVector fromStablePtr_massiv_hs_double_wrapper(HsStablePtr stablePtr_massiv_double)
{   // C_DoubleVector vec_double; // Without inizialization (faster but harder to debug).
    C_DoubleVector vec_double = {.c_doubleVectorSize = 0, .c_doubleVectorPtr = NULL}; // With inizialization (slower but easier to debug).
    fromStablePtr_massiv_double_hs(stablePtr_massiv_double,  &(vec_double.c_doubleVectorSize), &(vec_double.c_doubleVectorPtr));
    return vec_double;
}

// Wrapper
C_IntVector fromStablePtr_massiv_hs_int_wrapper(HsStablePtr stablePtr_massiv_int)
{   // C_IntVector vec_int; // Without inizialization (faster but harder to debug).
    C_IntVector vec_int = {.c_intVectorSize = 0, .c_intVectorPtr = NULL}; // With inizialization (slower but easier to debug).
    fromStablePtr_massiv_int_hs(stablePtr_massiv_int,  &(vec_int.c_intVectorSize), &(vec_int.c_intVectorPtr));
    return vec_int;
}


int main (int argc, char *argv[])
{   if (argc < 2) {printf("Usage: %s <intNumber>\n", argv[0]);return 2;}
    const int arg_int = atol(argv[1]);


	hs_init(&argc, &argv);	



    HsStablePtr stablePtr_massiv_double = somethingToVec_double_hs(arg_int);

    C_DoubleVector vec_double = fromStablePtr_massiv_hs_double_wrapper(stablePtr_massiv_double);
    printf("result:     "); doubleVecPtr_show(vec_double);              printf("\n");

    massiv_double_free_hs(stablePtr_massiv_double); // From now on the internal array of vec_double is not available!




    HsStablePtr stablePtr_massiv_int = somethingToVec_int_hs(arg_int);

    C_IntVector vec_int = fromStablePtr_massiv_hs_int_wrapper(stablePtr_massiv_int);
    printf("result:     "); intVecPtr_show(vec_int);              printf("\n");

    massiv_int_free_hs(stablePtr_massiv_int); // From now on the internal array of vec_int is not available!




	hs_exit();




	return 0;
}