/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: HRXDUAL_Delay.h
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

#ifndef RTW_HEADER_HRXDUAL_Delay_h_
#define RTW_HEADER_HRXDUAL_Delay_h_
#ifndef HRXDUAL_Delay_COMMON_INCLUDES_
#define HRXDUAL_Delay_COMMON_INCLUDES_
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "can_message.h"
#include "c2000BoardSupport.h"
#include "F2806x_Device.h"
#endif                                 /* HRXDUAL_Delay_COMMON_INCLUDES_ */

#include "HRXDUAL_Delay_types.h"
#include "rt_nonfinite.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

extern void init_eCAN_A ( uint16_T bitRatePrescaler, uint16_T timeSeg1, uint16_T
  timeSeg2, uint16_T sbg, uint16_T sjw, uint16_T sam);

/* user code (top of export header file) */
#include "can_message.h"

/* Block signals for system '<S9>/Set Torque Mode of Operation (PDO)1' */
typedef struct {
  CAN_DATATYPE CANPack;                /* '<S26>/CAN Pack' */
  uint16_T TmpSignalConversionAtCANPackInp[3];
} B_SetTorqueModeofOperationPDO_T;

/* Block signals for system '<S9>/Set Torque Mode of Operation (PDO)2' */
typedef struct {
  CAN_DATATYPE CANPack;                /* '<S27>/CAN Pack' */
  uint16_T TmpSignalConversionAtCANPackInp[3];
} B_SetTorqueModeofOperationP_k_T;

/* Block signals (default storage) */
typedef struct {
  CAN_DATATYPE eCANReceive1_o2;        /* '<S4>/eCAN Receive1' */
  CAN_DATATYPE eCANReceive2_o2;        /* '<S4>/eCAN Receive2' */
  CAN_DATATYPE eCANReceive3_o2;        /* '<S4>/eCAN Receive3' */
  CAN_DATATYPE eCANReceive5_o2;        /* '<S4>/eCAN Receive5' */
  CAN_DATATYPE eCANReceive7_o2;        /* '<S4>/eCAN Receive7' */
  CAN_DATATYPE eCANReceive6_o2;        /* '<S4>/eCAN Receive6' */
  CAN_DATATYPE eCANReceive8_o2;        /* '<S4>/eCAN Receive8' */
  CAN_DATATYPE eCANReceive9_o2;        /* '<S4>/eCAN Receive9' */
  CAN_DATATYPE CANPack;                /* '<S1>/CAN Pack' */
  CAN_DATATYPE CANPack_p;              /* '<S2>/CAN Pack' */
  CAN_DATATYPE CANPack_pu;             /* '<S28>/CAN Pack' */
  uint16_T CANUnpack[2];               /* '<S6>/CAN Unpack' */
  uint16_T CANUnpack_k[2];             /* '<S5>/CAN Unpack' */
  uint16_T CANUnpack_j[2];             /* '<S7>/CAN Unpack' */
  uint16_T CANUnpack_jh[4];            /* '<S8>/CAN Unpack' */
  uint16_T CANUnpack_h[4];             /* '<S11>/CAN Unpack' */
  uint16_T CANUnpack_o[4];             /* '<S10>/CAN Unpack' */
  uint16_T CANUnpack_n[4];             /* '<S12>/CAN Unpack' */
  uint16_T CANUnpack_hx[2];            /* '<S13>/CAN Unpack' */
  uint16_T TmpSignalConversionAtCANPackInp[2];
  uint16_T TmpSignalConversionAtCANPackI_a[2];
  uint16_T TmpSignalConversionAtCANPack_aw[2];
  B_SetTorqueModeofOperationP_k_T EnableMotor2PDO3;/* '<S9>/Enable Motor2 (PDO)3' */
  B_SetTorqueModeofOperationPDO_T EnableMotorPDO2;/* '<S9>/Enable Motor (PDO)2' */
  B_SetTorqueModeofOperationP_k_T SwitchOnMotor2PDO2;/* '<S9>/Switch On Motor2 (PDO)2' */
  B_SetTorqueModeofOperationPDO_T SwitchOnMotorPDO1;/* '<S9>/Switch On Motor (PDO)1' */
  B_SetTorqueModeofOperationP_k_T SetMotor2ReadyPDO2;/* '<S9>/Set Motor2 Ready (PDO)2' */
  B_SetTorqueModeofOperationPDO_T SetMotorReadyPDO1;/* '<S9>/Set Motor Ready (PDO)1' */
  B_SetTorqueModeofOperationP_k_T SetTorqueModeofOperationPDO2;
                                /* '<S9>/Set Torque Mode of Operation (PDO)2' */
  B_SetTorqueModeofOperationPDO_T SetTorqueModeofOperationPDO1;
                                /* '<S9>/Set Torque Mode of Operation (PDO)1' */
} B_HRXDUAL_Delay_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE;                 /* '<S4>/Delay' */
  real_T pos_list[1500];               /* '<Root>/MATLAB Function' */
  int_T CANUnpack_ModeSignalID;        /* '<S6>/CAN Unpack' */
  int_T CANUnpack_StatusPortID;        /* '<S6>/CAN Unpack' */
  int_T CANUnpack_ModeSignalID_g;      /* '<S5>/CAN Unpack' */
  int_T CANUnpack_StatusPortID_h;      /* '<S5>/CAN Unpack' */
  int_T CANUnpack_ModeSignalID_gx;     /* '<S7>/CAN Unpack' */
  int_T CANUnpack_StatusPortID_k;      /* '<S7>/CAN Unpack' */
  int_T CANUnpack_ModeSignalID_l;      /* '<S8>/CAN Unpack' */
  int_T CANUnpack_StatusPortID_n;      /* '<S8>/CAN Unpack' */
  int_T CANUnpack_ModeSignalID_m;      /* '<S11>/CAN Unpack' */
  int_T CANUnpack_StatusPortID_f;      /* '<S11>/CAN Unpack' */
  int_T CANUnpack_ModeSignalID_n;      /* '<S10>/CAN Unpack' */
  int_T CANUnpack_StatusPortID_d;      /* '<S10>/CAN Unpack' */
  int_T CANUnpack_ModeSignalID_e;      /* '<S12>/CAN Unpack' */
  int_T CANUnpack_StatusPortID_hh;     /* '<S12>/CAN Unpack' */
  int_T CANUnpack_ModeSignalID_j;      /* '<S13>/CAN Unpack' */
  int_T CANUnpack_StatusPortID_o;      /* '<S13>/CAN Unpack' */
} DW_HRXDUAL_Delay_T;

