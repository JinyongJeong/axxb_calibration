//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mean_Taylor_1st_emxutil.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 30-Aug-2015 22:36:03
//
#ifndef __MEAN_TAYLOR_1ST_EMXUTIL_H__
#define __MEAN_TAYLOR_1ST_EMXUTIL_H__

// Include Files
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "mean_Taylor_1st_types.h"

// Function Declarations
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for mean_Taylor_1st_emxutil.h
//
// [EOF]
//
