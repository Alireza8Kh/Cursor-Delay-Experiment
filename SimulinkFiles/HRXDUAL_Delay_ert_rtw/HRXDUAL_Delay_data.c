/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: HRXDUAL_Delay_data.c
 *
 * Code generated for Simulink model 'HRXDUAL_Delay'.
 *
 * Model version                  : 7.259
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Apr 24 18:18:50 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "HRXDUAL_Delay.h"

/* Block parameters (default storage) */
P_HRXDUAL_Delay_T HRXDUAL_Delay_P = {
  /* Expression: 0
   * Referenced by: '<S9>/Constant2'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S9>/Constant1'
   */
  1.0,

  /* Expression: 1/1000
   * Referenced by: '<Root>/Gain'
   */
  0.001,

  /* Expression: 1/1000
   * Referenced by: '<Root>/Gain1'
   */
  0.001,

  /* Expression: 2*pi/25600
   * Referenced by: '<S4>/Pulses to rad1'
   */
  0.00024543692606170261,

  /* Expression: 2*pi/60
   * Referenced by: '<S4>/RPM to rad//s1'
   */
  0.10471975511965977,

  /* Expression: 2*pi/25600
   * Referenced by: '<S4>/Pulses to rad2'
   */
  0.00024543692606170261,

  /* Expression: 2*pi/60
   * Referenced by: '<S4>/RPM to rad//s2'
   */
  0.10471975511965977,

  /* Expression: 1750
   * Referenced by: '<Root>/Saturation'
   */
  1750.0,

  /* Expression: -1750
   * Referenced by: '<Root>/Saturation'
   */
  -1750.0,

  /* Expression: 1750
   * Referenced by: '<Root>/Saturation1'
   */
  1750.0,

  /* Expression: -1750
   * Referenced by: '<Root>/Saturation1'
   */
  -1750.0,

  /* Expression: 0.0
   * Referenced by: '<S4>/Delay'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S4>/Constant20'
   */
  1.0,

  /* Start of '<S9>/Enable Motor2 (PDO)3' */
  {
    /* Computed Parameter: Constant24_Value
     * Referenced by: '<S23>/Constant24'
     */
    15U,

    /* Computed Parameter: Constant23_Value
     * Referenced by: '<S23>/Constant23'
     */
    0U,

    /* Computed Parameter: Constant22_Value
     * Referenced by: '<S23>/Constant22'
     */
    10U
  }
  ,

  /* End of '<S9>/Enable Motor2 (PDO)3' */

  /* Start of '<S9>/Enable Motor (PDO)2' */
  {
    /* Computed Parameter: Constant24_Value
     * Referenced by: '<S22>/Constant24'
     */
    15U,

    /* Computed Parameter: Constant23_Value
     * Referenced by: '<S22>/Constant23'
     */
    0U,

    /* Computed Parameter: Constant22_Value
     * Referenced by: '<S22>/Constant22'
     */
    10U
  }
  ,

  /* End of '<S9>/Enable Motor (PDO)2' */

  /* Start of '<S9>/Switch On Motor2 (PDO)2' */
  {
    /* Computed Parameter: Constant24_Value
     * Referenced by: '<S30>/Constant24'
     */
    7U,

    /* Computed Parameter: Constant23_Value
     * Referenced by: '<S30>/Constant23'
     */
    0U,

    /* Computed Parameter: Constant22_Value
     * Referenced by: '<S30>/Constant22'
     */
    10U
  }
  ,

  /* End of '<S9>/Switch On Motor2 (PDO)2' */

  /* Start of '<S9>/Switch On Motor (PDO)1' */
  {
    /* Computed Parameter: Constant24_Value
     * Referenced by: '<S29>/Constant24'
     */
    7U,

    /* Computed Parameter: Constant23_Value
     * Referenced by: '<S29>/Constant23'
     */
    0U,

    /* Computed Parameter: Constant22_Value
     * Referenced by: '<S29>/Constant22'
     */
    10U
  }
  ,

  /* End of '<S9>/Switch On Motor (PDO)1' */

  /* Start of '<S9>/Set Motor2 Ready (PDO)2' */
  {
    /* Computed Parameter: Constant24_Value
     * Referenced by: '<S25>/Constant24'
     */
    6U,

    /* Computed Parameter: Constant23_Value
     * Referenced by: '<S25>/Constant23'
     */
    0U,

    /* Computed Parameter: Constant22_Value
     * Referenced by: '<S25>/Constant22'
     */
    10U
  }
  ,

  /* End of '<S9>/Set Motor2 Ready (PDO)2' */

  /* Start of '<S9>/Set Motor Ready (PDO)1' */
  {
    /* Computed Parameter: Constant24_Value
     * Referenced by: '<S24>/Constant24'
     */
    6U,

    /* Computed Parameter: Constant23_Value
     * Referenced by: '<S24>/Constant23'
     */
    0U,

    /* Computed Parameter: Constant22_Value
     * Referenced by: '<S24>/Constant22'
     */
    10U
  }
  ,

  /* End of '<S9>/Set Motor Ready (PDO)1' */

  /* Start of '<S9>/Set Torque Mode of Operation (PDO)2' */
  {
    /* Computed Parameter: Constant24_Value
     * Referenced by: '<S27>/Constant24'
     */
    0U,

    /* Computed Parameter: Constant23_Value
     * Referenced by: '<S27>/Constant23'
     */
    0U,

    /* Computed Parameter: Constant22_Value
     * Referenced by: '<S27>/Constant22'
     */
    10U
  }
  ,

  /* End of '<S9>/Set Torque Mode of Operation (PDO)2' */

  /* Start of '<S9>/Set Torque Mode of Operation (PDO)1' */
  {
    /* Computed Parameter: Constant24_Value
     * Referenced by: '<S26>/Constant24'
     */
    0U,

    /* Computed Parameter: Constant23_Value
     * Referenced by: '<S26>/Constant23'
     */
    0U,

    /* Computed Parameter: Constant22_Value
     * Referenced by: '<S26>/Constant22'
     */
    10U
  }
  /* End of '<S9>/Set Torque Mode of Operation (PDO)1' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
