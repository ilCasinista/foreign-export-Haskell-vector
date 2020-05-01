#include <stdio.h>
#include <stdlib.h>

#include "HsFFI.h"

#include "DoubleVector.h"
#include "IntVector.h"
#include "StablePtr_Vector_extractor/Lib_stub.h"
#include "StablePtr_Vector_extractor/SomethingToVector_stub.h"

// Only to be used for arrays built in C.
void vector_double_free_c(C_DoubleVector* doubleVector) {free((void*)(doubleVector->c_doubleVectorPtr));free((void*)(doubleVector));}
void vector_int_free_c   (C_IntVector*    intVector)    {free((void*)(intVector->c_intVectorPtr));      free((void*)(intVector));}


C_DoubleVector* doubleVector_enum(const int n)
{ HsDouble* cDoubleVector_ = (HsDouble*) malloc(sizeof(HsDouble) * n);
  if(cDoubleVector_ == NULL) {printf("\nNOT ENOUGH MEMORY.\n");  exit(2);};
  int cDoubleVecIndex = 0; while (cDoubleVecIndex < n)
      { cDoubleVector_[cDoubleVecIndex] = ((HsDouble) cDoubleVecIndex); cDoubleVecIndex++; }
  C_DoubleVector* double_vec = (C_DoubleVector*) malloc(sizeof(C_DoubleVector));
  double_vec->c_doubleVectorSize = (HsInt32) n;
  double_vec->c_doubleVectorPtr  = cDoubleVector_;
  return double_vec;
}


C_IntVector* intVector_enum(const int n)
{ HsInt32* cIntVector_ = (HsInt32*) malloc(sizeof(HsInt32) * n);
  if(cIntVector_ == NULL) {printf("\nNOT ENOUGH MEMORY.\n");  exit(2);};
  int cIntVecIndex = 0; while (cIntVecIndex < n)
      { cIntVector_[cIntVecIndex] = ((HsInt32) cIntVecIndex); cIntVecIndex++; }
  C_IntVector* int_vec = (C_IntVector*) malloc(sizeof(C_IntVector));
  int_vec->c_intVectorSize = (HsInt32) n;
  int_vec->c_intVectorPtr  = cIntVector_;
  return int_vec;
}


char* int_show(HsInt32 c_int) {printf("%d",c_int);}


void double_show(HsDouble c_double) {printf("%f",c_double);}


void doubleVecPtr_show(C_DoubleVector c_doubleVector)
{ HsInt32   c_doubleVectorSize = c_doubleVector.c_doubleVectorSize;
  HsDouble* c_doubleVectorPtr  = c_doubleVector.c_doubleVectorPtr;

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
C_DoubleVector extractFromStablePtr_vector_hs_double_wrapper(HsStablePtr vecStablePtr_double)
{   // C_DoubleVector double_vec; // Without inizialization (faster but harder to debug).
    C_DoubleVector double_vec = {.c_doubleVectorSize = 0, .c_doubleVectorPtr = NULL}; // With inizialization (slower but easier to debug).
    extractFromStablePtr_vector_double_hs(vecStablePtr_double,  &(double_vec.c_doubleVectorSize), &(double_vec.c_doubleVectorPtr));
    return double_vec;
}

C_IntVector extractFromStablePtr_vector_hs_int_wrapper(HsStablePtr vecStablePtr_int)
{   // C_IntVector int_vec; // Without inizialization (faster but harder to debug).
    C_IntVector int_vec = {.c_intVectorSize = 0, .c_intVectorPtr = NULL}; // With inizialization (slower but easier to debug).
    extractFromStablePtr_vector_int_hs(vecStablePtr_int,  &(int_vec.c_intVectorSize), &(int_vec.c_intVectorPtr));
    return int_vec;
}


int main (int argc, char *argv[])
{   if (argc < 2) {printf("Usage: %s <intNumber>\n", argv[0]);return 2;}
    const int arg_int = atol(argv[1]);


	hs_init(&argc, &argv);	



    HsStablePtr vecStablePtr_double = somethingToVec_double_hs(arg_int);

    C_DoubleVector double_vec = extractFromStablePtr_vector_hs_double_wrapper(vecStablePtr_double);
    printf("result:     "); doubleVecPtr_show(double_vec);              printf("\n");

    vector_double_free_hs(vecStablePtr_double); // From now on the internal array of double_vec is not available!




    HsStablePtr vecStablePtr_int = somethingToVec_int_hs(arg_int);

    C_IntVector int_vec = extractFromStablePtr_vector_hs_int_wrapper(vecStablePtr_int);
    printf("result:     "); intVecPtr_show(int_vec);              printf("\n");

    vector_int_free_hs(vecStablePtr_int); // From now on the internal array of int_vec is not available!




	hs_exit();




	return 0;
}