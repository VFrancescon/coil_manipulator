//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: dynamic_lungs_embed.cpp
//
// Code generated for Simulink model 'dynamic_lungs_embed'.
//
// Model version                  : 1.247
// Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
// C/C++ source code generated on : Tue Aug 16 14:17:18 2022
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "dynamic_lungs_embed.h"
#include "rtwtypes.h"
#include <cstring>
#include <emmintrin.h>
#include <cmath>
#include <math.h>
#include <stddef.h>
#define NumBitsPerChar                 8U

// Private macros used by the generated code to access rtModel
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

extern "C" {
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;
}
  extern "C"
{
  //
  // Initialize rtNaN needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetNaN(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T nan{ 0.0 };

    if (bitsPerReal == 32U) {
      nan = rtGetNaNF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  //
  // Initialize rtNaNF needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetNaNF(void)
  {
    IEEESingle nanF{ { 0.0F } };

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
  }
}

extern "C" {
  //
  // Initialize the rtInf, rtMinusInf, and rtNaN needed by the
  // generated code. NaN is initialized as non-signaling. Assumes IEEE.
  //
  static void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  // Test if value is infinite
  static boolean_T rtIsInf(real_T value)
  {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  // Test if single-precision value is infinite
  static boolean_T rtIsInfF(real32_T value)
  {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  // Test if value is not a number
  static boolean_T rtIsNaN(real_T value)
  {
    boolean_T result{ (boolean_T) 0 };

    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    if (bitsPerReal == 32U) {
      result = rtIsNaNF((real32_T)value);
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.fltVal = value;
      result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) ==
                           0x7FF00000 &&
                           ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                            (tmpVal.bitVal.words.wordL != 0) ));
    }

    return result;
  }

  // Test if single-precision value is not a number
  static boolean_T rtIsNaNF(real32_T value)
  {
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                       (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
  }
}
  extern "C"
{
  //
  // Initialize rtInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetInf(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T inf{ 0.0 };

    if (bitsPerReal == 32U) {
      inf = rtGetInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
    }

    return inf;
  }

  //
  // Initialize rtInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetInfF(void)
  {
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
  }

  //
  // Initialize rtMinusInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T minf{ 0.0 };

    if (bitsPerReal == 32U) {
      minf = rtGetMinusInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
    }

    return minf;
  }

  //
  // Initialize rtMinusInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetMinusInfF(void)
  {
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::mtimes(const real_T A_data[], const int32_T A_size[2],
  const real_T B_0[768], real_T C_data[], int32_T C_size[2])
{
  int32_T mc;
  mc = A_size[0];
  C_size[0] = A_size[0];
  C_size[1] = 32;
  for (int32_T j{0}; j < 32; j++) {
    int32_T boffset;
    int32_T coffset;
    coffset = j * mc;
    boffset = j * 24;
    for (int32_T i{0}; i < mc; i++) {
      C_data[coffset + i] = 0.0;
    }

    for (int32_T i{0}; i < A_size[1]; i++) {
      real_T bkj;
      int32_T aoffset;
      aoffset = i * A_size[0];
      bkj = B_0[boffset + i];
      for (int32_T b_i{1}; b_i - 1 < mc; b_i++) {
        int32_T tmp;
        tmp = (coffset + b_i) - 1;
        C_data[tmp] += A_data[(aoffset + b_i) - 1] * bkj;
      }
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::mtimes_e(const real_T A_data[], const int32_T A_size[2],
  const real_T B_data[], const int32_T B_size[2], real_T C_data[], int32_T
  C_size[2])
{
  int32_T mc;
  mc = A_size[0];
  C_size[0] = A_size[0];
  C_size[1] = 8;
  for (int32_T j{0}; j < 8; j++) {
    int32_T boffset;
    int32_T coffset;
    coffset = j * mc;
    boffset = j * B_size[0];
    for (int32_T i{0}; i < mc; i++) {
      C_data[coffset + i] = 0.0;
    }

    for (int32_T i{0}; i < 32; i++) {
      real_T bkj;
      int32_T aoffset;
      aoffset = i * A_size[0];
      bkj = B_data[boffset + i];
      for (int32_T b_i{1}; b_i - 1 < mc; b_i++) {
        int32_T tmp;
        tmp = (coffset + b_i) - 1;
        C_data[tmp] += A_data[(aoffset + b_i) - 1] * bkj;
      }
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
real_T dynamic_lungs_embed::xdotc_ilx(const real_T x[9], const real_T y[9],
  int32_T iy0)
{
  return y[iy0 - 1] * x[1] + y[iy0] * x[2];
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xaxpy_ifn40(real_T a, real_T y[9], int32_T iy0)
{
  if (!(a == 0.0)) {
    y[iy0 - 1] += a * y[1];
    y[iy0] += a * y[2];
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xscal_dk(int32_T n, real_T a, real_T x_data[], int32_T
  ix0)
{
  int32_T b;
  b = (ix0 + n) - 1;
  for (int32_T k{ix0}; k <= b; k++) {
    x_data[k - 1] *= a;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xscal_dkkv3(real_T a, real_T x[9], int32_T ix0)
{
  for (int32_T k{ix0}; k <= ix0 + 2; k++) {
    x[k - 1] *= a;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xswap_kf(real_T x[9], int32_T ix0, int32_T iy0)
{
  real_T temp;
  temp = x[ix0 - 1];
  x[ix0 - 1] = x[iy0 - 1];
  x[iy0 - 1] = temp;
  temp = x[ix0];
  x[ix0] = x[iy0];
  x[iy0] = temp;
  temp = x[ix0 + 1];
  x[ix0 + 1] = x[iy0 + 1];
  x[iy0 + 1] = temp;
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xswap(int32_T n, real_T x_data[], int32_T ix0, int32_T
  iy0)
{
  int32_T ix;
  int32_T iy;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (int32_T k{0}; k < n; k++) {
    real_T temp;
    temp = x_data[ix];
    x_data[ix] = x_data[iy];
    x_data[iy] = temp;
    ix++;
    iy++;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xrotg(real_T *a, real_T *b, real_T *c, real_T *s)
{
  real_T absa;
  real_T absb;
  real_T roe;
  real_T scale;
  roe = *b;
  absa = std::abs(*a);
  absb = std::abs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    *a = 0.0;
    *b = 0.0;
  } else {
    real_T ads;
    real_T bds;
    ads = absa / scale;
    bds = absb / scale;
    scale *= std::sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }

    *a = scale;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xrot_dm(real_T x[9], int32_T ix0, int32_T iy0, real_T
  c, real_T s)
{
  real_T temp;
  real_T temp_tmp;
  temp = x[iy0 - 1];
  temp_tmp = x[ix0 - 1];
  x[iy0 - 1] = temp * c - temp_tmp * s;
  x[ix0 - 1] = temp_tmp * c + temp * s;
  temp = x[ix0] * c + x[iy0] * s;
  x[iy0] = x[iy0] * c - x[ix0] * s;
  x[ix0] = temp;
  temp = x[iy0 + 1];
  temp_tmp = x[ix0 + 1];
  x[iy0 + 1] = temp * c - temp_tmp * s;
  x[ix0 + 1] = temp_tmp * c + temp * s;
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xrot(int32_T n, real_T x_data[], int32_T ix0, int32_T
  iy0, real_T c, real_T s)
{
  if (n >= 1) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (int32_T k{0}; k < n; k++) {
      real_T temp;
      temp = x_data[ix] * c + x_data[iy] * s;
      x_data[iy] = x_data[iy] * c - x_data[ix] * s;
      x_data[ix] = temp;
      iy++;
      ix++;
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
real_T dynamic_lungs_embed::xdotc_i(int32_T n, const real_T x_data[], int32_T
  ix0, const real_T y_data[], int32_T iy0)
{
  real_T d;
  d = 0.0;
  if (n >= 1) {
    int32_T ix;
    int32_T iy;
    ix = ix0;
    iy = iy0;
    for (int32_T k{0}; k < n; k++) {
      d += x_data[ix - 1] * y_data[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xaxpy_i(int32_T n, real_T a, int32_T ix0, real_T
  y_data[], int32_T iy0)
{
  if ((n >= 1) && (!(a == 0.0))) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (int32_T k{0}; k < n; k++) {
      y_data[iy] += y_data[ix] * a;
      ix++;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
real_T dynamic_lungs_embed::xnrm2_h(int32_T n, const real_T x_data[], int32_T
  ix0)
{
  real_T y;
  y = 0.0;
  if (n == 1) {
    y = std::abs(x_data[ix0 - 1]);
  } else {
    real_T scale;
    int32_T kend;
    scale = 3.3121686421112381E-170;
    kend = (ix0 + n) - 1;
    for (int32_T k{ix0}; k <= kend; k++) {
      real_T absxk;
      absxk = std::abs(x_data[k - 1]);
      if (absxk > scale) {
        real_T t;
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        real_T t;
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * std::sqrt(y);
  }

  return y;
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xscal_dkk(int32_T n, real_T a, real_T x_data[],
  int32_T ix0)
{
  int32_T b;
  b = (ix0 + n) - 1;
  for (int32_T k{ix0}; k <= b; k++) {
    x_data[k - 1] *= a;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
real_T dynamic_lungs_embed::xnrm2_ht(const real_T x[3], int32_T ix0)
{
  real_T scale;
  real_T y;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (int32_T k{ix0}; k <= ix0 + 1; k++) {
    real_T absxk;
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      real_T t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      real_T t;
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xscal_dkkv(real_T a, real_T x[3], int32_T ix0)
{
  for (int32_T k{ix0}; k <= ix0 + 1; k++) {
    x[k - 1] *= a;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xaxpy_ifn4(int32_T n, real_T a, const real_T x_data[],
  int32_T ix0, real_T y_data[], int32_T iy0)
{
  if ((n >= 1) && (!(a == 0.0))) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (int32_T k{0}; k < n; k++) {
      y_data[iy] += a * x_data[ix];
      ix++;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xaxpy_ifn(int32_T n, real_T a, const real_T x_data[],
  int32_T ix0, real_T y_data[], int32_T iy0)
{
  if ((n >= 1) && (!(a == 0.0))) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (int32_T k{0}; k < n; k++) {
      y_data[iy] += x_data[ix] * a;
      ix++;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
real_T dynamic_lungs_embed::xdotc(int32_T n, const real_T x_data[], int32_T ix0,
  const real_T y_data[], int32_T iy0)
{
  real_T d;
  int32_T ix;
  int32_T iy;
  ix = ix0;
  iy = iy0;
  d = 0.0;
  for (int32_T k{0}; k < n; k++) {
    d += x_data[ix - 1] * y_data[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xaxpy_if(int32_T n, real_T a, int32_T ix0, real_T
  y_data[], int32_T iy0)
{
  if (!(a == 0.0)) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (int32_T k{0}; k < n; k++) {
      y_data[iy] += y_data[ix] * a;
      ix++;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::svd(const real_T A_data[], const int32_T A_size[2],
  real_T U_data[], int32_T U_size[2], real_T s_data[], int32_T *s_size, real_T
  V_data[], int32_T V_size[2])
{
  real_T b_A_data[108];
  real_T t_data[108];
  real_T work_data[36];
  real_T Vf[9];
  real_T b_s_data[3];
  real_T e[3];
  real_T p;
  real_T r;
  real_T rt;
  real_T smm1;
  real_T sqds;
  real_T ztest;
  int32_T b_A_size[2];
  int32_T l_size[2];
  int32_T t_size[2];
  int32_T iter;
  int32_T kase;
  int32_T loop_ub;
  int32_T m;
  int32_T n;
  int32_T nct;
  int32_T nmqp1;
  int32_T qp1jj;
  b_A_size[0] = A_size[0];
  loop_ub = A_size[0] * 3;
  if (loop_ub - 1 >= 0) {
    std::memcpy(&b_A_data[0], &A_data[0], loop_ub * sizeof(real_T));
  }

  n = A_size[0];
  b_s_data[0] = 0.0;
  e[0] = 0.0;
  b_s_data[1] = 0.0;
  e[1] = 0.0;
  b_s_data[2] = 0.0;
  e[2] = 0.0;
  loop_ub = static_cast<int8_T>(A_size[0]);
  if (loop_ub - 1 >= 0) {
    std::memset(&work_data[0], 0, loop_ub * sizeof(real_T));
  }

  U_size[0] = static_cast<int8_T>(A_size[0]);
  U_size[1] = 3;
  loop_ub = static_cast<int8_T>(A_size[0]) * 3 - 1;
  if (loop_ub >= 0) {
    std::memset(&U_data[0], 0, (loop_ub + 1) * sizeof(real_T));
  }

  std::memset(&Vf[0], 0, 9U * sizeof(real_T));
  if (A_size[0] - 1 <= 3) {
    nct = A_size[0] - 1;
  } else {
    nct = 3;
  }

  for (m = 0; m < nct; m++) {
    boolean_T apply_transform;
    qp1jj = n * m + m;
    iter = n - m;
    apply_transform = false;
    if (m + 1 <= nct) {
      r = xnrm2_h(iter, b_A_data, qp1jj + 1);
      if (r > 0.0) {
        apply_transform = true;
        if (b_A_data[qp1jj] < 0.0) {
          b_s_data[m] = -r;
        } else {
          b_s_data[m] = r;
        }

        if (std::abs(b_s_data[m]) >= 1.0020841800044864E-292) {
          t_size[0] = b_A_size[0];
          t_size[1] = 3;
          loop_ub = b_A_size[0] * 3;
          if (loop_ub - 1 >= 0) {
            std::memcpy(&t_data[0], &b_A_data[0], loop_ub * sizeof(real_T));
          }

          xscal_dkk(iter, 1.0 / b_s_data[m], t_data, qp1jj + 1);
          b_A_size[0] = t_size[0];
          loop_ub = t_size[0] * 3;
          if (loop_ub - 1 >= 0) {
            std::memcpy(&b_A_data[0], &t_data[0], loop_ub * sizeof(real_T));
          }
        } else {
          nmqp1 = qp1jj + iter;
          for (int32_T b_A{qp1jj}; b_A < nmqp1; b_A++) {
            b_A_data[b_A] /= b_s_data[m];
          }
        }

        b_A_data[qp1jj]++;
        b_s_data[m] = -b_s_data[m];
      } else {
        b_s_data[m] = 0.0;
      }
    }

    for (nmqp1 = m + 1; nmqp1 + 1 < 4; nmqp1++) {
      kase = (n * nmqp1 + m) + 1;
      if (apply_transform) {
        t_size[0] = b_A_size[0];
        t_size[1] = 3;
        loop_ub = b_A_size[0] * 3;
        if (loop_ub - 1 >= 0) {
          std::memcpy(&t_data[0], &b_A_data[0], loop_ub * sizeof(real_T));
        }

        xaxpy_if(iter, -(xdotc(iter, b_A_data, qp1jj + 1, b_A_data, kase) /
                         b_A_data[m + b_A_size[0] * m]), qp1jj + 1, t_data, kase);
        b_A_size[0] = t_size[0];
        loop_ub = t_size[0] * 3;
        if (loop_ub - 1 >= 0) {
          std::memcpy(&b_A_data[0], &t_data[0], loop_ub * sizeof(real_T));
        }
      }

      e[nmqp1] = b_A_data[kase - 1];
    }

    if (m + 1 <= nct) {
      for (qp1jj = m; qp1jj < n; qp1jj++) {
        U_data[qp1jj + U_size[0] * m] = b_A_data[b_A_size[0] * m + qp1jj];
      }
    }

    if (m + 1 <= 1) {
      r = xnrm2_ht(e, 2);
      if (r == 0.0) {
        e[0] = 0.0;
      } else {
        if (e[1] < 0.0) {
          e[0] = -r;
        } else {
          e[0] = r;
        }

        r = e[0];
        if (std::abs(e[0]) >= 1.0020841800044864E-292) {
          xscal_dkkv(1.0 / e[0], e, 2);
        } else {
          for (qp1jj = 1; qp1jj < 3; qp1jj++) {
            e[qp1jj] /= r;
          }
        }

        e[1]++;
        e[0] = -e[0];
        for (qp1jj = 2; qp1jj <= n; qp1jj++) {
          work_data[qp1jj - 1] = 0.0;
        }

        for (qp1jj = 1; qp1jj + 1 < 4; qp1jj++) {
          xaxpy_ifn(iter - 1, e[qp1jj], b_A_data, n * qp1jj + 2, work_data, 2);
        }

        for (qp1jj = 1; qp1jj + 1 < 4; qp1jj++) {
          t_size[0] = b_A_size[0];
          t_size[1] = 3;
          loop_ub = b_A_size[0] * 3;
          if (loop_ub - 1 >= 0) {
            std::memcpy(&t_data[0], &b_A_data[0], loop_ub * sizeof(real_T));
          }

          xaxpy_ifn4(iter - 1, -e[qp1jj] / e[1], work_data, 2, t_data, n * qp1jj
                     + 2);
          b_A_size[0] = t_size[0];
          loop_ub = t_size[0] * 3;
          if (loop_ub - 1 >= 0) {
            std::memcpy(&b_A_data[0], &t_data[0], loop_ub * sizeof(real_T));
          }
        }
      }

      for (iter = 1; iter + 1 < 4; iter++) {
        Vf[iter] = e[iter];
      }
    }
  }

  m = 1;
  if (nct < 3) {
    b_s_data[2] = b_A_data[(b_A_size[0] << 1) + 2];
  }

  e[1] = b_A_data[(b_A_size[0] << 1) + 1];
  e[2] = 0.0;
  if (nct + 1 <= 3) {
    for (iter = 0; iter < n; iter++) {
      U_data[iter + (U_size[0] << 1)] = 0.0;
    }

    U_data[2 + (static_cast<int8_T>(A_size[0]) << 1)] = 1.0;
  }

  for (nct--; nct + 1 > 0; nct--) {
    iter = n - nct;
    qp1jj = n * nct + nct;
    if (b_s_data[nct] != 0.0) {
      for (int32_T b_A{nct + 1}; b_A + 1 < 4; b_A++) {
        kase = (n * b_A + nct) + 1;
        l_size[0] = U_size[0];
        l_size[1] = 3;
        loop_ub = U_size[0] * 3;
        if (loop_ub - 1 >= 0) {
          std::memcpy(&b_A_data[0], &U_data[0], loop_ub * sizeof(real_T));
        }

        xaxpy_i(iter, -(xdotc_i(iter, U_data, qp1jj + 1, U_data, kase) /
                        U_data[qp1jj]), qp1jj + 1, b_A_data, kase);
        U_size[0] = l_size[0];
        U_size[1] = l_size[1];
        loop_ub = l_size[0] * l_size[1];
        if (loop_ub - 1 >= 0) {
          std::memcpy(&U_data[0], &b_A_data[0], loop_ub * sizeof(real_T));
        }
      }

      for (iter = nct; iter < n; iter++) {
        loop_ub = U_size[0] * nct + iter;
        U_data[loop_ub] = -U_data[loop_ub];
      }

      U_data[qp1jj]++;
      for (iter = 0; iter < nct; iter++) {
        U_data[iter + U_size[0] * nct] = 0.0;
      }
    } else {
      for (iter = 0; iter < n; iter++) {
        U_data[iter + U_size[0] * nct] = 0.0;
      }

      U_data[qp1jj] = 1.0;
    }
  }

  for (iter = 2; iter >= 0; iter--) {
    if ((iter + 1 <= 1) && (e[0] != 0.0)) {
      xaxpy_ifn40(-(xdotc_ilx(Vf, Vf, 5) / Vf[1]), Vf, 5);
      xaxpy_ifn40(-(xdotc_ilx(Vf, Vf, 8) / Vf[1]), Vf, 8);
    }

    Vf[3 * iter] = 0.0;
    Vf[3 * iter + 1] = 0.0;
    Vf[3 * iter + 2] = 0.0;
    Vf[iter + 3 * iter] = 1.0;
  }

  for (iter = 0; iter < 3; iter++) {
    ztest = e[iter];
    if (b_s_data[iter] != 0.0) {
      rt = std::abs(b_s_data[iter]);
      r = b_s_data[iter] / rt;
      b_s_data[iter] = rt;
      if (iter + 1 < 3) {
        ztest /= r;
      }

      l_size[0] = U_size[0];
      l_size[1] = 3;
      loop_ub = U_size[0] * 3;
      if (loop_ub - 1 >= 0) {
        std::memcpy(&b_A_data[0], &U_data[0], loop_ub * sizeof(real_T));
      }

      xscal_dk(n, r, b_A_data, n * iter + 1);
      U_size[0] = l_size[0];
      U_size[1] = l_size[1];
      loop_ub = l_size[0] * l_size[1];
      if (loop_ub - 1 >= 0) {
        std::memcpy(&U_data[0], &b_A_data[0], loop_ub * sizeof(real_T));
      }
    }

    if ((iter + 1 < 3) && (ztest != 0.0)) {
      rt = std::abs(ztest);
      r = rt / ztest;
      ztest = rt;
      b_s_data[iter + 1] *= r;
      xscal_dkkv3(r, Vf, 3 * (iter + 1) + 1);
    }

    e[iter] = ztest;
  }

  iter = 0;
  r = std::fmax(std::fmax(std::fmax(0.0, std::fmax(std::abs(b_s_data[0]), std::
    abs(e[0]))), std::fmax(std::abs(b_s_data[1]), std::abs(e[1]))), std::fmax
                (std::abs(b_s_data[2]), std::abs(e[2])));
  while ((m + 2 > 0) && (iter < 75)) {
    kase = m + 1;
    int32_T exitg1;
    do {
      exitg1 = 0;
      nct = kase;
      if (kase == 0) {
        exitg1 = 1;
      } else {
        rt = std::abs(e[kase - 1]);
        if (rt <= (std::abs(b_s_data[kase - 1]) + std::abs(b_s_data[kase])) *
            2.2204460492503131E-16) {
          e[kase - 1] = 0.0;
          exitg1 = 1;
        } else if ((rt <= 1.0020841800044864E-292) || ((iter > 20) && (rt <=
                     2.2204460492503131E-16 * r))) {
          e[kase - 1] = 0.0;
          exitg1 = 1;
        } else {
          kase--;
        }
      }
    } while (exitg1 == 0);

    if (m + 1 == kase) {
      kase = 4;
    } else {
      boolean_T exitg2;
      qp1jj = m + 2;
      nmqp1 = m + 2;
      exitg2 = false;
      while ((!exitg2) && (nmqp1 >= kase)) {
        qp1jj = nmqp1;
        if (nmqp1 == kase) {
          exitg2 = true;
        } else {
          rt = 0.0;
          if (nmqp1 < m + 2) {
            rt = std::abs(e[nmqp1 - 1]);
          }

          if (nmqp1 > kase + 1) {
            rt += std::abs(e[nmqp1 - 2]);
          }

          ztest = std::abs(b_s_data[nmqp1 - 1]);
          if ((ztest <= 2.2204460492503131E-16 * rt) || (ztest <=
               1.0020841800044864E-292)) {
            b_s_data[nmqp1 - 1] = 0.0;
            exitg2 = true;
          } else {
            nmqp1--;
          }
        }
      }

      if (qp1jj == kase) {
        kase = 3;
      } else if (m + 2 == qp1jj) {
        kase = 1;
      } else {
        kase = 2;
        nct = qp1jj;
      }
    }

    switch (kase) {
     case 1:
      rt = e[m];
      e[m] = 0.0;
      for (qp1jj = m; qp1jj + 1 >= nct + 1; qp1jj--) {
        p = b_s_data[qp1jj];
        xrotg(&p, &rt, &ztest, &sqds);
        b_s_data[qp1jj] = p;
        if (qp1jj + 1 > nct + 1) {
          rt = -sqds * e[0];
          e[0] *= ztest;
        }

        xrot_dm(Vf, 3 * qp1jj + 1, 3 * (m + 1) + 1, ztest, sqds);
      }
      break;

     case 2:
      rt = e[nct - 1];
      e[nct - 1] = 0.0;
      for (qp1jj = nct; qp1jj < m + 2; qp1jj++) {
        p = b_s_data[qp1jj];
        xrotg(&p, &rt, &ztest, &sqds);
        b_s_data[qp1jj] = p;
        rt = -sqds * e[qp1jj];
        e[qp1jj] *= ztest;
        l_size[0] = U_size[0];
        l_size[1] = 3;
        loop_ub = U_size[0] * 3;
        if (loop_ub - 1 >= 0) {
          std::memcpy(&b_A_data[0], &U_data[0], loop_ub * sizeof(real_T));
        }

        xrot(n, b_A_data, n * qp1jj + 1, n * (nct - 1) + 1, ztest, sqds);
        U_size[0] = l_size[0];
        U_size[1] = l_size[1];
        loop_ub = l_size[0] * l_size[1];
        if (loop_ub - 1 >= 0) {
          std::memcpy(&U_data[0], &b_A_data[0], loop_ub * sizeof(real_T));
        }
      }
      break;

     case 3:
      {
        real_T emm1;
        real_T shift;
        sqds = b_s_data[m + 1];
        ztest = std::fmax(std::fmax(std::fmax(std::fmax(std::abs(sqds), std::abs
          (b_s_data[m])), std::abs(e[m])), std::abs(b_s_data[nct])), std::abs
                          (e[nct]));
        rt = sqds / ztest;
        smm1 = b_s_data[m] / ztest;
        emm1 = e[m] / ztest;
        sqds = b_s_data[nct] / ztest;
        smm1 = ((smm1 + rt) * (smm1 - rt) + emm1 * emm1) / 2.0;
        emm1 *= rt;
        emm1 *= emm1;
        if ((smm1 != 0.0) || (emm1 != 0.0)) {
          shift = std::sqrt(smm1 * smm1 + emm1);
          if (smm1 < 0.0) {
            shift = -shift;
          }

          shift = emm1 / (smm1 + shift);
        } else {
          shift = 0.0;
        }

        rt = (sqds + rt) * (sqds - rt) + shift;
        ztest = e[nct] / ztest * sqds;
        for (qp1jj = nct + 1; qp1jj <= m + 1; qp1jj++) {
          xrotg(&rt, &ztest, &sqds, &smm1);
          if (qp1jj > nct + 1) {
            e[0] = rt;
          }

          rt = e[qp1jj - 1];
          emm1 = b_s_data[qp1jj - 1];
          e[qp1jj - 1] = rt * sqds - emm1 * smm1;
          ztest = smm1 * b_s_data[qp1jj];
          b_s_data[qp1jj] *= sqds;
          xrot_dm(Vf, 3 * (qp1jj - 1) + 1, 3 * qp1jj + 1, sqds, smm1);
          p = emm1 * sqds + rt * smm1;
          xrotg(&p, &ztest, &sqds, &smm1);
          b_s_data[qp1jj - 1] = p;
          rt = e[qp1jj - 1] * sqds + smm1 * b_s_data[qp1jj];
          b_s_data[qp1jj] = e[qp1jj - 1] * -smm1 + sqds * b_s_data[qp1jj];
          ztest = smm1 * e[qp1jj];
          e[qp1jj] *= sqds;
          l_size[0] = U_size[0];
          l_size[1] = 3;
          loop_ub = U_size[0] * 3;
          if (loop_ub - 1 >= 0) {
            std::memcpy(&b_A_data[0], &U_data[0], loop_ub * sizeof(real_T));
          }

          xrot(n, b_A_data, n * (qp1jj - 1) + 1, n * qp1jj + 1, sqds, smm1);
          U_size[0] = l_size[0];
          U_size[1] = l_size[1];
          loop_ub = l_size[0] * l_size[1];
          if (loop_ub - 1 >= 0) {
            std::memcpy(&U_data[0], &b_A_data[0], loop_ub * sizeof(real_T));
          }
        }

        e[m] = rt;
        iter++;
      }
      break;

     default:
      if (b_s_data[nct] < 0.0) {
        b_s_data[nct] = -b_s_data[nct];
        xscal_dkkv3(-1.0, Vf, 3 * nct + 1);
      }

      iter = nct + 1;
      while ((nct + 1 < 3) && (b_s_data[nct] < b_s_data[iter])) {
        rt = b_s_data[nct];
        b_s_data[nct] = b_s_data[iter];
        b_s_data[iter] = rt;
        xswap_kf(Vf, 3 * nct + 1, 3 * (nct + 1) + 1);
        l_size[0] = U_size[0];
        l_size[1] = 3;
        loop_ub = U_size[0] * 3;
        if (loop_ub - 1 >= 0) {
          std::memcpy(&b_A_data[0], &U_data[0], loop_ub * sizeof(real_T));
        }

        xswap(n, b_A_data, n * nct + 1, n * (nct + 1) + 1);
        U_size[0] = l_size[0];
        U_size[1] = l_size[1];
        loop_ub = l_size[0] * l_size[1];
        if (loop_ub - 1 >= 0) {
          std::memcpy(&U_data[0], &b_A_data[0], loop_ub * sizeof(real_T));
        }

        nct = iter;
        iter++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  *s_size = 3;
  V_size[0] = 3;
  V_size[1] = 3;
  for (n = 0; n < 3; n++) {
    s_data[n] = b_s_data[n];
    V_data[3 * n] = Vf[3 * n];
    V_data[1 + 3 * n] = Vf[3 * n + 1];
    V_data[2 + 3 * n] = Vf[3 * n + 2];
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xswap_k(real_T x_data[])
{
  real_T temp;
  temp = x_data[0];
  x_data[0] = x_data[3];
  x_data[3] = temp;
  temp = x_data[1];
  x_data[1] = x_data[4];
  x_data[4] = temp;
  temp = x_data[2];
  x_data[2] = x_data[5];
  x_data[5] = temp;
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xrot_d(real_T x_data[], int32_T ix0, int32_T iy0,
  real_T c, real_T s)
{
  real_T temp;
  real_T temp_tmp;
  temp = x_data[iy0 - 1];
  temp_tmp = x_data[ix0 - 1];
  x_data[iy0 - 1] = temp * c - temp_tmp * s;
  x_data[ix0 - 1] = temp_tmp * c + temp * s;
  temp = x_data[ix0] * c + x_data[iy0] * s;
  x_data[iy0] = x_data[iy0] * c - x_data[ix0] * s;
  x_data[ix0] = temp;
  temp = x_data[iy0 + 1];
  temp_tmp = x_data[ix0 + 1];
  x_data[iy0 + 1] = temp * c - temp_tmp * s;
  x_data[ix0 + 1] = temp_tmp * c + temp * s;
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xscal_d(real_T a, real_T x_data[], int32_T ix0)
{
  for (int32_T k{ix0}; k <= ix0 + 2; k++) {
    x_data[k - 1] *= a;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xaxpy(int32_T n, real_T a, int32_T ix0, real_T y_data[],
  int32_T iy0)
{
  if (!(a == 0.0)) {
    int32_T ix;
    int32_T iy;
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (int32_T k{0}; k < n; k++) {
      y_data[iy] += y_data[ix] * a;
      ix++;
      iy++;
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
real_T dynamic_lungs_embed::xnrm2(int32_T n, const real_T x_data[], int32_T ix0)
{
  real_T scale;
  real_T y;
  int32_T kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (int32_T k{ix0}; k <= kend; k++) {
    real_T absxk;
    absxk = std::abs(x_data[k - 1]);
    if (absxk > scale) {
      real_T t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      real_T t;
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xscal(int32_T n, real_T a, real_T x_data[], int32_T
  ix0)
{
  int32_T b;
  b = (ix0 + n) - 1;
  for (int32_T k{ix0}; k <= b; k++) {
    x_data[k - 1] *= a;
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::xzsvdc(real_T A_data[], const int32_T A_size[2],
  real_T U_data[], int32_T U_size[2], real_T S_data[], int32_T *S_size, real_T
  V_data[], int32_T V_size[2])
{
  real_T n_data[108];
  real_T l_data[9];
  real_T u_data[9];
  real_T e_data[2];
  real_T s_data[2];
  real_T smm1;
  real_T sqds;
  real_T t;
  real_T ztest;
  real_T ztest0;
  int32_T n_size[2];
  int32_T u_size[2];
  int32_T iter;
  int32_T m;
  int32_T p;
  int32_T s_size_idx_0_tmp;
  p = A_size[1];
  s_size_idx_0_tmp = static_cast<int8_T>(A_size[1]);
  if (s_size_idx_0_tmp - 1 >= 0) {
    std::memset(&s_data[0], 0, s_size_idx_0_tmp * sizeof(real_T));
  }

  if (s_size_idx_0_tmp - 1 >= 0) {
    std::memset(&e_data[0], 0, s_size_idx_0_tmp * sizeof(real_T));
  }

  U_size[0] = 3;
  U_size[1] = static_cast<int8_T>(A_size[1]);
  s_size_idx_0_tmp = 3 * static_cast<int8_T>(A_size[1]) - 1;
  if (s_size_idx_0_tmp >= 0) {
    std::memset(&U_data[0], 0, (s_size_idx_0_tmp + 1) * sizeof(real_T));
  }

  n_size[0] = static_cast<int8_T>(A_size[1]);
  s_size_idx_0_tmp = static_cast<int8_T>(A_size[1]) * static_cast<int8_T>
    (A_size[1]);
  if (s_size_idx_0_tmp - 1 >= 0) {
    std::memset(&n_data[0], 0, s_size_idx_0_tmp * sizeof(real_T));
  }

  if (A_size[1] == 0) {
    for (m = 0; m < p; m++) {
      U_data[m + 3 * m] = 1.0;
    }
  } else {
    real_T snorm;
    int32_T kase;
    int32_T qs;
    for (m = 0; m < p; m++) {
      boolean_T apply_transform;
      s_size_idx_0_tmp = m + 2;
      iter = (3 * m + m) + 1;
      apply_transform = false;
      if (m + 1 <= p) {
        snorm = xnrm2(3 - m, A_data, iter);
        if (snorm > 0.0) {
          apply_transform = true;
          if (A_data[iter - 1] < 0.0) {
            s_data[m] = -snorm;
          } else {
            s_data[m] = snorm;
          }

          if (std::abs(s_data[m]) >= 1.0020841800044864E-292) {
            xscal(3 - m, 1.0 / s_data[m], A_data, iter);
          } else {
            kase = (iter - m) + 2;
            for (qs = iter; qs <= kase; qs++) {
              A_data[qs - 1] /= s_data[m];
            }
          }

          A_data[iter - 1]++;
          s_data[m] = -s_data[m];
        } else {
          s_data[m] = 0.0;
        }
      }

      while (s_size_idx_0_tmp <= p) {
        if (apply_transform) {
          xaxpy(3 - m, -(xdotc(3 - m, A_data, iter, A_data, m + 4) / A_data[m +
                         3 * m]), iter, A_data, m + 4);
        }

        e_data[1] = A_data[m + 3];
        s_size_idx_0_tmp = 3;
      }

      if (m + 1 <= p) {
        for (iter = m; iter + 1 < 4; iter++) {
          kase = 3 * m + iter;
          U_data[kase] = A_data[kase];
        }
      }
    }

    m = A_size[1];
    if (A_size[1] > 1) {
      e_data[0] = A_data[3];
    }

    e_data[A_size[1] - 1] = 0.0;
    if ((A_size[1] + 1 <= A_size[1]) && (A_size[1] + 1 <= A_size[1])) {
      U_data[3] = 0.0;
      U_data[5] = 0.0;
      U_data[4] = 1.0;
    }

    for (s_size_idx_0_tmp = A_size[1] - 1; s_size_idx_0_tmp + 1 > 0;
         s_size_idx_0_tmp--) {
      iter = 3 * s_size_idx_0_tmp + s_size_idx_0_tmp;
      if (s_data[s_size_idx_0_tmp] != 0.0) {
        qs = s_size_idx_0_tmp + 2;
        while (qs <= p) {
          xaxpy(3 - s_size_idx_0_tmp, -(xdotc(3 - s_size_idx_0_tmp, U_data, iter
                  + 1, U_data, s_size_idx_0_tmp + 4) / U_data[iter]), iter + 1,
                U_data, s_size_idx_0_tmp + 4);
          qs = 3;
        }

        for (qs = s_size_idx_0_tmp; qs + 1 < 4; qs++) {
          kase = 3 * s_size_idx_0_tmp + qs;
          U_data[kase] = -U_data[kase];
        }

        U_data[iter]++;
        if (s_size_idx_0_tmp - 1 >= 0) {
          U_data[3 * s_size_idx_0_tmp] = 0.0;
        }
      } else {
        U_data[3 * s_size_idx_0_tmp] = 0.0;
        U_data[1 + 3 * s_size_idx_0_tmp] = 0.0;
        U_data[2 + 3 * s_size_idx_0_tmp] = 0.0;
        U_data[iter] = 1.0;
      }
    }

    for (iter = A_size[1] - 1; iter + 1 > 0; iter--) {
      for (s_size_idx_0_tmp = 0; s_size_idx_0_tmp < p; s_size_idx_0_tmp++) {
        n_data[s_size_idx_0_tmp + n_size[0] * iter] = 0.0;
      }

      n_data[iter + n_size[0] * iter] = 1.0;
    }

    for (iter = 0; iter < p; iter++) {
      if (s_data[iter] != 0.0) {
        ztest0 = std::abs(s_data[iter]);
        snorm = s_data[iter] / ztest0;
        s_data[iter] = ztest0;
        if (iter + 1 < p) {
          e_data[0] /= snorm;
        }

        u_size[0] = 3;
        u_size[1] = U_size[1];
        s_size_idx_0_tmp = 3 * U_size[1];
        if (s_size_idx_0_tmp - 1 >= 0) {
          std::memcpy(&u_data[0], &U_data[0], s_size_idx_0_tmp * sizeof(real_T));
        }

        xscal_d(snorm, u_data, 3 * iter + 1);
        qs = u_size[1];
        s_size_idx_0_tmp = 3 * u_size[1];
        if (s_size_idx_0_tmp - 1 >= 0) {
          std::memcpy(&l_data[0], &u_data[0], s_size_idx_0_tmp * sizeof(real_T));
        }

        U_size[0] = 3;
        U_size[1] = qs;
        s_size_idx_0_tmp = 3 * qs;
        if (s_size_idx_0_tmp - 1 >= 0) {
          std::memcpy(&U_data[0], &l_data[0], s_size_idx_0_tmp * sizeof(real_T));
        }
      }

      if ((iter + 1 < p) && (e_data[0] != 0.0)) {
        ztest0 = std::abs(e_data[0]);
        snorm = ztest0 / e_data[0];
        e_data[0] = ztest0;
        s_data[1] *= snorm;
        xscal_dk(2, snorm, n_data, 3);
      }
    }

    iter = 0;
    snorm = 0.0;
    for (s_size_idx_0_tmp = 0; s_size_idx_0_tmp < p; s_size_idx_0_tmp++) {
      snorm = std::fmax(snorm, std::fmax(std::abs(s_data[s_size_idx_0_tmp]), std::
        abs(e_data[s_size_idx_0_tmp])));
    }

    while ((m > 0) && (iter < 75)) {
      boolean_T exitg1;
      s_size_idx_0_tmp = m - 1;
      exitg1 = false;
      while (!(exitg1 || (s_size_idx_0_tmp == 0))) {
        ztest0 = std::abs(e_data[0]);
        if (ztest0 <= (std::abs(s_data[0]) + std::abs(s_data[1])) *
            2.2204460492503131E-16) {
          e_data[0] = 0.0;
          exitg1 = true;
        } else if ((ztest0 <= 1.0020841800044864E-292) || ((iter > 20) &&
                    (ztest0 <= 2.2204460492503131E-16 * snorm))) {
          e_data[0] = 0.0;
          exitg1 = true;
        } else {
          s_size_idx_0_tmp = 0;
        }
      }

      if (m - 1 == s_size_idx_0_tmp) {
        kase = 4;
      } else {
        qs = m;
        kase = m;
        exitg1 = false;
        while ((!exitg1) && (kase >= s_size_idx_0_tmp)) {
          qs = kase;
          if (kase == s_size_idx_0_tmp) {
            exitg1 = true;
          } else {
            ztest0 = 0.0;
            if (kase < m) {
              ztest0 = std::abs(e_data[0]);
            }

            if (kase > s_size_idx_0_tmp + 1) {
              ztest0 += std::abs(e_data[0]);
            }

            ztest = std::abs(s_data[kase - 1]);
            if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
                 1.0020841800044864E-292)) {
              s_data[kase - 1] = 0.0;
              exitg1 = true;
            } else {
              kase--;
            }
          }
        }

        if (qs == s_size_idx_0_tmp) {
          kase = 3;
        } else if (qs == m) {
          kase = 1;
        } else {
          kase = 2;
          s_size_idx_0_tmp = qs;
        }
      }

      switch (kase) {
       case 1:
        ztest0 = e_data[0];
        e_data[0] = 0.0;
        qs = m - 1;
        while (qs >= s_size_idx_0_tmp + 1) {
          t = s_data[0];
          xrotg(&t, &ztest0, &ztest, &sqds);
          s_data[0] = t;
          xrot(p, n_data, 1, p * (m - 1) + 1, ztest, sqds);
          qs = 0;
        }
        break;

       case 2:
        ztest0 = e_data[s_size_idx_0_tmp - 1];
        e_data[s_size_idx_0_tmp - 1] = 0.0;
        for (qs = s_size_idx_0_tmp; qs < m; qs++) {
          t = s_data[qs];
          xrotg(&t, &ztest0, &ztest, &sqds);
          s_data[qs] = t;
          ztest0 = -sqds * e_data[qs];
          e_data[qs] *= ztest;
          xrot_d(U_data, 3 * qs + 1, 3 * (s_size_idx_0_tmp - 1) + 1, ztest, sqds);
        }
        break;

       case 3:
        {
          real_T emm1;
          real_T shift;
          ztest0 = s_data[m - 1];
          ztest = std::fmax(std::fmax(std::fmax(std::fmax(std::abs(ztest0), std::
            abs(s_data[0])), std::abs(e_data[0])), std::abs
            (s_data[s_size_idx_0_tmp])), std::abs(e_data[s_size_idx_0_tmp]));
          ztest0 /= ztest;
          smm1 = s_data[0] / ztest;
          emm1 = e_data[0] / ztest;
          sqds = s_data[s_size_idx_0_tmp] / ztest;
          smm1 = ((smm1 + ztest0) * (smm1 - ztest0) + emm1 * emm1) / 2.0;
          emm1 *= ztest0;
          emm1 *= emm1;
          if ((smm1 != 0.0) || (emm1 != 0.0)) {
            shift = std::sqrt(smm1 * smm1 + emm1);
            if (smm1 < 0.0) {
              shift = -shift;
            }

            shift = emm1 / (smm1 + shift);
          } else {
            shift = 0.0;
          }

          ztest0 = (sqds + ztest0) * (sqds - ztest0) + shift;
          ztest = e_data[s_size_idx_0_tmp] / ztest * sqds;
          while (s_size_idx_0_tmp + 1 < 2) {
            xrotg(&ztest0, &ztest, &sqds, &smm1);
            ztest0 = sqds * s_data[0] + smm1 * e_data[0];
            e_data[0] = sqds * e_data[0] - smm1 * s_data[0];
            ztest = smm1 * s_data[1];
            s_data[1] *= sqds;
            xrot(p, n_data, 1, p + 1, sqds, smm1);
            t = ztest0;
            xrotg(&t, &ztest, &sqds, &smm1);
            s_data[0] = t;
            ztest0 = sqds * e_data[0] + smm1 * s_data[1];
            s_data[1] = -smm1 * e_data[0] + sqds * s_data[1];
            ztest = smm1 * e_data[1];
            e_data[1] *= sqds;
            xrot_d(U_data, 1, 4, sqds, smm1);
            s_size_idx_0_tmp = 1;
          }

          e_data[0] = ztest0;
          iter++;
        }
        break;

       default:
        if (s_data[s_size_idx_0_tmp] < 0.0) {
          s_data[s_size_idx_0_tmp] = -s_data[s_size_idx_0_tmp];
          xscal_dk(p, -1.0, n_data, p * s_size_idx_0_tmp + 1);
        }

        while ((s_size_idx_0_tmp + 1 < p) && (s_data[0] < s_data[1])) {
          ztest0 = s_data[0];
          s_data[0] = s_data[1];
          s_data[1] = ztest0;
          xswap(2, n_data, 1, 3);
          xswap_k(U_data);
          s_size_idx_0_tmp = 1;
        }

        iter = 0;
        m--;
        break;
      }
    }
  }

  *S_size = A_size[1];
  for (m = 0; m < p; m++) {
    S_data[m] = s_data[m];
  }

  V_size[0] = static_cast<int8_T>(A_size[1]);
  V_size[1] = static_cast<int8_T>(A_size[1]);
  for (m = 0; m < p; m++) {
    for (iter = 0; iter < p; iter++) {
      V_data[iter + static_cast<int8_T>(p) * m] = n_data[n_size[0] * m + iter];
    }
  }
}

// Function for MATLAB Function: '<Root>/MATLAB Function2'
void dynamic_lungs_embed::pinv(const real_T A_data[], const int32_T A_size[2],
  real_T X_data[], int32_T X_size[2])
{
  real_T U_data[108];
  real_T V_data[9];
  real_T b_A_data[6];
  real_T b_A_data_0[6];
  real_T b_X_data[6];
  real_T s_data[3];
  real_T b_s_data[2];
  int32_T U_size[2];
  int32_T V_size[2];
  int32_T b_x_size[2];
  int32_T br;
  int32_T r;
  if (A_size[0] < 3) {
    int32_T b_A_size_idx_1;
    int32_T lastColC;
    int32_T m;
    m = A_size[0];
    b_A_size_idx_1 = A_size[0];
    for (br = 0; br < m; br++) {
      b_A_data[3 * br] = A_data[br];
      b_A_data[1 + 3 * br] = A_data[br + A_size[0]];
      b_A_data[2 + 3 * br] = A_data[(A_size[0] << 1) + br];
    }

    m = A_size[0];
    lastColC = A_size[0] * 3 - 1;
    if (lastColC >= 0) {
      std::memset(&b_X_data[0], 0, (lastColC + 1) * sizeof(real_T));
    }

    if (A_size[0] != 0) {
      int32_T nx;
      int32_T vcol;
      boolean_T p;
      nx = 3 * A_size[0];
      p = true;
      for (vcol = 0; vcol < nx; vcol++) {
        if (p && (std::isinf(b_A_data[vcol]) || std::isnan(b_A_data[vcol]))) {
          p = false;
        }
      }

      if (!p) {
        m = A_size[0];
        for (br = 0; br <= lastColC; br++) {
          b_X_data[br] = (rtNaN);
        }
      } else {
        real_T absx;
        U_size[0] = 3;
        U_size[1] = A_size[0];
        br = 3 * A_size[0] - 1;
        if (br >= 0) {
          std::memcpy(&b_A_data_0[0], &b_A_data[0], (br + 1) * sizeof(real_T));
        }

        xzsvdc(b_A_data_0, U_size, b_A_data, V_size, b_s_data, &br, U_data,
               b_x_size);
        absx = std::abs(b_s_data[0]);
        if ((!std::isinf(absx)) && (!std::isnan(absx))) {
          if (absx <= 2.2250738585072014E-308) {
            absx = 4.94065645841247E-324;
          } else {
            frexp(absx, &r);
            absx = std::ldexp(1.0, r - 53);
          }
        } else {
          absx = (rtNaN);
        }

        absx *= 3.0;
        r = -1;
        nx = 0;
        while ((nx <= b_A_size_idx_1 - 1) && (b_s_data[nx] > absx)) {
          r++;
          nx++;
        }

        if (r + 1 > 0) {
          vcol = 0;
          for (lastColC = 0; lastColC <= r; lastColC++) {
            absx = 1.0 / b_s_data[lastColC];
            br = vcol + b_A_size_idx_1;
            while (vcol + 1 <= br) {
              U_data[vcol] *= absx;
              vcol++;
            }

            vcol = br;
          }

          lastColC = A_size[0] << 1;
          nx = 0;
          while ((b_A_size_idx_1 > 0) && (nx <= lastColC)) {
            vcol = nx;
            br = nx + b_A_size_idx_1;
            while (vcol + 1 <= br) {
              b_X_data[vcol] = 0.0;
              vcol++;
            }

            nx += b_A_size_idx_1;
          }

          br = 0;
          vcol = 0;
          while ((b_A_size_idx_1 > 0) && (vcol <= lastColC)) {
            int32_T b;
            nx = -1;
            br++;
            b = 3 * r + br;
            for (int32_T ib{br}; ib <= b; ib += 3) {
              int32_T b_ic;
              int32_T e;
              int32_T ia;
              ia = nx;
              b_ic = vcol;
              e = vcol + b_A_size_idx_1;
              while (b_ic + 1 <= e) {
                ia++;
                b_X_data[b_ic] += b_A_data[ib - 1] * U_data[ia];
                b_ic++;
              }

              nx += b_A_size_idx_1;
            }

            vcol += b_A_size_idx_1;
          }
        }
      }
    }

    X_size[0] = 3;
    X_size[1] = m;
    for (br = 0; br < m; br++) {
      X_data[3 * br] = b_X_data[br];
      X_data[1 + 3 * br] = b_X_data[br + m];
      X_data[2 + 3 * br] = b_X_data[(m << 1) + br];
    }
  } else {
    int32_T lastColC;
    int32_T m;
    int32_T nx;
    int32_T vcol;
    boolean_T p;
    m = A_size[0];
    X_size[0] = 3;
    X_size[1] = A_size[0];
    lastColC = 3 * A_size[0] - 1;
    std::memset(&X_data[0], 0, (lastColC + 1) * sizeof(real_T));
    nx = A_size[0] * 3;
    p = true;
    for (vcol = 0; vcol < nx; vcol++) {
      if (p && (std::isinf(A_data[vcol]) || std::isnan(A_data[vcol]))) {
        p = false;
      }
    }

    if (!p) {
      X_size[0] = 3;
      X_size[1] = A_size[0];
      for (br = 0; br <= lastColC; br++) {
        X_data[br] = (rtNaN);
      }
    } else {
      real_T absx;
      svd(A_data, A_size, U_data, U_size, s_data, &br, V_data, V_size);
      absx = std::abs(s_data[0]);
      if ((!std::isinf(absx)) && (!std::isnan(absx))) {
        if (absx <= 2.2250738585072014E-308) {
          absx = 4.94065645841247E-324;
        } else {
          frexp(absx, &r);
          absx = std::ldexp(1.0, r - 53);
        }
      } else {
        absx = (rtNaN);
      }

      absx *= static_cast<real_T>(A_size[0]);
      r = -1;
      nx = 0;
      while ((nx < 3) && (s_data[nx] > absx)) {
        r++;
        nx++;
      }

      if (r + 1 > 0) {
        vcol = 0;
        for (lastColC = 0; lastColC <= r; lastColC++) {
          absx = 1.0 / s_data[lastColC];
          for (br = vcol; br < vcol + 3; br++) {
            V_data[br] *= absx;
          }

          vcol += 3;
        }

        lastColC = (A_size[0] - 1) * 3;
        for (nx = 0; nx <= lastColC; nx += 3) {
          for (vcol = nx + 1; vcol <= nx + 3; vcol++) {
            X_data[vcol - 1] = 0.0;
          }
        }

        br = 0;
        for (vcol = 0; vcol <= lastColC; vcol += 3) {
          int32_T b;
          nx = -1;
          br++;
          b = m * r + br;
          for (int32_T ib{br}; ib <= b; ib += m) {
            int32_T ia;
            ia = nx;
            for (int32_T b_ic{vcol}; b_ic < vcol + 3; b_ic++) {
              ia++;
              X_data[b_ic] += U_data[ib - 1] * V_data[ia];
            }

            nx += 3;
          }
        }
      }
    }
  }
}

// Model step function
void dynamic_lungs_embed::step()
{
  static const int8_T T0[16]{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

  static const int8_T t[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T g_b[3]{ 0, 1, 0 };

  static const int8_T h_b[3]{ 1, 0, 0 };

  static const int8_T r[3]{ 0, 0, 1 };

  __m128d tmp;
  __m128d tmp_0;
  real_T A_data[288];
  real_T p_data[219];
  real_T Ji_data[216];
  real_T T_Local_data[208];
  real_T y_data[108];
  real_T z_data[108];
  real_T varargin_1[48];
  real_T varargin_2[48];
  real_T varargin_3[48];
  real_T varargin_4[48];
  real_T b_A[36];
  real_T z[18];
  real_T M_deformed[12];
  real_T rtb_q_error[12];
  real_T Rot[9];
  real_T ang[9];
  real_T c_b_0[9];
  real_T c_b_1[9];
  real_T z_tmp[9];
  real_T rtb_U[8];
  real_T rtb_U_n[8];
  real_T T_Local[3];
  real_T c_b[3];
  real_T d_b_idx_1;
  real_T d_b_idx_2;
  real_T e_b_idx_0;
  real_T e_b_idx_1;
  real_T e_b_idx_2;
  real_T s;
  real_T z_tmp_0;
  real_T z_tmp_1;
  real_T z_tmp_2;
  int32_T A_size[2];
  int32_T J_size[2];
  int32_T decom_size[2];
  int32_T tmp_size[2];
  int32_T y_size[2];
  int32_T Ji_size_idx_1_tmp;
  int32_T N;
  int32_T T_Local_data_tmp;
  int32_T T_Local_tmp;
  int32_T b;
  int32_T b_0;
  int32_T b_b_tmp;
  int32_T boffset;
  int32_T c_b_tmp;
  int32_T coffset;
  int32_T e_b_idx_0_tmp_tmp;
  int32_T i;
  int32_T s_tmp_tmp;
  int8_T b_I[64];
  int8_T B_2[24];
  for (i = 0; i <= 10; i += 2) {
    // Sum: '<Root>/Sum10' incorporates:
    //   Inport: '<Root>/q_desired'
    //   Inport: '<Root>/q_observed'

    _mm_storeu_pd(&rtb_q_error[i], _mm_sub_pd(_mm_loadu_pd(&rtU.q_desired[i]),
      _mm_loadu_pd(&rtU.q_observed[i])));
  }

  // MATLAB Function: '<Root>/MATLAB Function3' incorporates:
  //   Constant: '<Root>/Constant27'
  //   Constant: '<Root>/Constant28'
  //   Constant: '<Root>/Constant29'
  //   Constant: '<Root>/Constant30'
  //   Sum: '<Root>/Sum10'

  std::memset(&T_Local_data[0], 0, 80U * sizeof(real_T));
  for (i = 0; i < 4; i++) {
    T_Local_tmp = i << 2;
    T_Local_data[(i << 2) + 0] = T0[T_Local_tmp];
    T_Local_data[((i << 2) + 0) + 1] = T0[T_Local_tmp + 1];
    T_Local_data[((i << 2) + 0) + 2] = T0[T_Local_tmp + 2];
    T_Local_data[((i << 2) + 0) + 3] = T0[T_Local_tmp + 3];
  }

  ang[6] = 0.0;
  ang[7] = 0.0;
  ang[2] = 0.0;
  ang[5] = 0.0;
  ang[8] = 1.0;
  c_b[0] = 0.0;
  c_b[1] = 0.0;
  c_b[2] = -0.02;
  for (N = 0; N < 4; N++) {
    e_b_idx_0 = rtb_q_error[3 * N + 2];
    s = std::sin(e_b_idx_0);
    e_b_idx_0 = std::cos(e_b_idx_0);
    z_tmp_0 = rtb_q_error[3 * N + 1];
    d_b_idx_1 = std::sin(z_tmp_0);
    z_tmp_0 = std::cos(z_tmp_0);
    d_b_idx_2 = rtb_q_error[3 * N];
    e_b_idx_1 = std::sin(d_b_idx_2);
    d_b_idx_2 = std::cos(d_b_idx_2);
    ang[0] = e_b_idx_0;
    ang[3] = -s;
    ang[1] = s;
    ang[4] = e_b_idx_0;
    z_tmp[0] = z_tmp_0;
    z_tmp[3] = 0.0;
    z_tmp[6] = d_b_idx_1;
    for (i = 0; i < 3; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        T_Local_tmp = 3 * T_Local_data_tmp + i;
        Rot[T_Local_tmp] = 0.0;
        Ji_size_idx_1_tmp = N << 4;
        Rot[T_Local_tmp] += ang[3 * T_Local_data_tmp] * T_Local_data[i +
          Ji_size_idx_1_tmp];
        Rot[T_Local_tmp] += ang[3 * T_Local_data_tmp + 1] * T_Local_data[(i +
          Ji_size_idx_1_tmp) + 4];
        Rot[T_Local_tmp] += ang[3 * T_Local_data_tmp + 2] * T_Local_data[(i +
          Ji_size_idx_1_tmp) + 8];
      }

      z_tmp[3 * i + 1] = g_b[i];
    }

    z_tmp[2] = -d_b_idx_1;
    z_tmp[5] = 0.0;
    z_tmp[8] = z_tmp_0;
    for (i = 0; i < 3; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        T_Local_tmp = 3 * T_Local_data_tmp + i;
        c_b_0[T_Local_tmp] = 0.0;
        c_b_0[T_Local_tmp] += z_tmp[3 * T_Local_data_tmp] * Rot[i];
        c_b_0[T_Local_tmp] += z_tmp[3 * T_Local_data_tmp + 1] * Rot[i + 3];
        c_b_0[T_Local_tmp] += z_tmp[3 * T_Local_data_tmp + 2] * Rot[i + 6];
      }

      c_b_1[3 * i] = h_b[i];
    }

    c_b_1[1] = 0.0;
    c_b_1[4] = d_b_idx_2;
    c_b_1[7] = -e_b_idx_1;
    c_b_1[2] = 0.0;
    c_b_1[5] = e_b_idx_1;
    c_b_1[8] = d_b_idx_2;
    for (i = 0; i < 3; i++) {
      z_tmp_0 = 0.0;
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        T_Local_tmp = 3 * T_Local_data_tmp + i;
        Rot[T_Local_tmp] = 0.0;
        Rot[T_Local_tmp] += c_b_1[3 * T_Local_data_tmp] * c_b_0[i];
        Rot[T_Local_tmp] += c_b_1[3 * T_Local_data_tmp + 1] * c_b_0[i + 3];
        Rot[T_Local_tmp] += c_b_1[3 * T_Local_data_tmp + 2] * c_b_0[i + 6];
        z_tmp_0 += Rot[T_Local_tmp] * c_b[T_Local_data_tmp];
      }

      T_Local[i] = T_Local_data[((N << 4) + i) + 12] + z_tmp_0;
    }

    for (i = 0; i < 3; i++) {
      T_Local_data_tmp = (N + 1) << 4;
      T_Local_data[(i << 2) + T_Local_data_tmp] = Rot[3 * i];
      T_Local_data[((i << 2) + T_Local_data_tmp) + 1] = Rot[3 * i + 1];
      T_Local_data[((i << 2) + T_Local_data_tmp) + 2] = Rot[3 * i + 2];
      T_Local_data[(i + T_Local_data_tmp) + 12] = T_Local[i];
    }

    T_Local_data_tmp = (N + 1) << 4;
    T_Local_data[3 + T_Local_data_tmp] = 0.0;
    T_Local_data[7 + T_Local_data_tmp] = 0.0;
    T_Local_data[11 + T_Local_data_tmp] = 0.0;
    T_Local_data[15 + T_Local_data_tmp] = 1.0;
  }

  std::memset(&rtDW.J_data[0], 0, 288U * sizeof(real_T));
  std::memset(&p_data[0], 0, 75U * sizeof(real_T));
  for (N = 0; N < 5; N++) {
    for (coffset = 0; coffset < 3; coffset++) {
      i = N * 3 + coffset;
      T_Local_tmp = N << 4;
      p_data[3 * i] = T_Local_data[12 + T_Local_tmp];
      p_data[1 + 3 * i] = T_Local_data[13 + T_Local_tmp];
      p_data[2 + 3 * i] = T_Local_data[14 + T_Local_tmp];
    }
  }

  std::memset(&z_data[0], 0, 36U * sizeof(real_T));
  ang[3] = 0.0;
  ang[5] = 0.0;
  ang[1] = 0.0;
  ang[4] = 1.0;
  ang[7] = 0.0;
  c_b_0[1] = 0.0;
  c_b_0[2] = 0.0;
  for (T_Local_tmp = 0; T_Local_tmp < 4; T_Local_tmp++) {
    N = T_Local_tmp * 3;
    d_b_idx_1 = rtb_q_error[3 * T_Local_tmp];
    s = std::sin(d_b_idx_1);
    e_b_idx_0 = std::cos(d_b_idx_1);
    for (i = 0; i < 3; i++) {
      Ji_size_idx_1_tmp = 3 * N + i;
      z_data[Ji_size_idx_1_tmp] = 0.0;
      T_Local_data_tmp = T_Local_tmp << 4;
      z_data[Ji_size_idx_1_tmp] += T_Local_data[i + T_Local_data_tmp];
      z_data[Ji_size_idx_1_tmp] += T_Local_data[(i + T_Local_data_tmp) + 4] *
        0.0;
      z_data[Ji_size_idx_1_tmp] += T_Local_data[(i + T_Local_data_tmp) + 8] *
        0.0;
      T_Local_data_tmp = h_b[i];
      c_b_1[3 * i] = T_Local_data_tmp;
      c_b[i] = T_Local_data_tmp;
    }

    c_b_1[1] = 0.0;
    c_b_1[4] = e_b_idx_0;
    c_b_1[7] = -s;
    c_b_1[2] = 0.0;
    c_b_1[5] = s;
    c_b_1[8] = e_b_idx_0;
    N = T_Local_tmp * 3 + 1;
    for (i = 0; i < 3; i++) {
      z_data[i + 3 * N] = 0.0;
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        coffset = 3 * T_Local_data_tmp + i;
        Rot[coffset] = 0.0;
        Ji_size_idx_1_tmp = T_Local_tmp << 4;
        Rot[coffset] += T_Local_data[(T_Local_data_tmp << 2) + Ji_size_idx_1_tmp]
          * c_b_1[i];
        Rot[coffset] += T_Local_data[((T_Local_data_tmp << 2) +
          Ji_size_idx_1_tmp) + 1] * c_b_1[i + 3];
        Rot[coffset] += T_Local_data[((T_Local_data_tmp << 2) +
          Ji_size_idx_1_tmp) + 2] * c_b_1[i + 6];
        Ji_size_idx_1_tmp = 3 * N + i;
        z_data[Ji_size_idx_1_tmp] += Rot[coffset] * static_cast<real_T>
          (g_b[T_Local_data_tmp]);
      }
    }

    e_b_idx_0 = rtb_q_error[N];
    s = std::sin(e_b_idx_0);
    e_b_idx_0 = std::cos(e_b_idx_0);
    z_tmp_0 = std::sin(d_b_idx_1);
    d_b_idx_1 = std::cos(d_b_idx_1);
    ang[0] = e_b_idx_0;
    ang[6] = s;
    ang[2] = -s;
    ang[8] = e_b_idx_0;
    c_b_0[0] = c_b[0];
    c_b_0[3] = c_b[1];
    c_b_0[6] = c_b[2];
    c_b_0[4] = d_b_idx_1;
    c_b_0[7] = -z_tmp_0;
    c_b_0[5] = z_tmp_0;
    c_b_0[8] = d_b_idx_1;
    N = T_Local_tmp * 3 + 2;
    for (i = 0; i < 3; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        coffset = 3 * T_Local_data_tmp + i;
        c_b_1[coffset] = 0.0;
        c_b_1[coffset] += c_b_0[3 * T_Local_data_tmp] * ang[i];
        c_b_1[coffset] += c_b_0[3 * T_Local_data_tmp + 1] * ang[i + 3];
        c_b_1[coffset] += c_b_0[3 * T_Local_data_tmp + 2] * ang[i + 6];
      }

      Ji_size_idx_1_tmp = 3 * N + i;
      z_data[Ji_size_idx_1_tmp] = 0.0;
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        coffset = 3 * T_Local_data_tmp + i;
        Rot[coffset] = 0.0;
        Rot[coffset] += T_Local_data[(T_Local_data_tmp << 2) + (T_Local_tmp << 4)]
          * c_b_1[i];
        Rot[coffset] += T_Local_data[((T_Local_data_tmp << 2) + (T_Local_tmp <<
          4)) + 1] * c_b_1[i + 3];
        Rot[coffset] += T_Local_data[((T_Local_data_tmp << 2) + (T_Local_tmp <<
          4)) + 2] * c_b_1[i + 6];
        z_data[Ji_size_idx_1_tmp] += Rot[coffset] * static_cast<real_T>
          (r[T_Local_data_tmp]);
      }
    }
  }

  for (T_Local_tmp = 1; T_Local_tmp - 1 < 4; T_Local_tmp++) {
    Ji_size_idx_1_tmp = 3 * T_Local_tmp;
    i = 3 * T_Local_tmp * 6 - 1;
    if (i >= 0) {
      std::memset(&Ji_data[0], 0, (i + 1) * sizeof(real_T));
    }

    if (T_Local_tmp - 1 >= 0) {
      b_b_tmp = Ji_size_idx_1_tmp;
      b = Ji_size_idx_1_tmp;
    }

    for (N = 0; N < T_Local_tmp; N++) {
      T_Local_data_tmp = N * 3;
      coffset = T_Local_data_tmp;
      i = (N + 1) * 3;
      if (T_Local_data_tmp + 1 > i) {
        coffset = 0;
        boffset = 0;
      } else {
        boffset = i;
      }

      c_b_tmp = 3 * T_Local_data_tmp;
      c_b[0] = p_data[3 * b_b_tmp] - p_data[c_b_tmp];
      s_tmp_tmp = (T_Local_data_tmp + 1) * 3;
      s = p_data[3 * b] - p_data[s_tmp_tmp];
      e_b_idx_0_tmp_tmp = (T_Local_data_tmp + 2) * 3;
      e_b_idx_0 = p_data[3 * b] - p_data[e_b_idx_0_tmp_tmp];
      z[3] = z_data[c_b_tmp];
      z[9] = z_data[s_tmp_tmp];
      z[15] = z_data[e_b_idx_0_tmp_tmp];
      c_b_tmp = 3 * T_Local_data_tmp + 1;
      c_b[1] = p_data[3 * b_b_tmp + 1] - p_data[c_b_tmp];
      d_b_idx_1 = p_data[3 * b + 1] - p_data[1 + s_tmp_tmp];
      e_b_idx_1 = p_data[3 * b + 1] - p_data[1 + e_b_idx_0_tmp_tmp];
      z[4] = z_data[c_b_tmp];
      z[10] = z_data[1 + s_tmp_tmp];
      z[16] = z_data[1 + e_b_idx_0_tmp_tmp];
      c_b_tmp = 3 * T_Local_data_tmp + 2;
      c_b[2] = p_data[3 * b_b_tmp + 2] - p_data[c_b_tmp];
      d_b_idx_2 = p_data[3 * b + 2] - p_data[2 + s_tmp_tmp];
      e_b_idx_2 = p_data[3 * b + 2] - p_data[2 + e_b_idx_0_tmp_tmp];
      z[5] = z_data[c_b_tmp];
      z[11] = z_data[2 + s_tmp_tmp];
      z[17] = z_data[2 + e_b_idx_0_tmp_tmp];
      z_tmp_0 = z_data[N * 3 * 3 + 2];
      z_tmp_2 = z_data[N * 3 * 3 + 1];
      z[0] = z_tmp_2 * c_b[2] - z_tmp_0 * c_b[1];
      z_tmp_1 = z_data[N * 3 * 3];
      z[1] = z_tmp_0 * c_b[0] - z_tmp_1 * c_b[2];
      z[2] = z_tmp_1 * c_b[1] - z_tmp_2 * c_b[0];
      z_tmp_0 = z_data[(N * 3 + 1) * 3 + 2];
      z_tmp_2 = z_data[(N * 3 + 1) * 3 + 1];
      z[6] = z_tmp_2 * d_b_idx_2 - z_tmp_0 * d_b_idx_1;
      z_tmp_1 = z_data[(N * 3 + 1) * 3];
      z[7] = z_tmp_0 * s - z_tmp_1 * d_b_idx_2;
      z[8] = z_tmp_1 * d_b_idx_1 - z_tmp_2 * s;
      T_Local_data_tmp = N * 3 + 2;
      z_tmp_0 = z_data[3 * T_Local_data_tmp + 2];
      z_tmp_2 = z_data[3 * T_Local_data_tmp + 1];
      z[12] = z_tmp_2 * e_b_idx_2 - z_tmp_0 * e_b_idx_1;
      z_tmp_1 = z_data[3 * T_Local_data_tmp];
      z[13] = z_tmp_0 * e_b_idx_0 - z_tmp_1 * e_b_idx_2;
      z[14] = z_tmp_1 * e_b_idx_1 - z_tmp_2 * e_b_idx_0;
      c_b_tmp = boffset - coffset;
      for (i = 0; i < c_b_tmp; i++) {
        for (T_Local_data_tmp = 0; T_Local_data_tmp < 6; T_Local_data_tmp++) {
          Ji_data[T_Local_data_tmp + 6 * (coffset + i)] = z[6 * i +
            T_Local_data_tmp];
        }
      }
    }

    N = (T_Local_tmp - 1) * 6;
    if (N + 1 > T_Local_tmp * 6) {
      N = 0;
    }

    for (i = 0; i < Ji_size_idx_1_tmp; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 6; T_Local_data_tmp++) {
        rtDW.J_data[(N + T_Local_data_tmp) + 24 * i] = Ji_data[6 * i +
          T_Local_data_tmp];
      }
    }
  }

  std::memset(&M_deformed[0], 0, 12U * sizeof(real_T));
  for (N = 0; N < 4; N++) {
    for (i = 0; i <= 0; i += 2) {
      T_Local_data_tmp = 3 * N + i;
      _mm_storeu_pd(&M_deformed[T_Local_data_tmp], _mm_set1_pd(0.0));
      T_Local_tmp = (N + 1) << 4;
      tmp = _mm_loadu_pd(&T_Local_data[i + T_Local_tmp]);
      tmp_0 = _mm_loadu_pd(&M_deformed[T_Local_data_tmp]);
      _mm_storeu_pd(&M_deformed[T_Local_data_tmp], _mm_add_pd(tmp_0, _mm_mul_pd
        (tmp, _mm_set1_pd(rtConstP.pooled2[3 * N]))));
      tmp = _mm_loadu_pd(&T_Local_data[(((N + 1) << 4) + i) + 4]);
      tmp_0 = _mm_loadu_pd(&M_deformed[T_Local_data_tmp]);
      _mm_storeu_pd(&M_deformed[T_Local_data_tmp], _mm_add_pd(_mm_mul_pd
        (_mm_set1_pd(rtConstP.pooled2[3 * N + 1]), tmp), tmp_0));
      tmp = _mm_loadu_pd(&T_Local_data[(i + T_Local_tmp) + 8]);
      tmp_0 = _mm_loadu_pd(&M_deformed[T_Local_data_tmp]);
      _mm_storeu_pd(&M_deformed[T_Local_data_tmp], _mm_add_pd(_mm_mul_pd
        (_mm_set1_pd(rtConstP.pooled2[3 * N + 2]), tmp), tmp_0));
    }

    for (i = 2; i < 3; i++) {
      b_b_tmp = 3 * N + i;
      M_deformed[b_b_tmp] = 0.0;
      M_deformed[b_b_tmp] += T_Local_data[((N + 1) << 4) + i] *
        rtConstP.pooled2[3 * N];
      T_Local_tmp = (N + 1) << 4;
      M_deformed[b_b_tmp] += rtConstP.pooled2[3 * N + 1] * T_Local_data[(i +
        T_Local_tmp) + 4];
      M_deformed[b_b_tmp] += rtConstP.pooled2[3 * N + 2] * T_Local_data[(i +
        T_Local_tmp) + 8];
    }
  }

  std::memset(&varargin_1[0], 0, 48U * sizeof(real_T));
  varargin_1[0] = M_deformed[0];
  varargin_1[6] = M_deformed[1];
  varargin_1[12] = M_deformed[2];
  varargin_1[18] = 0.0;
  varargin_1[24] = 0.0;
  varargin_1[1] = 0.0;
  varargin_1[7] = M_deformed[0];
  varargin_1[13] = 0.0;
  varargin_1[19] = M_deformed[1];
  varargin_1[25] = M_deformed[2];
  varargin_1[2] = -M_deformed[2];
  varargin_1[8] = 0.0;
  varargin_1[14] = M_deformed[0];
  varargin_1[20] = -M_deformed[2];
  varargin_1[26] = M_deformed[1];
  varargin_1[33] = 0.0;
  varargin_1[39] = -M_deformed[2];
  varargin_1[45] = M_deformed[1];
  varargin_1[34] = M_deformed[2];
  varargin_1[40] = 0.0;
  varargin_1[46] = -M_deformed[0];
  varargin_1[35] = -M_deformed[1];
  varargin_1[41] = M_deformed[0];
  varargin_1[47] = 0.0;
  std::memset(&varargin_2[0], 0, 48U * sizeof(real_T));
  varargin_2[0] = M_deformed[3];
  varargin_2[6] = M_deformed[4];
  varargin_2[12] = M_deformed[5];
  varargin_2[18] = 0.0;
  varargin_2[24] = 0.0;
  varargin_2[1] = 0.0;
  varargin_2[7] = M_deformed[3];
  varargin_2[13] = 0.0;
  varargin_2[19] = M_deformed[4];
  varargin_2[25] = M_deformed[5];
  varargin_2[2] = -M_deformed[5];
  varargin_2[8] = 0.0;
  varargin_2[14] = M_deformed[3];
  varargin_2[20] = -M_deformed[5];
  varargin_2[26] = M_deformed[4];
  varargin_2[33] = 0.0;
  varargin_2[39] = -M_deformed[5];
  varargin_2[45] = M_deformed[4];
  varargin_2[34] = M_deformed[5];
  varargin_2[40] = 0.0;
  varargin_2[46] = -M_deformed[3];
  varargin_2[35] = -M_deformed[4];
  varargin_2[41] = M_deformed[3];
  varargin_2[47] = 0.0;
  std::memset(&varargin_3[0], 0, 48U * sizeof(real_T));
  varargin_3[0] = M_deformed[6];
  varargin_3[6] = M_deformed[7];
  varargin_3[12] = M_deformed[8];
  varargin_3[18] = 0.0;
  varargin_3[24] = 0.0;
  varargin_3[1] = 0.0;
  varargin_3[7] = M_deformed[6];
  varargin_3[13] = 0.0;
  varargin_3[19] = M_deformed[7];
  varargin_3[25] = M_deformed[8];
  varargin_3[2] = -M_deformed[8];
  varargin_3[8] = 0.0;
  varargin_3[14] = M_deformed[6];
  varargin_3[20] = -M_deformed[8];
  varargin_3[26] = M_deformed[7];
  varargin_3[33] = 0.0;
  varargin_3[39] = -M_deformed[8];
  varargin_3[45] = M_deformed[7];
  varargin_3[34] = M_deformed[8];
  varargin_3[40] = 0.0;
  varargin_3[46] = -M_deformed[6];
  varargin_3[35] = -M_deformed[7];
  varargin_3[41] = M_deformed[6];
  varargin_3[47] = 0.0;
  std::memset(&varargin_4[0], 0, 48U * sizeof(real_T));
  varargin_4[0] = M_deformed[9];
  varargin_4[6] = M_deformed[10];
  varargin_4[12] = M_deformed[11];
  varargin_4[18] = 0.0;
  varargin_4[24] = 0.0;
  varargin_4[1] = 0.0;
  varargin_4[7] = M_deformed[9];
  varargin_4[13] = 0.0;
  varargin_4[19] = M_deformed[10];
  varargin_4[25] = M_deformed[11];
  varargin_4[2] = -M_deformed[11];
  varargin_4[8] = 0.0;
  varargin_4[14] = M_deformed[9];
  varargin_4[20] = -M_deformed[11];
  varargin_4[26] = M_deformed[10];
  varargin_4[33] = 0.0;
  varargin_4[39] = -M_deformed[11];
  varargin_4[45] = M_deformed[10];
  varargin_4[34] = M_deformed[11];
  varargin_4[40] = 0.0;
  varargin_4[46] = -M_deformed[9];
  varargin_4[35] = -M_deformed[10];
  varargin_4[41] = M_deformed[9];
  varargin_4[47] = 0.0;
  std::memset(&rtDW.b_b[0], 0, 768U * sizeof(real_T));
  for (i = 0; i < 8; i++) {
    for (T_Local_data_tmp = 0; T_Local_data_tmp < 6; T_Local_data_tmp++) {
      b_b_tmp = 6 * i + T_Local_data_tmp;
      rtDW.b_b[T_Local_data_tmp + 24 * i] = varargin_1[b_b_tmp];
      rtDW.b_b[(T_Local_data_tmp + 24 * (i + 8)) + 6] = varargin_2[b_b_tmp];
      rtDW.b_b[(T_Local_data_tmp + 24 * (i + 16)) + 12] = varargin_3[b_b_tmp];
      rtDW.b_b[(T_Local_data_tmp + 24 * (i + 24)) + 18] = varargin_4[b_b_tmp];
    }
  }

  decom_size[0] = 32;
  decom_size[1] = 8;
  std::memset(&rtDW.decom_data[0], 0, sizeof(real_T) << 8U);
  for (N = 0; N < 4; N++) {
    std::memset(&b_I[0], 0, sizeof(int8_T) << 6U);
    for (T_Local_tmp = 0; T_Local_tmp < 8; T_Local_tmp++) {
      b_I[T_Local_tmp + (T_Local_tmp << 3)] = 1;
    }

    b_b_tmp = N << 3;
    for (i = 0; i < 8; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 8; T_Local_data_tmp++) {
        rtDW.decom_data[(T_Local_data_tmp + b_b_tmp) + (i << 5)] = b_I[(i << 3)
          + T_Local_data_tmp];
      }
    }
  }

  for (i = 0; i < 24; i++) {
    B_2[i] = 0;
  }

  for (i = 0; i < 3; i++) {
    b_b_tmp = i << 3;
    B_2[b_b_tmp + 5] = t[3 * i];
    B_2[b_b_tmp + 6] = t[3 * i + 1];
    B_2[b_b_tmp + 7] = t[3 * i + 2];
  }

  std::memset(&rtb_U[0], 0, sizeof(real_T) << 3U);
  J_size[0] = 12;
  J_size[1] = 24;
  for (i = 0; i < 24; i++) {
    for (T_Local_data_tmp = 0; T_Local_data_tmp < 12; T_Local_data_tmp++) {
      rtDW.J_data_m[T_Local_data_tmp + 12 * i] = rtDW.J_data[24 *
        T_Local_data_tmp + i];
    }
  }

  mtimes(rtDW.J_data_m, J_size, rtDW.b_b, rtDW.tmp_data, tmp_size);
  mtimes_e(rtDW.tmp_data, tmp_size, rtDW.decom_data, decom_size, A_data, A_size);
  N = A_size[0];
  y_size[0] = A_size[0];
  y_size[1] = 3;
  for (T_Local_tmp = 0; T_Local_tmp < 3; T_Local_tmp++) {
    coffset = T_Local_tmp * N;
    boffset = T_Local_tmp << 3;
    for (i = 0; i < N; i++) {
      s = 0.0;
      for (b_b_tmp = 0; b_b_tmp < 8; b_b_tmp++) {
        s += A_data[b_b_tmp * A_size[0] + i] * static_cast<real_T>(B_2[boffset +
          b_b_tmp]);
      }

      y_data[coffset + i] = s;
    }
  }

  pinv(y_data, y_size, z_data, tmp_size);
  for (i = 0; i < 12; i++) {
    for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
      b_b_tmp = 3 * i + T_Local_data_tmp;
      b_A[b_b_tmp] = 0.0;
      for (b = 0; b < 12; b++) {
        b_A[b_b_tmp] += z_data[3 * b + T_Local_data_tmp] * rtConstP.pooled3[12 *
          i + b];
      }
    }
  }

  for (T_Local_tmp = 0; T_Local_tmp < 3; T_Local_tmp++) {
    s = 0.0;
    for (N = 0; N < 12; N++) {
      s += b_A[N * 3 + T_Local_tmp] * rtb_q_error[N];
    }

    rtb_U[T_Local_tmp + 5] = s;
  }

  // End of MATLAB Function: '<Root>/MATLAB Function3'

  // MATLAB Function: '<Root>/MATLAB Function2' incorporates:
  //   Constant: '<Root>/Constant22'
  //   Constant: '<Root>/Constant23'
  //   Constant: '<Root>/Constant24'
  //   Constant: '<Root>/Constant25'
  //   Inport: '<Root>/q_desired'

  std::memset(&T_Local_data[0], 0, 80U * sizeof(real_T));
  for (i = 0; i < 4; i++) {
    T_Local_tmp = i << 2;
    T_Local_data[(i << 2) + 0] = T0[T_Local_tmp];
    T_Local_data[((i << 2) + 0) + 1] = T0[T_Local_tmp + 1];
    T_Local_data[((i << 2) + 0) + 2] = T0[T_Local_tmp + 2];
    T_Local_data[((i << 2) + 0) + 3] = T0[T_Local_tmp + 3];
  }

  ang[6] = 0.0;
  ang[7] = 0.0;
  ang[2] = 0.0;
  ang[5] = 0.0;
  ang[8] = 1.0;
  c_b[0] = 0.0;
  c_b[1] = 0.0;
  c_b[2] = -0.02;
  for (N = 0; N < 4; N++) {
    e_b_idx_0 = rtU.q_desired[3 * N + 2];
    s = std::sin(e_b_idx_0);
    e_b_idx_0 = std::cos(e_b_idx_0);
    z_tmp_0 = rtU.q_desired[3 * N + 1];
    d_b_idx_1 = std::sin(z_tmp_0);
    z_tmp_0 = std::cos(z_tmp_0);
    d_b_idx_2 = rtU.q_desired[3 * N];
    e_b_idx_1 = std::sin(d_b_idx_2);
    d_b_idx_2 = std::cos(d_b_idx_2);
    ang[0] = e_b_idx_0;
    ang[3] = -s;
    ang[1] = s;
    ang[4] = e_b_idx_0;
    z_tmp[0] = z_tmp_0;
    z_tmp[3] = 0.0;
    z_tmp[6] = d_b_idx_1;
    for (i = 0; i < 3; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        T_Local_tmp = 3 * T_Local_data_tmp + i;
        Rot[T_Local_tmp] = 0.0;
        Ji_size_idx_1_tmp = N << 4;
        Rot[T_Local_tmp] += ang[3 * T_Local_data_tmp] * T_Local_data[i +
          Ji_size_idx_1_tmp];
        Rot[T_Local_tmp] += ang[3 * T_Local_data_tmp + 1] * T_Local_data[(i +
          Ji_size_idx_1_tmp) + 4];
        Rot[T_Local_tmp] += ang[3 * T_Local_data_tmp + 2] * T_Local_data[(i +
          Ji_size_idx_1_tmp) + 8];
      }

      z_tmp[3 * i + 1] = g_b[i];
    }

    z_tmp[2] = -d_b_idx_1;
    z_tmp[5] = 0.0;
    z_tmp[8] = z_tmp_0;
    for (i = 0; i < 3; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        T_Local_tmp = 3 * T_Local_data_tmp + i;
        c_b_0[T_Local_tmp] = 0.0;
        c_b_0[T_Local_tmp] += z_tmp[3 * T_Local_data_tmp] * Rot[i];
        c_b_0[T_Local_tmp] += z_tmp[3 * T_Local_data_tmp + 1] * Rot[i + 3];
        c_b_0[T_Local_tmp] += z_tmp[3 * T_Local_data_tmp + 2] * Rot[i + 6];
      }

      c_b_1[3 * i] = h_b[i];
    }

    c_b_1[1] = 0.0;
    c_b_1[4] = d_b_idx_2;
    c_b_1[7] = -e_b_idx_1;
    c_b_1[2] = 0.0;
    c_b_1[5] = e_b_idx_1;
    c_b_1[8] = d_b_idx_2;
    for (i = 0; i < 3; i++) {
      z_tmp_0 = 0.0;
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        T_Local_tmp = 3 * T_Local_data_tmp + i;
        Rot[T_Local_tmp] = 0.0;
        Rot[T_Local_tmp] += c_b_1[3 * T_Local_data_tmp] * c_b_0[i];
        Rot[T_Local_tmp] += c_b_1[3 * T_Local_data_tmp + 1] * c_b_0[i + 3];
        Rot[T_Local_tmp] += c_b_1[3 * T_Local_data_tmp + 2] * c_b_0[i + 6];
        z_tmp_0 += Rot[T_Local_tmp] * c_b[T_Local_data_tmp];
      }

      T_Local[i] = T_Local_data[((N << 4) + i) + 12] + z_tmp_0;
    }

    for (i = 0; i < 3; i++) {
      T_Local_data_tmp = (N + 1) << 4;
      T_Local_data[(i << 2) + T_Local_data_tmp] = Rot[3 * i];
      T_Local_data[((i << 2) + T_Local_data_tmp) + 1] = Rot[3 * i + 1];
      T_Local_data[((i << 2) + T_Local_data_tmp) + 2] = Rot[3 * i + 2];
      T_Local_data[(i + T_Local_data_tmp) + 12] = T_Local[i];
    }

    T_Local_data_tmp = (N + 1) << 4;
    T_Local_data[3 + T_Local_data_tmp] = 0.0;
    T_Local_data[7 + T_Local_data_tmp] = 0.0;
    T_Local_data[11 + T_Local_data_tmp] = 0.0;
    T_Local_data[15 + T_Local_data_tmp] = 1.0;
  }

  std::memset(&rtDW.J_data[0], 0, 288U * sizeof(real_T));
  std::memset(&p_data[0], 0, 75U * sizeof(real_T));
  for (N = 0; N < 5; N++) {
    for (coffset = 0; coffset < 3; coffset++) {
      i = N * 3 + coffset;
      T_Local_tmp = N << 4;
      p_data[3 * i] = T_Local_data[12 + T_Local_tmp];
      p_data[1 + 3 * i] = T_Local_data[13 + T_Local_tmp];
      p_data[2 + 3 * i] = T_Local_data[14 + T_Local_tmp];
    }
  }

  std::memset(&z_data[0], 0, 36U * sizeof(real_T));
  ang[3] = 0.0;
  ang[5] = 0.0;
  ang[1] = 0.0;
  ang[4] = 1.0;
  ang[7] = 0.0;
  c_b_0[1] = 0.0;
  c_b_0[2] = 0.0;
  for (T_Local_tmp = 0; T_Local_tmp < 4; T_Local_tmp++) {
    b_b_tmp = T_Local_tmp * 3;
    d_b_idx_1 = rtU.q_desired[3 * T_Local_tmp];
    s = std::sin(d_b_idx_1);
    e_b_idx_0 = std::cos(d_b_idx_1);
    for (i = 0; i < 3; i++) {
      Ji_size_idx_1_tmp = 3 * b_b_tmp + i;
      z_data[Ji_size_idx_1_tmp] = 0.0;
      T_Local_data_tmp = T_Local_tmp << 4;
      z_data[Ji_size_idx_1_tmp] += T_Local_data[i + T_Local_data_tmp];
      z_data[Ji_size_idx_1_tmp] += T_Local_data[(i + T_Local_data_tmp) + 4] *
        0.0;
      z_data[Ji_size_idx_1_tmp] += T_Local_data[(i + T_Local_data_tmp) + 8] *
        0.0;
      T_Local_data_tmp = h_b[i];
      c_b_1[3 * i] = T_Local_data_tmp;
      c_b[i] = T_Local_data_tmp;
    }

    c_b_1[1] = 0.0;
    c_b_1[4] = e_b_idx_0;
    c_b_1[7] = -s;
    c_b_1[2] = 0.0;
    c_b_1[5] = s;
    c_b_1[8] = e_b_idx_0;
    N = T_Local_tmp * 3 + 1;
    for (i = 0; i < 3; i++) {
      z_data[i + 3 * N] = 0.0;
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        coffset = 3 * T_Local_data_tmp + i;
        Rot[coffset] = 0.0;
        Ji_size_idx_1_tmp = T_Local_tmp << 4;
        Rot[coffset] += T_Local_data[(T_Local_data_tmp << 2) + Ji_size_idx_1_tmp]
          * c_b_1[i];
        Rot[coffset] += T_Local_data[((T_Local_data_tmp << 2) +
          Ji_size_idx_1_tmp) + 1] * c_b_1[i + 3];
        Rot[coffset] += T_Local_data[((T_Local_data_tmp << 2) +
          Ji_size_idx_1_tmp) + 2] * c_b_1[i + 6];
        Ji_size_idx_1_tmp = 3 * N + i;
        z_data[Ji_size_idx_1_tmp] += Rot[coffset] * static_cast<real_T>
          (g_b[T_Local_data_tmp]);
      }
    }

    e_b_idx_0 = rtU.q_desired[N];
    s = std::sin(e_b_idx_0);
    e_b_idx_0 = std::cos(e_b_idx_0);
    z_tmp_0 = std::sin(d_b_idx_1);
    d_b_idx_1 = std::cos(d_b_idx_1);
    ang[0] = e_b_idx_0;
    ang[6] = s;
    ang[2] = -s;
    ang[8] = e_b_idx_0;
    c_b_0[0] = c_b[0];
    c_b_0[3] = c_b[1];
    c_b_0[6] = c_b[2];
    c_b_0[4] = d_b_idx_1;
    c_b_0[7] = -z_tmp_0;
    c_b_0[5] = z_tmp_0;
    c_b_0[8] = d_b_idx_1;
    b_b_tmp = T_Local_tmp * 3 + 2;
    for (i = 0; i < 3; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        coffset = 3 * T_Local_data_tmp + i;
        c_b_1[coffset] = 0.0;
        c_b_1[coffset] += c_b_0[3 * T_Local_data_tmp] * ang[i];
        c_b_1[coffset] += c_b_0[3 * T_Local_data_tmp + 1] * ang[i + 3];
        c_b_1[coffset] += c_b_0[3 * T_Local_data_tmp + 2] * ang[i + 6];
      }

      Ji_size_idx_1_tmp = 3 * b_b_tmp + i;
      z_data[Ji_size_idx_1_tmp] = 0.0;
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
        coffset = 3 * T_Local_data_tmp + i;
        Rot[coffset] = 0.0;
        Rot[coffset] += T_Local_data[(T_Local_data_tmp << 2) + (T_Local_tmp << 4)]
          * c_b_1[i];
        Rot[coffset] += T_Local_data[((T_Local_data_tmp << 2) + (T_Local_tmp <<
          4)) + 1] * c_b_1[i + 3];
        Rot[coffset] += T_Local_data[((T_Local_data_tmp << 2) + (T_Local_tmp <<
          4)) + 2] * c_b_1[i + 6];
        z_data[Ji_size_idx_1_tmp] += Rot[coffset] * static_cast<real_T>
          (r[T_Local_data_tmp]);
      }
    }
  }

  for (T_Local_tmp = 1; T_Local_tmp - 1 < 4; T_Local_tmp++) {
    Ji_size_idx_1_tmp = 3 * T_Local_tmp;
    i = 3 * T_Local_tmp * 6 - 1;
    if (i >= 0) {
      std::memset(&Ji_data[0], 0, (i + 1) * sizeof(real_T));
    }

    if (T_Local_tmp - 1 >= 0) {
      b_0 = Ji_size_idx_1_tmp;
    }

    for (N = 0; N < T_Local_tmp; N++) {
      b_b_tmp = N * 3;
      boffset = b_b_tmp;
      coffset = (N + 1) * 3;
      if (b_b_tmp + 1 > coffset) {
        boffset = 0;
        i = 0;
      } else {
        i = coffset;
      }

      c_b_tmp = 3 * b_b_tmp;
      c_b[0] = p_data[3 * b_0] - p_data[c_b_tmp];
      s_tmp_tmp = (b_b_tmp + 1) * 3;
      s = p_data[3 * b_0] - p_data[s_tmp_tmp];
      e_b_idx_0_tmp_tmp = (b_b_tmp + 2) * 3;
      e_b_idx_0 = p_data[3 * b_0] - p_data[e_b_idx_0_tmp_tmp];
      z[3] = z_data[c_b_tmp];
      z[9] = z_data[s_tmp_tmp];
      z[15] = z_data[e_b_idx_0_tmp_tmp];
      c_b_tmp = 3 * b_b_tmp + 1;
      c_b[1] = p_data[3 * b_0 + 1] - p_data[c_b_tmp];
      d_b_idx_1 = p_data[3 * b_0 + 1] - p_data[1 + s_tmp_tmp];
      e_b_idx_1 = p_data[3 * b_0 + 1] - p_data[1 + e_b_idx_0_tmp_tmp];
      z[4] = z_data[c_b_tmp];
      z[10] = z_data[1 + s_tmp_tmp];
      z[16] = z_data[1 + e_b_idx_0_tmp_tmp];
      c_b[2] = p_data[3 * b_0 + 2] - p_data[3 * b_b_tmp + 2];
      d_b_idx_2 = p_data[3 * b_0 + 2] - p_data[2 + s_tmp_tmp];
      e_b_idx_2 = p_data[3 * b_0 + 2] - p_data[2 + e_b_idx_0_tmp_tmp];
      z[5] = z_data[3 * b_b_tmp + 2];
      z[11] = z_data[(b_b_tmp + 1) * 3 + 2];
      z[17] = z_data[(b_b_tmp + 2) * 3 + 2];
      b_b_tmp = N * 3 * 3;
      z_tmp_0 = z_data[2 + b_b_tmp];
      z_tmp_2 = z_data[1 + b_b_tmp];
      z[0] = z_tmp_2 * c_b[2] - z_tmp_0 * c_b[1];
      z_tmp_1 = z_data[b_b_tmp];
      z[1] = z_tmp_0 * c_b[0] - z_tmp_1 * c_b[2];
      z[2] = z_tmp_1 * c_b[1] - z_tmp_2 * c_b[0];
      b_b_tmp = (N * 3 + 1) * 3;
      z_tmp_0 = z_data[2 + b_b_tmp];
      z_tmp_2 = z_data[1 + b_b_tmp];
      z[6] = z_tmp_2 * d_b_idx_2 - z_tmp_0 * d_b_idx_1;
      z_tmp_1 = z_data[b_b_tmp];
      z[7] = z_tmp_0 * s - z_tmp_1 * d_b_idx_2;
      z[8] = z_tmp_1 * d_b_idx_1 - z_tmp_2 * s;
      T_Local_data_tmp = N * 3 + 2;
      z_tmp_0 = z_data[3 * T_Local_data_tmp + 2];
      z_tmp_2 = z_data[3 * T_Local_data_tmp + 1];
      z[12] = z_tmp_2 * e_b_idx_2 - z_tmp_0 * e_b_idx_1;
      z_tmp_1 = z_data[3 * T_Local_data_tmp];
      z[13] = z_tmp_0 * e_b_idx_0 - z_tmp_1 * e_b_idx_2;
      z[14] = z_tmp_1 * e_b_idx_1 - z_tmp_2 * e_b_idx_0;
      c_b_tmp = i - boffset;
      for (i = 0; i < c_b_tmp; i++) {
        for (T_Local_data_tmp = 0; T_Local_data_tmp < 6; T_Local_data_tmp++) {
          Ji_data[T_Local_data_tmp + 6 * (boffset + i)] = z[6 * i +
            T_Local_data_tmp];
        }
      }
    }

    coffset = (T_Local_tmp - 1) * 6;
    if (coffset + 1 > T_Local_tmp * 6) {
      coffset = 0;
    }

    for (i = 0; i < Ji_size_idx_1_tmp; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 6; T_Local_data_tmp++) {
        rtDW.J_data[(coffset + T_Local_data_tmp) + 24 * i] = Ji_data[6 * i +
          T_Local_data_tmp];
      }
    }
  }

  std::memset(&M_deformed[0], 0, 12U * sizeof(real_T));
  for (N = 0; N < 4; N++) {
    for (i = 0; i <= 0; i += 2) {
      T_Local_data_tmp = 3 * N + i;
      _mm_storeu_pd(&M_deformed[T_Local_data_tmp], _mm_set1_pd(0.0));
      tmp = _mm_loadu_pd(&T_Local_data[((N + 1) << 4) + i]);
      tmp_0 = _mm_loadu_pd(&M_deformed[T_Local_data_tmp]);
      _mm_storeu_pd(&M_deformed[T_Local_data_tmp], _mm_add_pd(tmp_0, _mm_mul_pd
        (tmp, _mm_set1_pd(rtConstP.pooled2[3 * N]))));
      tmp = _mm_loadu_pd(&T_Local_data[(((N + 1) << 4) + i) + 4]);
      tmp_0 = _mm_loadu_pd(&M_deformed[T_Local_data_tmp]);
      _mm_storeu_pd(&M_deformed[T_Local_data_tmp], _mm_add_pd(_mm_mul_pd
        (_mm_set1_pd(rtConstP.pooled2[3 * N + 1]), tmp), tmp_0));
      tmp = _mm_loadu_pd(&T_Local_data[(((N + 1) << 4) + i) + 8]);
      tmp_0 = _mm_loadu_pd(&M_deformed[T_Local_data_tmp]);
      _mm_storeu_pd(&M_deformed[T_Local_data_tmp], _mm_add_pd(_mm_mul_pd
        (_mm_set1_pd(rtConstP.pooled2[3 * N + 2]), tmp), tmp_0));
    }

    for (i = 2; i < 3; i++) {
      b_b_tmp = 3 * N + i;
      M_deformed[b_b_tmp] = 0.0;
      M_deformed[b_b_tmp] += T_Local_data[((N + 1) << 4) + i] *
        rtConstP.pooled2[3 * N];
      T_Local_tmp = (N + 1) << 4;
      M_deformed[b_b_tmp] += rtConstP.pooled2[3 * N + 1] * T_Local_data[(i +
        T_Local_tmp) + 4];
      M_deformed[b_b_tmp] += rtConstP.pooled2[3 * N + 2] * T_Local_data[(i +
        T_Local_tmp) + 8];
    }
  }

  std::memset(&varargin_1[0], 0, 48U * sizeof(real_T));
  varargin_1[0] = M_deformed[0];
  varargin_1[6] = M_deformed[1];
  varargin_1[12] = M_deformed[2];
  varargin_1[18] = 0.0;
  varargin_1[24] = 0.0;
  varargin_1[1] = 0.0;
  varargin_1[7] = M_deformed[0];
  varargin_1[13] = 0.0;
  varargin_1[19] = M_deformed[1];
  varargin_1[25] = M_deformed[2];
  varargin_1[2] = -M_deformed[2];
  varargin_1[8] = 0.0;
  varargin_1[14] = M_deformed[0];
  varargin_1[20] = -M_deformed[2];
  varargin_1[26] = M_deformed[1];
  varargin_1[33] = 0.0;
  varargin_1[39] = -M_deformed[2];
  varargin_1[45] = M_deformed[1];
  varargin_1[34] = M_deformed[2];
  varargin_1[40] = 0.0;
  varargin_1[46] = -M_deformed[0];
  varargin_1[35] = -M_deformed[1];
  varargin_1[41] = M_deformed[0];
  varargin_1[47] = 0.0;
  std::memset(&varargin_2[0], 0, 48U * sizeof(real_T));
  varargin_2[0] = M_deformed[3];
  varargin_2[6] = M_deformed[4];
  varargin_2[12] = M_deformed[5];
  varargin_2[18] = 0.0;
  varargin_2[24] = 0.0;
  varargin_2[1] = 0.0;
  varargin_2[7] = M_deformed[3];
  varargin_2[13] = 0.0;
  varargin_2[19] = M_deformed[4];
  varargin_2[25] = M_deformed[5];
  varargin_2[2] = -M_deformed[5];
  varargin_2[8] = 0.0;
  varargin_2[14] = M_deformed[3];
  varargin_2[20] = -M_deformed[5];
  varargin_2[26] = M_deformed[4];
  varargin_2[33] = 0.0;
  varargin_2[39] = -M_deformed[5];
  varargin_2[45] = M_deformed[4];
  varargin_2[34] = M_deformed[5];
  varargin_2[40] = 0.0;
  varargin_2[46] = -M_deformed[3];
  varargin_2[35] = -M_deformed[4];
  varargin_2[41] = M_deformed[3];
  varargin_2[47] = 0.0;
  std::memset(&varargin_3[0], 0, 48U * sizeof(real_T));
  varargin_3[0] = M_deformed[6];
  varargin_3[6] = M_deformed[7];
  varargin_3[12] = M_deformed[8];
  varargin_3[18] = 0.0;
  varargin_3[24] = 0.0;
  varargin_3[1] = 0.0;
  varargin_3[7] = M_deformed[6];
  varargin_3[13] = 0.0;
  varargin_3[19] = M_deformed[7];
  varargin_3[25] = M_deformed[8];
  varargin_3[2] = -M_deformed[8];
  varargin_3[8] = 0.0;
  varargin_3[14] = M_deformed[6];
  varargin_3[20] = -M_deformed[8];
  varargin_3[26] = M_deformed[7];
  varargin_3[33] = 0.0;
  varargin_3[39] = -M_deformed[8];
  varargin_3[45] = M_deformed[7];
  varargin_3[34] = M_deformed[8];
  varargin_3[40] = 0.0;
  varargin_3[46] = -M_deformed[6];
  varargin_3[35] = -M_deformed[7];
  varargin_3[41] = M_deformed[6];
  varargin_3[47] = 0.0;
  std::memset(&varargin_4[0], 0, 48U * sizeof(real_T));
  varargin_4[0] = M_deformed[9];
  varargin_4[6] = M_deformed[10];
  varargin_4[12] = M_deformed[11];
  varargin_4[18] = 0.0;
  varargin_4[24] = 0.0;
  varargin_4[1] = 0.0;
  varargin_4[7] = M_deformed[9];
  varargin_4[13] = 0.0;
  varargin_4[19] = M_deformed[10];
  varargin_4[25] = M_deformed[11];
  varargin_4[2] = -M_deformed[11];
  varargin_4[8] = 0.0;
  varargin_4[14] = M_deformed[9];
  varargin_4[20] = -M_deformed[11];
  varargin_4[26] = M_deformed[10];
  varargin_4[33] = 0.0;
  varargin_4[39] = -M_deformed[11];
  varargin_4[45] = M_deformed[10];
  varargin_4[34] = M_deformed[11];
  varargin_4[40] = 0.0;
  varargin_4[46] = -M_deformed[9];
  varargin_4[35] = -M_deformed[10];
  varargin_4[41] = M_deformed[9];
  varargin_4[47] = 0.0;
  std::memset(&rtDW.b_b[0], 0, 768U * sizeof(real_T));
  for (i = 0; i < 8; i++) {
    for (T_Local_data_tmp = 0; T_Local_data_tmp < 6; T_Local_data_tmp++) {
      b_b_tmp = 6 * i + T_Local_data_tmp;
      rtDW.b_b[T_Local_data_tmp + 24 * i] = varargin_1[b_b_tmp];
      rtDW.b_b[(T_Local_data_tmp + 24 * (i + 8)) + 6] = varargin_2[b_b_tmp];
      rtDW.b_b[(T_Local_data_tmp + 24 * (i + 16)) + 12] = varargin_3[b_b_tmp];
      rtDW.b_b[(T_Local_data_tmp + 24 * (i + 24)) + 18] = varargin_4[b_b_tmp];
    }
  }

  decom_size[0] = 32;
  decom_size[1] = 8;
  std::memset(&rtDW.decom_data[0], 0, sizeof(real_T) << 8U);
  for (N = 0; N < 4; N++) {
    std::memset(&b_I[0], 0, sizeof(int8_T) << 6U);
    for (T_Local_tmp = 0; T_Local_tmp < 8; T_Local_tmp++) {
      b_I[T_Local_tmp + (T_Local_tmp << 3)] = 1;
    }

    b_b_tmp = N << 3;
    for (i = 0; i < 8; i++) {
      for (T_Local_data_tmp = 0; T_Local_data_tmp < 8; T_Local_data_tmp++) {
        rtDW.decom_data[(T_Local_data_tmp + b_b_tmp) + (i << 5)] = b_I[(i << 3)
          + T_Local_data_tmp];
      }
    }
  }

  for (i = 0; i < 24; i++) {
    B_2[i] = 0;
  }

  for (i = 0; i < 3; i++) {
    b_b_tmp = i << 3;
    B_2[b_b_tmp + 5] = t[3 * i];
    B_2[b_b_tmp + 6] = t[3 * i + 1];
    B_2[b_b_tmp + 7] = t[3 * i + 2];
  }

  std::memset(&rtb_U_n[0], 0, sizeof(real_T) << 3U);
  J_size[0] = 12;
  J_size[1] = 24;
  for (i = 0; i < 24; i++) {
    for (T_Local_data_tmp = 0; T_Local_data_tmp < 12; T_Local_data_tmp++) {
      rtDW.J_data_m[T_Local_data_tmp + 12 * i] = rtDW.J_data[24 *
        T_Local_data_tmp + i];
    }
  }

  mtimes(rtDW.J_data_m, J_size, rtDW.b_b, rtDW.tmp_data, tmp_size);
  mtimes_e(rtDW.tmp_data, tmp_size, rtDW.decom_data, decom_size, A_data, A_size);
  N = A_size[0];
  y_size[0] = A_size[0];
  y_size[1] = 3;
  for (T_Local_tmp = 0; T_Local_tmp < 3; T_Local_tmp++) {
    coffset = T_Local_tmp * N;
    boffset = T_Local_tmp << 3;
    for (i = 0; i < N; i++) {
      s = 0.0;
      for (b_b_tmp = 0; b_b_tmp < 8; b_b_tmp++) {
        s += A_data[b_b_tmp * A_size[0] + i] * static_cast<real_T>(B_2[boffset +
          b_b_tmp]);
      }

      y_data[coffset + i] = s;
    }
  }

  pinv(y_data, y_size, z_data, tmp_size);
  for (i = 0; i < 12; i++) {
    for (T_Local_data_tmp = 0; T_Local_data_tmp < 3; T_Local_data_tmp++) {
      b_b_tmp = 3 * i + T_Local_data_tmp;
      b_A[b_b_tmp] = 0.0;
      for (b = 0; b < 12; b++) {
        b_A[b_b_tmp] += z_data[3 * b + T_Local_data_tmp] * rtConstP.pooled3[12 *
          i + b];
      }
    }
  }

  for (T_Local_tmp = 0; T_Local_tmp < 3; T_Local_tmp++) {
    s = 0.0;
    for (N = 0; N < 12; N++) {
      s += b_A[N * 3 + T_Local_tmp] * rtU.q_desired[N];
    }

    rtb_U_n[T_Local_tmp + 5] = s;
  }

  // End of MATLAB Function: '<Root>/MATLAB Function2'
  for (i = 0; i <= 6; i += 2) {
    // Sum: '<Root>/Sum11' incorporates:
    //   Outport: '<Root>/Out1'

    tmp = _mm_loadu_pd(&rtb_U_n[i]);
    tmp_0 = _mm_loadu_pd(&rtb_U[i]);

    // Outport: '<Root>/Out1'
    _mm_storeu_pd(&rtY.Out1[i], _mm_add_pd(tmp, tmp_0));
  }

  // Matfile logging
  rt_UpdateTXYLogVars((&rtM)->rtwLogInfo, (&(&rtM)->Timing.taskTime0));

  // signal main to stop simulation
  {                                    // Sample time: [0.02s, 0.0s]
    if ((rtmGetTFinal((&rtM))!=-1) &&
        !((rtmGetTFinal((&rtM))-(&rtM)->Timing.taskTime0) > (&rtM)
          ->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus((&rtM), "Simulation finished");
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  (&rtM)->Timing.taskTime0 =
    ((time_T)(++(&rtM)->Timing.clockTick0)) * (&rtM)->Timing.stepSize0;
}

// Model initialize function
void dynamic_lungs_embed::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal((&rtM), 1.0);
  (&rtM)->Timing.stepSize0 = 0.02;

  // Setup for data logging
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (nullptr);
    (&rtM)->rtwLogInfo = &rt_DataLoggingInfo;
  }

  // Setup for data logging
  {
    rtliSetLogXSignalInfo((&rtM)->rtwLogInfo, (nullptr));
    rtliSetLogXSignalPtrs((&rtM)->rtwLogInfo, (nullptr));
    rtliSetLogT((&rtM)->rtwLogInfo, "tout");
    rtliSetLogX((&rtM)->rtwLogInfo, "");
    rtliSetLogXFinal((&rtM)->rtwLogInfo, "");
    rtliSetLogVarNameModifier((&rtM)->rtwLogInfo, "rt_");
    rtliSetLogFormat((&rtM)->rtwLogInfo, 4);
    rtliSetLogMaxRows((&rtM)->rtwLogInfo, 0);
    rtliSetLogDecimation((&rtM)->rtwLogInfo, 1);
    rtliSetLogY((&rtM)->rtwLogInfo, "");
    rtliSetLogYSignalInfo((&rtM)->rtwLogInfo, (nullptr));
    rtliSetLogYSignalPtrs((&rtM)->rtwLogInfo, (nullptr));
  }

  // Matfile logging
  rt_StartDataLoggingWithStartTime((&rtM)->rtwLogInfo, 0.0, rtmGetTFinal((&rtM)),
    (&rtM)->Timing.stepSize0, (&rtmGetErrorStatus((&rtM))));
}

// Constructor
dynamic_lungs_embed::dynamic_lungs_embed() :
  rtU(),
  rtY(),
  rtDW(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
dynamic_lungs_embed::~dynamic_lungs_embed()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
dynamic_lungs_embed::RT_MODEL * dynamic_lungs_embed::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