/* Parameters for system: '<S9>/Set Torque Mode of Operation (PDO)1' */
struct P_SetTorqueModeofOperationPDO_T_ {
  uint16_T Constant24_Value;           /* Computed Parameter: Constant24_Value
                                        * Referenced by: '<S26>/Constant24'
                                        */
  uint16_T Constant23_Value;           /* Computed Parameter: Constant23_Value
                                        * Referenced by: '<S26>/Constant23'
                                        */
  uint16_T Constant22_Value;           /* Computed Parameter: Constant22_Value
                                        * Referenced by: '<S26>/Constant22'
                                        */
};

/* Parameters for system: '<S9>/Set Torque Mode of Operation (PDO)2' */
struct P_SetTorqueModeofOperationP_i_T_ {
  uint16_T Constant24_Value;           /* Computed Parameter: Constant24_Value
                                        * Referenced by: '<S27>/Constant24'
                                        */
  uint16_T Constant23_Value;           /* Computed Parameter: Constant23_Value
                                        * Referenced by: '<S27>/Constant23'
                                        */
  uint16_T Constant22_Value;           /* Computed Parameter: Constant22_Value
                                        * Referenced by: '<S27>/Constant22'
                                        */
};

/* Parameters (default storage) */
struct P_HRXDUAL_Delay_T_ {
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S9>/Constant2'
                                        */
  real_T Constant1_Value;              /* Expression: 1
                                        * Referenced by: '<S9>/Constant1'
                                        */
  real_T Gain_Gain;                    /* Expression: 1/1000
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/1000
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Pulsestorad1_Gain;            /* Expression: 2*pi/25600
                                        * Referenced by: '<S4>/Pulses to rad1'
                                        */
  real_T RPMtorads1_Gain;              /* Expression: 2*pi/60
                                        * Referenced by: '<S4>/RPM to rad//s1'
                                        */
  real_T Pulsestorad2_Gain;            /* Expression: 2*pi/25600
                                        * Referenced by: '<S4>/Pulses to rad2'
                                        */
  real_T RPMtorads2_Gain;              /* Expression: 2*pi/60
                                        * Referenced by: '<S4>/RPM to rad//s2'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1750
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1750
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 1750
                                        * Referenced by: '<Root>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -1750
                                        * Referenced by: '<Root>/Saturation1'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<S4>/Delay'
                                        */
  real_T Constant20_Value;             /* Expression: 1
                                        * Referenced by: '<S4>/Constant20'
                                        */
  P_SetTorqueModeofOperationP_i_T EnableMotor2PDO3;/* '<S9>/Enable Motor2 (PDO)3' */
  P_SetTorqueModeofOperationPDO_T EnableMotorPDO2;/* '<S9>/Enable Motor (PDO)2' */
  P_SetTorqueModeofOperationP_i_T SwitchOnMotor2PDO2;/* '<S9>/Switch On Motor2 (PDO)2' */
  P_SetTorqueModeofOperationPDO_T SwitchOnMotorPDO1;/* '<S9>/Switch On Motor (PDO)1' */
  P_SetTorqueModeofOperationP_i_T SetMotor2ReadyPDO2;/* '<S9>/Set Motor2 Ready (PDO)2' */
  P_SetTorqueModeofOperationPDO_T SetMotorReadyPDO1;/* '<S9>/Set Motor Ready (PDO)1' */
  P_SetTorqueModeofOperationP_i_T SetTorqueModeofOperationPDO2;
                                /* '<S9>/Set Torque Mode of Operation (PDO)2' */
  P_SetTorqueModeofOperationPDO_T SetTorqueModeofOperationPDO1;
                                /* '<S9>/Set Torque Mode of Operation (PDO)1' */
};

