#include <stdio.h>
#include <stdlib.h>

#include "HsFFI.h"
#include "DoubleVector_C.h"
#include "DoubleVector_H.h"
#include "StablePtr_Massiv/Lib_stub.h"


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


int main (int argc, char *argv[])
{   if (argc < 2) {printf("Usage: %s <intNumber>\n", argv[0]);return 2;}
    const int arg_int = atol(argv[1]);


	hs_init(&argc, &argv);	


    C_DoubleVector* doubleVecPtr_INPUT = doubleVector_enum(arg_int);
    printf("input Vec:  "); doubleVecPtr_show(*doubleVecPtr_INPUT); printf("\n");

    HsInt32 sz_OUTPUT = 0; HsDouble* doubleVecRawPtr_OUTPUT = NULL; // Inizialize
    HsStablePtr doubleVecStablePtr_OUTPUT = twiceVec_hs(doubleVecPtr_INPUT->c_doubleVectorSize, doubleVecPtr_INPUT->c_doubleVectorPtr, &sz_OUTPUT, &doubleVecRawPtr_OUTPUT);
    C_DoubleVector doubleVec_OUTPUT = (C_DoubleVector) {.c_doubleVectorSize = sz_OUTPUT, .c_doubleVectorPtr = doubleVecRawPtr_OUTPUT};
    printf("twice:      "); doubleVecPtr_show(doubleVec_OUTPUT);              printf("\n");


    massiv_free_hs(doubleVecStablePtr_OUTPUT);


	hs_exit();


    vector_free_c(doubleVecPtr_INPUT);

	return 0;
}