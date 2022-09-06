//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: dynamic_lungs_embed.h
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
#ifndef RTW_HEADER_dynamic_lungs_embed_h_
#define RTW_HEADER_dynamic_lungs_embed_h_
#include "rtwtypes.h"
#include "rt_logging.h"
#include <cfloat>
#include <stddef.h>

// Model Code Variants

// Macros for accessing real-time model data structure
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

#ifndef SS_UINT64
#define SS_UINT64                      17
#endif

#ifndef SS_INT64
#define SS_INT64                       18
#endif

extern "C" {
  static real_T rtGetNaN(void);
  static real32_T rtGetNaNF(void);
}                                      // extern "C"
  extern "C"
{
  extern real_T rtInf;
  extern real_T rtMinusInf;
  extern real_T rtNaN;
  extern real32_T rtInfF;
  extern real32_T rtMinusInfF;
  extern real32_T rtNaNF;
  static void rt_InitInfAndNaN(size_t realSize);
  static boolean_T rtIsInf(real_T value);
  static boolean_T rtIsInfF(real32_T value);
  static boolean_T rtIsNaN(real_T value);
  static boolean_T rtIsNaNF(real32_T value);
  struct BigEndianIEEEDouble {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  };

  struct LittleEndianIEEEDouble {
    struct {
      uint32_T wordL;
      uint32_T wordH;
    } words;
  };

  struct IEEESingle {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  };
}                                      // extern "C"

extern "C" {
  static real_T rtGetInf(void);
  static real32_T rtGetInfF(void);
  static real_T rtGetMinusInf(void);
  static real32_T rtGetMinusInfF(void);
}                                      // extern "C"
  // Class declaration for model dynamic_lungs_embed
  class dynamic_lungs_embed final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T decom_data[1016];
    real_T b_b[768];
    real_T J_data[2592];
    real_T J_data_m[2592];
    real_T tmp_data[1152];
  };

  // Constant parameters (default storage)
  struct ConstP {
    // Pooled Parameter (Expression: Mag)
    //  Referenced by:
    //    '<Root>/Constant23'
    //    '<Root>/Constant28'

    real_T pooled2[12];

    // Pooled Parameter (Expression: K)
    //  Referenced by:
    //    '<Root>/Constant24'
    //    '<Root>/Constant29'

    real_T pooled3[144];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T q_desired[12];              // '<Root>/q_desired'
    real_T q_observed[12];             // '<Root>/q_observed'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T Out1[8];                    // '<Root>/Out1'
  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T *errorStatus;
    RTWLogInfo *rtwLogInfo;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      time_T taskTime0;
      uint32_T clockTick0;
      time_T stepSize0;
      time_T tFinal;
      boolean_T stopRequestedFlag;
    } Timing;
  };

  // Copy Constructor
  dynamic_lungs_embed(dynamic_lungs_embed const&) = delete;

  // Assignment Operator
  dynamic_lungs_embed& operator= (dynamic_lungs_embed const&) & = delete;

  // Move Constructor
  dynamic_lungs_embed(dynamic_lungs_embed &&) = delete;

  // Move Assignment Operator
  dynamic_lungs_embed& operator= (dynamic_lungs_embed &&) = delete;

  // Real-Time Model get method
  dynamic_lungs_embed::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  dynamic_lungs_embed();

  // Destructor
  ~dynamic_lungs_embed();

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // private member function(s) for subsystem '<Root>'
  void mtimes(const real_T A_data[], const int32_T A_size[2], const real_T B_0
              [768], real_T C_data[], int32_T C_size[2]);
  void mtimes_e(const real_T A_data[], const int32_T A_size[2], const real_T
                B_data[], const int32_T B_size[2], real_T C_data[], int32_T
                C_size[2]);
  real_T xdotc_ilx(const real_T x[9], const real_T y[9], int32_T iy0);
  void xaxpy_ifn40(real_T a, real_T y[9], int32_T iy0);
  void xscal_dk(int32_T n, real_T a, real_T x_data[], int32_T ix0);
  void xscal_dkkv3(real_T a, real_T x[9], int32_T ix0);
  void xswap_kf(real_T x[9], int32_T ix0, int32_T iy0);
  void xswap(int32_T n, real_T x_data[], int32_T ix0, int32_T iy0);
  void xrotg(real_T *a, real_T *b, real_T *c, real_T *s);
  void xrot_dm(real_T x[9], int32_T ix0, int32_T iy0, real_T c, real_T s);
  void xrot(int32_T n, real_T x_data[], int32_T ix0, int32_T iy0, real_T c,
            real_T s);
  real_T xdotc_i(int32_T n, const real_T x_data[], int32_T ix0, const real_T
                 y_data[], int32_T iy0);
  void xaxpy_i(int32_T n, real_T a, int32_T ix0, real_T y_data[], int32_T iy0);
  real_T xnrm2_h(int32_T n, const real_T x_data[], int32_T ix0);
  void xscal_dkk(int32_T n, real_T a, real_T x_data[], int32_T ix0);
  real_T xnrm2_ht(const real_T x[3], int32_T ix0);
  void xscal_dkkv(real_T a, real_T x[3], int32_T ix0);
  void xaxpy_ifn4(int32_T n, real_T a, const real_T x_data[], int32_T ix0,
                  real_T y_data[], int32_T iy0);
  void xaxpy_ifn(int32_T n, real_T a, const real_T x_data[], int32_T ix0, real_T
                 y_data[], int32_T iy0);
  real_T xdotc(int32_T n, const real_T x_data[], int32_T ix0, const real_T
               y_data[], int32_T iy0);
  void xaxpy_if(int32_T n, real_T a, int32_T ix0, real_T y_data[], int32_T iy0);
  void svd(const real_T A_data[], const int32_T A_size[2], real_T U_data[],
           int32_T U_size[2], real_T s_data[], int32_T *s_size, real_T V_data[],
           int32_T V_size[2]);
  void xswap_k(real_T x_data[]);
  void xrot_d(real_T x_data[], int32_T ix0, int32_T iy0, real_T c, real_T s);
  void xscal_d(real_T a, real_T x_data[], int32_T ix0);
  void xaxpy(int32_T n, real_T a, int32_T ix0, real_T y_data[], int32_T iy0);
  real_T xnrm2(int32_T n, const real_T x_data[], int32_T ix0);
  void xscal(int32_T n, real_T a, real_T x_data[], int32_T ix0);
  void xzsvdc(real_T A_data[], const int32_T A_size[2], real_T U_data[], int32_T
              U_size[2], real_T S_data[], int32_T *S_size, real_T V_data[],
              int32_T V_size[2]);
  void pinv(const real_T A_data[], const int32_T A_size[2], real_T X_data[],
            int32_T X_size[2]);

  // Real-Time Model
  RT_MODEL rtM;
}

;

// Constant parameters (default storage)
extern const dynamic_lungs_embed::ConstP rtConstP;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'dynamic_lungs_embed'
//  '<S1>'   : 'dynamic_lungs_embed/MATLAB Function2'
//  '<S2>'   : 'dynamic_lungs_embed/MATLAB Function3'

#endif                                 // RTW_HEADER_dynamic_lungs_embed_h_

//
// File trailer for generated code.
//
// [EOF]
//