/* Real-time Model Data Structure */
struct tag_RTM_HRXDUAL_Delay_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

extern CAN_DATATYPE CAN_DATATYPE_GROUND;
extern CAN_DATATYPE CAN_DATATYPE_GROUND;
extern CAN_DATATYPE CAN_DATATYPE_GROUND;

/* Block parameters (default storage) */
extern P_HRXDUAL_Delay_T HRXDUAL_Delay_P;

/* Block signals (default storage) */
extern B_HRXDUAL_Delay_T HRXDUAL_Delay_B;

/* Block states (default storage) */
extern DW_HRXDUAL_Delay_T HRXDUAL_Delay_DW;

/* Model entry point functions */
extern void HRXDUAL_Delay_initialize(void);
extern void HRXDUAL_Delay_step(void);
extern void HRXDUAL_Delay_terminate(void);

/* Real-time Model object */
extern RT_MODEL_HRXDUAL_Delay_T *const HRXDUAL_Delay_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'HRXDUAL_Delay'
 * '<S1>'   : 'HRXDUAL_Delay/Apply Torque1'
 * '<S2>'   : 'HRXDUAL_Delay/Apply Torque2'
 * '<S3>'   : 'HRXDUAL_Delay/MATLAB Function'
 * '<S4>'   : 'HRXDUAL_Delay/Read position2'
 * '<S5>'   : 'HRXDUAL_Delay/Read position2/Subsystem'
 * '<S6>'   : 'HRXDUAL_Delay/Read position2/Subsystem1'
 * '<S7>'   : 'HRXDUAL_Delay/Read position2/Subsystem3'
 * '<S8>'   : 'HRXDUAL_Delay/Read position2/Subsystem4'
 * '<S9>'   : 'HRXDUAL_Delay/Read position2/Subsystem5'
 * '<S10>'  : 'HRXDUAL_Delay/Read position2/Subsystem6'
 * '<S11>'  : 'HRXDUAL_Delay/Read position2/Subsystem7'
 * '<S12>'  : 'HRXDUAL_Delay/Read position2/Subsystem8'
 * '<S13>'  : 'HRXDUAL_Delay/Read position2/Subsystem9'
 * '<S14>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Delay 1ms10'
 * '<S15>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Delay 1ms11'
 * '<S16>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Delay 1ms4'
 * '<S17>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Delay 1ms5'
 * '<S18>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Delay 1ms6'
 * '<S19>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Delay 1ms7'
 * '<S20>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Delay 1ms8'
 * '<S21>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Delay 1ms9'
 * '<S22>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Enable Motor (PDO)2'
 * '<S23>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Enable Motor2 (PDO)3'
 * '<S24>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Set Motor Ready (PDO)1'
 * '<S25>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Set Motor2 Ready (PDO)2'
 * '<S26>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Set Torque Mode of Operation (PDO)1'
 * '<S27>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Set Torque Mode of Operation (PDO)2'
 * '<S28>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Subsystem1'
 * '<S29>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Switch On Motor (PDO)1'
 * '<S30>'  : 'HRXDUAL_Delay/Read position2/Subsystem5/Switch On Motor2 (PDO)2'
 */
#endif                                 /* RTW_HEADER_HRXDUAL_Delay_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
