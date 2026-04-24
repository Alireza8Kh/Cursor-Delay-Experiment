/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: HRXDUAL_Delay_private.h
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

#ifndef RTW_HEADER_HRXDUAL_Delay_private_h_
#define RTW_HEADER_HRXDUAL_Delay_private_h_
#include "rtwtypes.h"
#include "HRXDUAL_Delay.h"
#include "HRXDUAL_Delay_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "can_message.h"
#include "can_message.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

void config_eCAN_A_mbx (uint16_T mbxType, uint16_T mbxNo, uint32_T msgID,
  uint16_T msgType, uint16_T isAcceptanceFilteringEnabled, uint32_T msgIDMask);
extern CAN_DATATYPE CAN_DATATYPE_GROUND;
extern void HRXDUAL_Delay_Delay1ms4(void);
extern void HR_SetTorqueModeofOperationPDO1(B_SetTorqueModeofOperationPDO_T
  *localB, P_SetTorqueModeofOperationPDO_T *localP);
extern void HR_SetTorqueModeofOperationPDO2(B_SetTorqueModeofOperationP_k_T
  *localB, P_SetTorqueModeofOperationP_i_T *localP);

#endif                                 /* RTW_HEADER_HRXDUAL_Delay_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
