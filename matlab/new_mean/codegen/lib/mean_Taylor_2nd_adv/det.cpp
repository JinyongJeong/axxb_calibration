//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: det.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 31-Aug-2015 00:46:55
//

// Include Files
#include "rt_nonfinite.h"
#include "mean_Taylor_2nd_adv.h"
#include "det.h"
#include <stdio.h>

// Function Definitions

//
// Arguments    : const double x[9]
// Return Type  : double
//
double det(const double x[9])
{
  double y;
  double A[9];
  signed char ipiv[3];
  int i6;
  int j;
  int c;
  int iy;
  int ix;
  double smax;
  int jy;
  double s;
  int b_j;
  int ijA;
  boolean_T isodd;
  memcpy(&A[0], &x[0], 9U * sizeof(double));
  for (i6 = 0; i6 < 3; i6++) {
    ipiv[i6] = (signed char)(1 + i6);
  }

  for (j = 0; j < 2; j++) {
    c = j << 2;
    iy = 0;
    ix = c;
    smax = fabs(A[c]);
    for (jy = 2; jy <= 3 - j; jy++) {
      ix++;
      s = fabs(A[ix]);
      if (s > smax) {
        iy = jy - 1;
        smax = s;
      }
    }

    if (A[c + iy] != 0.0) {
      if (iy != 0) {
        ipiv[j] = (signed char)((j + iy) + 1);
        ix = j;
        iy += j;
        for (jy = 0; jy < 3; jy++) {
          smax = A[ix];
          A[ix] = A[iy];
          A[iy] = smax;
          ix += 3;
          iy += 3;
        }
      }

      i6 = (c - j) + 3;
      for (iy = c + 1; iy + 1 <= i6; iy++) {
        A[iy] /= A[c];
      }
    }

    iy = c;
    jy = c + 3;
    for (b_j = 1; b_j <= 2 - j; b_j++) {
      smax = A[jy];
      if (A[jy] != 0.0) {
        ix = c + 1;
        i6 = (iy - j) + 6;
        for (ijA = 4 + iy; ijA + 1 <= i6; ijA++) {
          A[ijA] += A[ix] * -smax;
          ix++;
        }
      }

      jy += 3;
      iy += 3;
    }
  }

  y = A[0];
  isodd = false;
  for (jy = 0; jy < 2; jy++) {
    y *= A[(jy + 3 * (jy + 1)) + 1];
    if (ipiv[jy] > 1 + jy) {
      isodd = !isodd;
    }
  }

  if (isodd) {
    y = -y;
  }

  return y;
}

//
// File trailer for det.cpp
//
// [EOF]
//
