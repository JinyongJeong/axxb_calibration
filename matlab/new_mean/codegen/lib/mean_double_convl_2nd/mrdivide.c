/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mrdivide.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 11-Jun-2015 01:24:21
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "mean_double_convl_2nd.h"
#include "mrdivide.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : double A[16]
 *                const double B[16]
 * Return Type  : void
 */
void b_mrdivide(double A[16], const double B[16])
{
  double b_A[16];
  int info;
  int ipiv[4];
  int jp;
  int jAcol;
  int k;
  int kBcol;
  int i;
  double temp;
  memcpy(&b_A[0], &B[0], sizeof(double) << 4);
  eml_xgetrf(b_A, ipiv, &info);
  for (info = 0; info < 4; info++) {
    jp = info << 2;
    jAcol = info << 2;
    for (k = 0; k + 1 <= info; k++) {
      kBcol = k << 2;
      if (b_A[k + jAcol] != 0.0) {
        for (i = 0; i < 4; i++) {
          A[i + jp] -= b_A[k + jAcol] * A[i + kBcol];
        }
      }
    }

    temp = 1.0 / b_A[info + jAcol];
    for (i = 0; i < 4; i++) {
      A[i + jp] *= temp;
    }
  }

  for (info = 3; info > -1; info += -1) {
    jp = info << 2;
    jAcol = info << 2;
    for (k = info + 1; k + 1 < 5; k++) {
      kBcol = k << 2;
      if (b_A[k + jAcol] != 0.0) {
        for (i = 0; i < 4; i++) {
          A[i + jp] -= b_A[k + jAcol] * A[i + kBcol];
        }
      }
    }
  }

  for (info = 2; info > -1; info += -1) {
    if (ipiv[info] != info + 1) {
      jp = ipiv[info] - 1;
      for (jAcol = 0; jAcol < 4; jAcol++) {
        temp = A[jAcol + (info << 2)];
        A[jAcol + (info << 2)] = A[jAcol + (jp << 2)];
        A[jAcol + (jp << 2)] = temp;
      }
    }
  }
}

/*
 * Arguments    : double A[16]
 *                int ipiv[4]
 *                int *info
 * Return Type  : void
 */
void eml_xgetrf(double A[16], int ipiv[4], int *info)
{
  int i21;
  int j;
  int c;
  int iy;
  int ix;
  double smax;
  int jy;
  double s;
  int b_j;
  int ijA;
  for (i21 = 0; i21 < 4; i21++) {
    ipiv[i21] = 1 + i21;
  }

  *info = 0;
  for (j = 0; j < 3; j++) {
    c = j * 5;
    iy = 0;
    ix = c;
    smax = fabs(A[c]);
    for (jy = 2; jy <= 4 - j; jy++) {
      ix++;
      s = fabs(A[ix]);
      if (s > smax) {
        iy = jy - 1;
        smax = s;
      }
    }

    if (A[c + iy] != 0.0) {
      if (iy != 0) {
        ipiv[j] = (j + iy) + 1;
        ix = j;
        iy += j;
        for (jy = 0; jy < 4; jy++) {
          smax = A[ix];
          A[ix] = A[iy];
          A[iy] = smax;
          ix += 4;
          iy += 4;
        }
      }

      i21 = (c - j) + 4;
      for (iy = c + 1; iy + 1 <= i21; iy++) {
        A[iy] /= A[c];
      }
    } else {
      *info = j + 1;
    }

    iy = c;
    jy = c + 4;
    for (b_j = 1; b_j <= 3 - j; b_j++) {
      smax = A[jy];
      if (A[jy] != 0.0) {
        ix = c + 1;
        i21 = (iy - j) + 8;
        for (ijA = 5 + iy; ijA + 1 <= i21; ijA++) {
          A[ijA] += A[ix] * -smax;
          ix++;
        }
      }

      jy += 4;
      iy += 4;
    }
  }

  if ((*info == 0) && (!(A[15] != 0.0))) {
    *info = 4;
  }
}

/*
 * Arguments    : const double A_data[]
 *                const int A_size[2]
 *                const double B[16]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void mrdivide(const double A_data[], const int A_size[2], const double B[16],
              double y_data[], int y_size[2])
{
  double A[16];
  int info;
  int ipiv[4];
  int jp;
  int jAcol;
  int k;
  int kBcol;
  int i;
  double temp;
  memcpy(&A[0], &B[0], sizeof(double) << 4);
  eml_xgetrf(A, ipiv, &info);
  y_size[0] = 4;
  y_size[1] = A_size[1];
  info = A_size[0] * A_size[1];
  for (jp = 0; jp < info; jp++) {
    y_data[jp] = A_data[jp];
  }

  for (info = 0; info < 4; info++) {
    jp = info << 2;
    jAcol = info << 2;
    for (k = 0; k + 1 <= info; k++) {
      kBcol = k << 2;
      if (A[k + jAcol] != 0.0) {
        for (i = 0; i < 4; i++) {
          y_data[i + jp] -= A[k + jAcol] * y_data[i + kBcol];
        }
      }
    }

    temp = 1.0 / A[info + jAcol];
    for (i = 0; i < 4; i++) {
      y_data[i + jp] *= temp;
    }
  }

  for (info = 3; info > -1; info += -1) {
    jp = info << 2;
    jAcol = info << 2;
    for (k = info + 1; k + 1 < 5; k++) {
      kBcol = k << 2;
      if (A[k + jAcol] != 0.0) {
        for (i = 0; i < 4; i++) {
          y_data[i + jp] -= A[k + jAcol] * y_data[i + kBcol];
        }
      }
    }
  }

  for (info = 2; info > -1; info += -1) {
    if (ipiv[info] != info + 1) {
      jp = ipiv[info] - 1;
      for (jAcol = 0; jAcol < 4; jAcol++) {
        temp = y_data[jAcol + (info << 2)];
        y_data[jAcol + (info << 2)] = y_data[jAcol + (jp << 2)];
        y_data[jAcol + (jp << 2)] = temp;
      }
    }
  }
}

/*
 * File trailer for mrdivide.c
 *
 * [EOF]
 */
