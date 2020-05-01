#include <stdio.h>
#include <stdlib.h>

#include "HsFFI.h"

#include "DoubleVector.h"
#include "StablePtr_Vector_extractor/Lib_stub.h"
#include "StablePtr_Vector_extractor/SomethingToVector_stub.h"


void vector_free_c(C_DoubleVector* doubleVector) {free((void*)(doubleVector->c_doubleVectorPtr));free((void*)(doubleVector));}


C_DoubleVector* doubleVector_enum(const int n)
{ HsDouble* cDoubleVector_ = (HsDouble*) malloc(sizeof(HsDouble) * n);
  if(cDoubleVector_ == NULL) {printf("\nNOT ENOUGH MEMORY.\n");  exit(2);};
  int cDoubleVecIndex = 0; while (cDoubleVecIndex < n)
      { cDoubleVector_[cDoubleVecIndex] = ((HsDouble) cDoubleVecIndex); cDoubleVecIndex++; }
  C_DoubleVector* doubleVec = (C_DoubleVector*) malloc(sizeof(C_DoubleVector));
  doubleVec->c_doubleVectorSize = (HsInt32) n;
  doubleVec->c_doubleVectorPtr  = cDoubleVector_;
  return doubleVec;
}


char* int_show(HsInt32 c_int) {printf("%d",c_int);return NULL;}


void double_show(HsDouble c_double) {printf("%f",c_double);}


void doubleVecPtr_show(C_DoubleVector c_doubleVector)
{ HsInt32   c_doubleVectorSize = c_doubleVector.c_doubleVectorSize;
  HsDouble* c_doubleVectorPtr  = c_doubleVector.c_doubleVectorPtr;

  printf("C_DoubleVector(size="); int_show(c_doubleVectorSize); printf(",[");
  int j = 0; while(j < (int)c_doubleVectorSize) {double_show(c_doubleVectorPtr[j]); printf(","); j++;}
  printf("END])\n");
}

// Wrapper
C_DoubleVector extractFromStablePtr_vector_hs_wrapper(HsStablePtr doubleVecStablePtr_INPUT)
{   // C_DoubleVector doubleVec_OUTPUT; // Without inizialization (faster but harder to debug).
    C_DoubleVector doubleVec_OUTPUT = {.c_doubleVectorSize = 0, .c_doubleVectorPtr = NULL}; // With inizialization (slower but easier to debug).
    extractFromStablePtr_vector_hs(doubleVecStablePtr_INPUT,  &(doubleVec_OUTPUT.c_doubleVectorSize), &(doubleVec_OUTPUT.c_doubleVectorPtr));
    return doubleVec_OUTPUT;
}



int main (int argc, char *argv[])
{   if (argc < 2) {printf("Usage: %s <intNumber>\n", argv[0]);return 2;}
    const int arg_int = atol(argv[1]);


	hs_init(&argc, &argv);	


    HsStablePtr doubleVecStablePtr_INPUT = somethingToVec_hs(arg_int);



    C_DoubleVector doubleVec_OUTPUT = extractFromStablePtr_vector_hs_wrapper(doubleVecStablePtr_INPUT);
    printf("result:     "); doubleVecPtr_show(doubleVec_OUTPUT);              printf("\n");



    vector_free_hs(doubleVecStablePtr_INPUT);

	hs_exit();




	return 0;
}