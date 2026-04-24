/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: HRXDUAL_Delay.c
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
#include "HRXDUAL_Delay_private.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include <string.h>

/* Block signals (default storage) */
B_HRXDUAL_Delay_T HRXDUAL_Delay_B;

/* Block states (default storage) */
DW_HRXDUAL_Delay_T HRXDUAL_Delay_DW;

/* Real-time model */
static RT_MODEL_HRXDUAL_Delay_T HRXDUAL_Delay_M_;
RT_MODEL_HRXDUAL_Delay_T *const HRXDUAL_Delay_M = &HRXDUAL_Delay_M_;

/*
 * Output and update for function-call system:
 *    '<S9>/Delay 1ms4'
 *    '<S9>/Delay 1ms5'
 *    '<S9>/Delay 1ms11'
 *    '<S9>/Delay 1ms6'
 *    '<S9>/Delay 1ms10'
 *    '<S9>/Delay 1ms7'
 *    '<S9>/Delay 1ms9'
 *    '<S9>/Delay 1ms8'
 */
void HRXDUAL_Delay_Delay1ms4(void)
{
  /* user code (Output function Body) */

  /* System '<S9>/Delay 1ms4' */
  DELAY_US(1000);

  /*Delay of 1 ms*/
}

/*
 * Output and update for function-call system:
 *    '<S9>/Set Torque Mode of Operation (PDO)1'
 *    '<S9>/Set Motor Ready (PDO)1'
 *    '<S9>/Switch On Motor (PDO)1'
 *    '<S9>/Enable Motor (PDO)2'
 */
void HR_SetTorqueModeofOperationPDO1(B_SetTorqueModeofOperationPDO_T *localB,
  P_SetTorqueModeofOperationPDO_T *localP)
{
  /* SignalConversion generated from: '<S26>/CAN Pack' incorporates:
   *  Constant: '<S26>/Constant22'
   *  Constant: '<S26>/Constant23'
   *  Constant: '<S26>/Constant24'
   */
  localB->TmpSignalConversionAtCANPackInp[0] = localP->Constant24_Value;
  localB->TmpSignalConversionAtCANPackInp[1] = localP->Constant23_Value;
  localB->TmpSignalConversionAtCANPackInp[2] = localP->Constant22_Value;

  /* S-Function (scanpack): '<S26>/CAN Pack' */
  /* S-Function (scanpack): '<S26>/CAN Pack' */
  localB->CANPack.ID = 513U;
  localB->CANPack.Length = 3U;
  localB->CANPack.Extended = 0U;
  localB->CANPack.Remote = 0;
  localB->CANPack.Data[0] = 0;
  localB->CANPack.Data[1] = 0;
  localB->CANPack.Data[2] = 0;
  localB->CANPack.Data[3] = 0;
  localB->CANPack.Data[4] = 0;
  localB->CANPack.Data[5] = 0;
  localB->CANPack.Data[6] = 0;
  localB->CANPack.Data[7] = 0;

  {
    (void) memcpy((localB->CANPack.Data),
                  &localB->TmpSignalConversionAtCANPackInp[0],
                  3 * sizeof(uint16_T));
  }

  /* S-Function (c280xcanxmt): '<S26>/eCAN Transmit3' */
  {
    uint32_T messageID = localB->CANPack.ID;
    uint16_T isExtended = localB->CANPack.Extended;
    config_eCAN_A_mbx (1U, 0,messageID, isExtended, 0U, 0U);
    struct ECAN_REGS ECanaShadow;
    EALLOW;
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = localB->CANPack.Length;
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.all &= ~((uint32_T)0x1 << 0);
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX0.MSGID.all &= ~((uint32_T) 0x1FFFFFFF);
    if (isExtended) {
      ECanaMboxes.MBOX0.MSGID.all |= (0x1FFFFFFF & ((uint32_T)localB->CANPack.ID));
    } else {
      ECanaMboxes.MBOX0.MSGID.all |= (0x1FFFFFFF & ((uint32_T)
        (localB->CANPack.ID) << 18));
    }

    ECanaShadow.CANME.all |= ((uint32_T)0x1 << 0);
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX0.MDL.byte.BYTE0 = localB->CANPack.Data[3];
    ECanaMboxes.MBOX0.MDL.byte.BYTE1 = localB->CANPack.Data[2];
    ECanaMboxes.MBOX0.MDL.byte.BYTE2 = localB->CANPack.Data[1];
    ECanaMboxes.MBOX0.MDL.byte.BYTE3 = localB->CANPack.Data[0];
    ECanaMboxes.MBOX0.MDH.byte.BYTE4 = localB->CANPack.Data[7];
    ECanaMboxes.MBOX0.MDH.byte.BYTE5 = localB->CANPack.Data[6];
    ECanaMboxes.MBOX0.MDH.byte.BYTE6 = localB->CANPack.Data[5];
    ECanaMboxes.MBOX0.MDH.byte.BYTE7 = localB->CANPack.Data[4];
    ECanaRegs.CANTRS.all = (((uint32_T) 0x00000001) << 0);
    EDIS;
    while (ECanaRegs.CANTA.bit.TA0 != 1 ) {
    }                              /* check eCAN Transmit Acknowledge register*/

    ECanaRegs.CANTA.bit.TA0 = 1;
                             /* clear eCAN Transmit Acknowledge register 	    */
  }
}

/*
 * Output and update for function-call system:
 *    '<S9>/Set Torque Mode of Operation (PDO)2'
 *    '<S9>/Set Motor2 Ready (PDO)2'
 *    '<S9>/Switch On Motor2 (PDO)2'
 *    '<S9>/Enable Motor2 (PDO)3'
 */
void HR_SetTorqueModeofOperationPDO2(B_SetTorqueModeofOperationP_k_T *localB,
  P_SetTorqueModeofOperationP_i_T *localP)
{
  /* SignalConversion generated from: '<S27>/CAN Pack' incorporates:
   *  Constant: '<S27>/Constant22'
   *  Constant: '<S27>/Constant23'
   *  Constant: '<S27>/Constant24'
   */
  localB->TmpSignalConversionAtCANPackInp[0] = localP->Constant24_Value;
  localB->TmpSignalConversionAtCANPackInp[1] = localP->Constant23_Value;
  localB->TmpSignalConversionAtCANPackInp[2] = localP->Constant22_Value;

  /* S-Function (scanpack): '<S27>/CAN Pack' */
  /* S-Function (scanpack): '<S27>/CAN Pack' */
  localB->CANPack.ID = 514U;
  localB->CANPack.Length = 3U;
  localB->CANPack.Extended = 0U;
  localB->CANPack.Remote = 0;
  localB->CANPack.Data[0] = 0;
  localB->CANPack.Data[1] = 0;
  localB->CANPack.Data[2] = 0;
  localB->CANPack.Data[3] = 0;
  localB->CANPack.Data[4] = 0;
  localB->CANPack.Data[5] = 0;
  localB->CANPack.Data[6] = 0;
  localB->CANPack.Data[7] = 0;

  {
    (void) memcpy((localB->CANPack.Data),
                  &localB->TmpSignalConversionAtCANPackInp[0],
                  3 * sizeof(uint16_T));
  }

  /* S-Function (c280xcanxmt): '<S27>/eCAN Transmit3' */
  {
    uint32_T messageID = localB->CANPack.ID;
    uint16_T isExtended = localB->CANPack.Extended;
    config_eCAN_A_mbx (1U, 0,messageID, isExtended, 0U, 0U);
    struct ECAN_REGS ECanaShadow;
    EALLOW;
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = localB->CANPack.Length;
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.all &= ~((uint32_T)0x1 << 0);
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX0.MSGID.all &= ~((uint32_T) 0x1FFFFFFF);
    if (isExtended) {
      ECanaMboxes.MBOX0.MSGID.all |= (0x1FFFFFFF & ((uint32_T)localB->CANPack.ID));
    } else {
      ECanaMboxes.MBOX0.MSGID.all |= (0x1FFFFFFF & ((uint32_T)
        (localB->CANPack.ID) << 18));
    }

    ECanaShadow.CANME.all |= ((uint32_T)0x1 << 0);
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX0.MDL.byte.BYTE0 = localB->CANPack.Data[3];
    ECanaMboxes.MBOX0.MDL.byte.BYTE1 = localB->CANPack.Data[2];
    ECanaMboxes.MBOX0.MDL.byte.BYTE2 = localB->CANPack.Data[1];
    ECanaMboxes.MBOX0.MDL.byte.BYTE3 = localB->CANPack.Data[0];
    ECanaMboxes.MBOX0.MDH.byte.BYTE4 = localB->CANPack.Data[7];
    ECanaMboxes.MBOX0.MDH.byte.BYTE5 = localB->CANPack.Data[6];
    ECanaMboxes.MBOX0.MDH.byte.BYTE6 = localB->CANPack.Data[5];
    ECanaMboxes.MBOX0.MDH.byte.BYTE7 = localB->CANPack.Data[4];
    ECanaRegs.CANTRS.all = (((uint32_T) 0x00000001) << 0);
    EDIS;
    while (ECanaRegs.CANTA.bit.TA0 != 1 ) {
    }                              /* check eCAN Transmit Acknowledge register*/

    ECanaRegs.CANTA.bit.TA0 = 1;
                             /* clear eCAN Transmit Acknowledge register 	    */
  }
}

/* Model step function */
void HRXDUAL_Delay_step(void)
{
  real_T Gain;
  real_T Gain1;
  real_T Pulsestorad1;
  real_T Pulsestorad2;
  real_T delayed_pos1;
  real_T delayed_pos2;
  real_T k;
  int16_T j;
  int16_T pos_list_tmp;
  int16_T rtb_BitwiseOR_nt;
  boolean_T exitg1;

  /* S-Function (c280xcanrcv): '<S4>/eCAN Receive1' */
  {
    struct ECAN_REGS ECanaShadow;
    if (ECanaRegs.CANRMP.bit.RMP7) {
      /* reenable the mailbox to receive the next message */
      EALLOW;
      ECanaShadow.CANRMP.all = 0x0;
      ECanaShadow.CANRMP.bit.RMP7 = 1;
                                    /* request clear RMP for this mailbox only*/
      ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
                                    /* 32-bit register access is reliable only*/
      EDIS;
      uint16_T len = ECanaMboxes.MBOX7.MSGCTRL.bit.DLC;
      unsigned char rxMsgData[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint16_T idx = 0;
      for (idx = 0; idx<len; idx++) {
        if (idx<len) {
          switch (idx){
           case 0:
            rxMsgData[3] = ECanaMboxes.MBOX7.MDL.byte.BYTE3;
            break;

           case 1:
            rxMsgData[2] = ECanaMboxes.MBOX7.MDL.byte.BYTE2;
            break;

           case 2:
            rxMsgData[1] = ECanaMboxes.MBOX7.MDL.byte.BYTE1;
            break;

           case 3:
            rxMsgData[0] = ECanaMboxes.MBOX7.MDL.byte.BYTE0;
            break;

           case 4:
            rxMsgData[7] = ECanaMboxes.MBOX7.MDH.byte.BYTE7;
            break;

           case 5:
            rxMsgData[6] = ECanaMboxes.MBOX7.MDH.byte.BYTE6;
            break;

           case 6:
            rxMsgData[5] = ECanaMboxes.MBOX7.MDH.byte.BYTE5;
            break;

           case 7:
            rxMsgData[4] = ECanaMboxes.MBOX7.MDH.byte.BYTE4;
            break;
          }
        }
      }

      HRXDUAL_Delay_B.eCANReceive1_o2.Extended = ECanaMboxes.MBOX7.MSGID.bit.IDE;
      HRXDUAL_Delay_B.eCANReceive1_o2.Length = ECanaMboxes.MBOX7.MSGCTRL.bit.DLC;
      uint32_T msgID = ECanaMboxes.MBOX7.MSGID.all;
      if (ECanaMboxes.MBOX7.MSGID.bit.IDE) {
        HRXDUAL_Delay_B.eCANReceive1_o2.ID = (uint32_T)(msgID & ((uint32_T)
          0x1FFFFFFF));
      } else {
        HRXDUAL_Delay_B.eCANReceive1_o2.ID = ((uint32_T)(msgID & ((uint32_T)
          0x1FFC0000))>>18);
      }

      HRXDUAL_Delay_B.eCANReceive1_o2.Data[3] = rxMsgData[0];
      HRXDUAL_Delay_B.eCANReceive1_o2.Data[2] = rxMsgData[1];
      HRXDUAL_Delay_B.eCANReceive1_o2.Data[1] = rxMsgData[2];
      HRXDUAL_Delay_B.eCANReceive1_o2.Data[0] = rxMsgData[3];
      HRXDUAL_Delay_B.eCANReceive1_o2.Data[7] = rxMsgData[4];
      HRXDUAL_Delay_B.eCANReceive1_o2.Data[6] = rxMsgData[5];
      HRXDUAL_Delay_B.eCANReceive1_o2.Data[5] = rxMsgData[6];
      HRXDUAL_Delay_B.eCANReceive1_o2.Data[4] = rxMsgData[7];

      /* -- Call CAN RX Fcn-Call_0 -- */
    }
  }

  /* S-Function (scanunpack): '<S6>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<S6>/CAN Unpack' */
    if ((2 == HRXDUAL_Delay_B.eCANReceive1_o2.Length) &&
        (HRXDUAL_Delay_B.eCANReceive1_o2.ID != INVALID_CAN_ID) ) {
      (void) memcpy(&HRXDUAL_Delay_B.CANUnpack[0],
                    HRXDUAL_Delay_B.eCANReceive1_o2.Data,
                    2 * sizeof(uint16_T));
    }
  }

  /* S-Function (c280xcanrcv): '<S4>/eCAN Receive2' */
  {
    struct ECAN_REGS ECanaShadow;
    if (ECanaRegs.CANRMP.bit.RMP8) {
      /* reenable the mailbox to receive the next message */
      EALLOW;
      ECanaShadow.CANRMP.all = 0x0;
      ECanaShadow.CANRMP.bit.RMP8 = 1;
                                    /* request clear RMP for this mailbox only*/
      ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
                                    /* 32-bit register access is reliable only*/
      EDIS;
      uint16_T len = ECanaMboxes.MBOX8.MSGCTRL.bit.DLC;
      unsigned char rxMsgData[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint16_T idx = 0;
      for (idx = 0; idx<len; idx++) {
        if (idx<len) {
          switch (idx){
           case 0:
            rxMsgData[3] = ECanaMboxes.MBOX8.MDL.byte.BYTE3;
            break;

           case 1:
            rxMsgData[2] = ECanaMboxes.MBOX8.MDL.byte.BYTE2;
            break;

           case 2:
            rxMsgData[1] = ECanaMboxes.MBOX8.MDL.byte.BYTE1;
            break;

           case 3:
            rxMsgData[0] = ECanaMboxes.MBOX8.MDL.byte.BYTE0;
            break;

           case 4:
            rxMsgData[7] = ECanaMboxes.MBOX8.MDH.byte.BYTE7;
            break;

           case 5:
            rxMsgData[6] = ECanaMboxes.MBOX8.MDH.byte.BYTE6;
            break;

           case 6:
            rxMsgData[5] = ECanaMboxes.MBOX8.MDH.byte.BYTE5;
            break;

           case 7:
            rxMsgData[4] = ECanaMboxes.MBOX8.MDH.byte.BYTE4;
            break;
          }
        }
      }

      HRXDUAL_Delay_B.eCANReceive2_o2.Extended = ECanaMboxes.MBOX8.MSGID.bit.IDE;
      HRXDUAL_Delay_B.eCANReceive2_o2.Length = ECanaMboxes.MBOX8.MSGCTRL.bit.DLC;
      uint32_T msgID = ECanaMboxes.MBOX8.MSGID.all;
      if (ECanaMboxes.MBOX8.MSGID.bit.IDE) {
        HRXDUAL_Delay_B.eCANReceive2_o2.ID = (uint32_T)(msgID & ((uint32_T)
          0x1FFFFFFF));
      } else {
        HRXDUAL_Delay_B.eCANReceive2_o2.ID = ((uint32_T)(msgID & ((uint32_T)
          0x1FFC0000))>>18);
      }

      HRXDUAL_Delay_B.eCANReceive2_o2.Data[3] = rxMsgData[0];
      HRXDUAL_Delay_B.eCANReceive2_o2.Data[2] = rxMsgData[1];
      HRXDUAL_Delay_B.eCANReceive2_o2.Data[1] = rxMsgData[2];
      HRXDUAL_Delay_B.eCANReceive2_o2.Data[0] = rxMsgData[3];
      HRXDUAL_Delay_B.eCANReceive2_o2.Data[7] = rxMsgData[4];
      HRXDUAL_Delay_B.eCANReceive2_o2.Data[6] = rxMsgData[5];
      HRXDUAL_Delay_B.eCANReceive2_o2.Data[5] = rxMsgData[6];
      HRXDUAL_Delay_B.eCANReceive2_o2.Data[4] = rxMsgData[7];

      /* -- Call CAN RX Fcn-Call_0 -- */
    }
  }

  /* S-Function (scanunpack): '<S5>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<S5>/CAN Unpack' */
    if ((2 == HRXDUAL_Delay_B.eCANReceive2_o2.Length) &&
        (HRXDUAL_Delay_B.eCANReceive2_o2.ID != INVALID_CAN_ID) ) {
      (void) memcpy(&HRXDUAL_Delay_B.CANUnpack_k[0],
                    HRXDUAL_Delay_B.eCANReceive2_o2.Data,
                    2 * sizeof(uint16_T));
    }
  }

  /* S-Function (c280xcanrcv): '<S4>/eCAN Receive3' */
  {
    struct ECAN_REGS ECanaShadow;
    if (ECanaRegs.CANRMP.bit.RMP9) {
      /* reenable the mailbox to receive the next message */
      EALLOW;
      ECanaShadow.CANRMP.all = 0x0;
      ECanaShadow.CANRMP.bit.RMP9 = 1;
                                    /* request clear RMP for this mailbox only*/
      ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
                                    /* 32-bit register access is reliable only*/
      EDIS;
      uint16_T len = ECanaMboxes.MBOX9.MSGCTRL.bit.DLC;
      unsigned char rxMsgData[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint16_T idx = 0;
      for (idx = 0; idx<len; idx++) {
        if (idx<len) {
          switch (idx){
           case 0:
            rxMsgData[3] = ECanaMboxes.MBOX9.MDL.byte.BYTE3;
            break;

           case 1:
            rxMsgData[2] = ECanaMboxes.MBOX9.MDL.byte.BYTE2;
            break;

           case 2:
            rxMsgData[1] = ECanaMboxes.MBOX9.MDL.byte.BYTE1;
            break;

           case 3:
            rxMsgData[0] = ECanaMboxes.MBOX9.MDL.byte.BYTE0;
            break;

           case 4:
            rxMsgData[7] = ECanaMboxes.MBOX9.MDH.byte.BYTE7;
            break;

           case 5:
            rxMsgData[6] = ECanaMboxes.MBOX9.MDH.byte.BYTE6;
            break;

           case 6:
            rxMsgData[5] = ECanaMboxes.MBOX9.MDH.byte.BYTE5;
            break;

           case 7:
            rxMsgData[4] = ECanaMboxes.MBOX9.MDH.byte.BYTE4;
            break;
          }
        }
      }

      HRXDUAL_Delay_B.eCANReceive3_o2.Extended = ECanaMboxes.MBOX9.MSGID.bit.IDE;
      HRXDUAL_Delay_B.eCANReceive3_o2.Length = ECanaMboxes.MBOX9.MSGCTRL.bit.DLC;
      uint32_T msgID = ECanaMboxes.MBOX9.MSGID.all;
      if (ECanaMboxes.MBOX9.MSGID.bit.IDE) {
        HRXDUAL_Delay_B.eCANReceive3_o2.ID = (uint32_T)(msgID & ((uint32_T)
          0x1FFFFFFF));
      } else {
        HRXDUAL_Delay_B.eCANReceive3_o2.ID = ((uint32_T)(msgID & ((uint32_T)
          0x1FFC0000))>>18);
      }

      HRXDUAL_Delay_B.eCANReceive3_o2.Data[3] = rxMsgData[0];
      HRXDUAL_Delay_B.eCANReceive3_o2.Data[2] = rxMsgData[1];
      HRXDUAL_Delay_B.eCANReceive3_o2.Data[1] = rxMsgData[2];
      HRXDUAL_Delay_B.eCANReceive3_o2.Data[0] = rxMsgData[3];
      HRXDUAL_Delay_B.eCANReceive3_o2.Data[7] = rxMsgData[4];
      HRXDUAL_Delay_B.eCANReceive3_o2.Data[6] = rxMsgData[5];
      HRXDUAL_Delay_B.eCANReceive3_o2.Data[5] = rxMsgData[6];
      HRXDUAL_Delay_B.eCANReceive3_o2.Data[4] = rxMsgData[7];

      /* -- Call CAN RX Fcn-Call_0 -- */
    }
  }

  /* S-Function (scanunpack): '<S7>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<S7>/CAN Unpack' */
    if ((2 == HRXDUAL_Delay_B.eCANReceive3_o2.Length) &&
        (HRXDUAL_Delay_B.eCANReceive3_o2.ID != INVALID_CAN_ID) ) {
      (void) memcpy(&HRXDUAL_Delay_B.CANUnpack_j[0],
                    HRXDUAL_Delay_B.eCANReceive3_o2.Data,
                    2 * sizeof(uint16_T));
    }
  }

  /* S-Function (c280xcanrcv): '<S4>/eCAN Receive5' */
  {
    struct ECAN_REGS ECanaShadow;
    if (ECanaRegs.CANRMP.bit.RMP3) {
      /* reenable the mailbox to receive the next message */
      EALLOW;
      ECanaShadow.CANRMP.all = 0x0;
      ECanaShadow.CANRMP.bit.RMP3 = 1;
                                    /* request clear RMP for this mailbox only*/
      ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
                                    /* 32-bit register access is reliable only*/
      EDIS;
      uint16_T len = ECanaMboxes.MBOX3.MSGCTRL.bit.DLC;
      unsigned char rxMsgData[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint16_T idx = 0;
      for (idx = 0; idx<len; idx++) {
        if (idx<len) {
          switch (idx){
           case 0:
            rxMsgData[3] = ECanaMboxes.MBOX3.MDL.byte.BYTE3;
            break;

           case 1:
            rxMsgData[2] = ECanaMboxes.MBOX3.MDL.byte.BYTE2;
            break;

           case 2:
            rxMsgData[1] = ECanaMboxes.MBOX3.MDL.byte.BYTE1;
            break;

           case 3:
            rxMsgData[0] = ECanaMboxes.MBOX3.MDL.byte.BYTE0;
            break;

           case 4:
            rxMsgData[7] = ECanaMboxes.MBOX3.MDH.byte.BYTE7;
            break;

           case 5:
            rxMsgData[6] = ECanaMboxes.MBOX3.MDH.byte.BYTE6;
            break;

           case 6:
            rxMsgData[5] = ECanaMboxes.MBOX3.MDH.byte.BYTE5;
            break;

           case 7:
            rxMsgData[4] = ECanaMboxes.MBOX3.MDH.byte.BYTE4;
            break;
          }
        }
      }

      HRXDUAL_Delay_B.eCANReceive5_o2.Extended = ECanaMboxes.MBOX3.MSGID.bit.IDE;
      HRXDUAL_Delay_B.eCANReceive5_o2.Length = ECanaMboxes.MBOX3.MSGCTRL.bit.DLC;
      uint32_T msgID = ECanaMboxes.MBOX3.MSGID.all;
      if (ECanaMboxes.MBOX3.MSGID.bit.IDE) {
        HRXDUAL_Delay_B.eCANReceive5_o2.ID = (uint32_T)(msgID & ((uint32_T)
          0x1FFFFFFF));
      } else {
        HRXDUAL_Delay_B.eCANReceive5_o2.ID = ((uint32_T)(msgID & ((uint32_T)
          0x1FFC0000))>>18);
      }

      HRXDUAL_Delay_B.eCANReceive5_o2.Data[3] = rxMsgData[0];
      HRXDUAL_Delay_B.eCANReceive5_o2.Data[2] = rxMsgData[1];
      HRXDUAL_Delay_B.eCANReceive5_o2.Data[1] = rxMsgData[2];
      HRXDUAL_Delay_B.eCANReceive5_o2.Data[0] = rxMsgData[3];
      HRXDUAL_Delay_B.eCANReceive5_o2.Data[7] = rxMsgData[4];
      HRXDUAL_Delay_B.eCANReceive5_o2.Data[6] = rxMsgData[5];
      HRXDUAL_Delay_B.eCANReceive5_o2.Data[5] = rxMsgData[6];
      HRXDUAL_Delay_B.eCANReceive5_o2.Data[4] = rxMsgData[7];

      /* -- Call CAN RX Fcn-Call_0 -- */
    }
  }

  /* S-Function (scanunpack): '<S8>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<S8>/CAN Unpack' */
    if ((4 == HRXDUAL_Delay_B.eCANReceive5_o2.Length) &&
        (HRXDUAL_Delay_B.eCANReceive5_o2.ID != INVALID_CAN_ID) ) {
      (void) memcpy(&HRXDUAL_Delay_B.CANUnpack_jh[0],
                    HRXDUAL_Delay_B.eCANReceive5_o2.Data,
                    4 * sizeof(uint16_T));
    }
  }

  /* S-Function (c280xcanrcv): '<S4>/eCAN Receive7' */
  {
    struct ECAN_REGS ECanaShadow;
    if (ECanaRegs.CANRMP.bit.RMP5) {
      /* reenable the mailbox to receive the next message */
      EALLOW;
      ECanaShadow.CANRMP.all = 0x0;
      ECanaShadow.CANRMP.bit.RMP5 = 1;
                                    /* request clear RMP for this mailbox only*/
      ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
                                    /* 32-bit register access is reliable only*/
      EDIS;
      uint16_T len = ECanaMboxes.MBOX5.MSGCTRL.bit.DLC;
      unsigned char rxMsgData[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint16_T idx = 0;
      for (idx = 0; idx<len; idx++) {
        if (idx<len) {
          switch (idx){
           case 0:
            rxMsgData[3] = ECanaMboxes.MBOX5.MDL.byte.BYTE3;
            break;

           case 1:
            rxMsgData[2] = ECanaMboxes.MBOX5.MDL.byte.BYTE2;
            break;

           case 2:
            rxMsgData[1] = ECanaMboxes.MBOX5.MDL.byte.BYTE1;
            break;

           case 3:
            rxMsgData[0] = ECanaMboxes.MBOX5.MDL.byte.BYTE0;
            break;

           case 4:
            rxMsgData[7] = ECanaMboxes.MBOX5.MDH.byte.BYTE7;
            break;

           case 5:
            rxMsgData[6] = ECanaMboxes.MBOX5.MDH.byte.BYTE6;
            break;

           case 6:
            rxMsgData[5] = ECanaMboxes.MBOX5.MDH.byte.BYTE5;
            break;

           case 7:
            rxMsgData[4] = ECanaMboxes.MBOX5.MDH.byte.BYTE4;
            break;
          }
        }
      }

      HRXDUAL_Delay_B.eCANReceive7_o2.Extended = ECanaMboxes.MBOX5.MSGID.bit.IDE;
      HRXDUAL_Delay_B.eCANReceive7_o2.Length = ECanaMboxes.MBOX5.MSGCTRL.bit.DLC;
      uint32_T msgID = ECanaMboxes.MBOX5.MSGID.all;
      if (ECanaMboxes.MBOX5.MSGID.bit.IDE) {
        HRXDUAL_Delay_B.eCANReceive7_o2.ID = (uint32_T)(msgID & ((uint32_T)
          0x1FFFFFFF));
      } else {
        HRXDUAL_Delay_B.eCANReceive7_o2.ID = ((uint32_T)(msgID & ((uint32_T)
          0x1FFC0000))>>18);
      }

      HRXDUAL_Delay_B.eCANReceive7_o2.Data[3] = rxMsgData[0];
      HRXDUAL_Delay_B.eCANReceive7_o2.Data[2] = rxMsgData[1];
      HRXDUAL_Delay_B.eCANReceive7_o2.Data[1] = rxMsgData[2];
      HRXDUAL_Delay_B.eCANReceive7_o2.Data[0] = rxMsgData[3];
      HRXDUAL_Delay_B.eCANReceive7_o2.Data[7] = rxMsgData[4];
      HRXDUAL_Delay_B.eCANReceive7_o2.Data[6] = rxMsgData[5];
      HRXDUAL_Delay_B.eCANReceive7_o2.Data[5] = rxMsgData[6];
      HRXDUAL_Delay_B.eCANReceive7_o2.Data[4] = rxMsgData[7];

      /* -- Call CAN RX Fcn-Call_0 -- */
    }
  }

  /* S-Function (scanunpack): '<S11>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<S11>/CAN Unpack' */
    if ((4 == HRXDUAL_Delay_B.eCANReceive7_o2.Length) &&
        (HRXDUAL_Delay_B.eCANReceive7_o2.ID != INVALID_CAN_ID) ) {
      (void) memcpy(&HRXDUAL_Delay_B.CANUnpack_h[0],
                    HRXDUAL_Delay_B.eCANReceive7_o2.Data,
                    4 * sizeof(uint16_T));
    }
  }

  /* S-Function (c280xcanrcv): '<S4>/eCAN Receive6' */
  {
    struct ECAN_REGS ECanaShadow;
    if (ECanaRegs.CANRMP.bit.RMP4) {
      /* reenable the mailbox to receive the next message */
      EALLOW;
      ECanaShadow.CANRMP.all = 0x0;
      ECanaShadow.CANRMP.bit.RMP4 = 1;
                                    /* request clear RMP for this mailbox only*/
      ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
                                    /* 32-bit register access is reliable only*/
      EDIS;
      uint16_T len = ECanaMboxes.MBOX4.MSGCTRL.bit.DLC;
      unsigned char rxMsgData[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint16_T idx = 0;
      for (idx = 0; idx<len; idx++) {
        if (idx<len) {
          switch (idx){
           case 0:
            rxMsgData[3] = ECanaMboxes.MBOX4.MDL.byte.BYTE3;
            break;

           case 1:
            rxMsgData[2] = ECanaMboxes.MBOX4.MDL.byte.BYTE2;
            break;

           case 2:
            rxMsgData[1] = ECanaMboxes.MBOX4.MDL.byte.BYTE1;
            break;

           case 3:
            rxMsgData[0] = ECanaMboxes.MBOX4.MDL.byte.BYTE0;
            break;

           case 4:
            rxMsgData[7] = ECanaMboxes.MBOX4.MDH.byte.BYTE7;
            break;

           case 5:
            rxMsgData[6] = ECanaMboxes.MBOX4.MDH.byte.BYTE6;
            break;

           case 6:
            rxMsgData[5] = ECanaMboxes.MBOX4.MDH.byte.BYTE5;
            break;

           case 7:
            rxMsgData[4] = ECanaMboxes.MBOX4.MDH.byte.BYTE4;
            break;
          }
        }
      }

      HRXDUAL_Delay_B.eCANReceive6_o2.Extended = ECanaMboxes.MBOX4.MSGID.bit.IDE;
      HRXDUAL_Delay_B.eCANReceive6_o2.Length = ECanaMboxes.MBOX4.MSGCTRL.bit.DLC;
      uint32_T msgID = ECanaMboxes.MBOX4.MSGID.all;
      if (ECanaMboxes.MBOX4.MSGID.bit.IDE) {
        HRXDUAL_Delay_B.eCANReceive6_o2.ID = (uint32_T)(msgID & ((uint32_T)
          0x1FFFFFFF));
      } else {
        HRXDUAL_Delay_B.eCANReceive6_o2.ID = ((uint32_T)(msgID & ((uint32_T)
          0x1FFC0000))>>18);
      }

      HRXDUAL_Delay_B.eCANReceive6_o2.Data[3] = rxMsgData[0];
      HRXDUAL_Delay_B.eCANReceive6_o2.Data[2] = rxMsgData[1];
      HRXDUAL_Delay_B.eCANReceive6_o2.Data[1] = rxMsgData[2];
      HRXDUAL_Delay_B.eCANReceive6_o2.Data[0] = rxMsgData[3];
      HRXDUAL_Delay_B.eCANReceive6_o2.Data[7] = rxMsgData[4];
      HRXDUAL_Delay_B.eCANReceive6_o2.Data[6] = rxMsgData[5];
      HRXDUAL_Delay_B.eCANReceive6_o2.Data[5] = rxMsgData[6];
      HRXDUAL_Delay_B.eCANReceive6_o2.Data[4] = rxMsgData[7];

      /* -- Call CAN RX Fcn-Call_0 -- */
    }
  }

  /* S-Function (scanunpack): '<S10>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<S10>/CAN Unpack' */
    if ((4 == HRXDUAL_Delay_B.eCANReceive6_o2.Length) &&
        (HRXDUAL_Delay_B.eCANReceive6_o2.ID != INVALID_CAN_ID) ) {
      (void) memcpy(&HRXDUAL_Delay_B.CANUnpack_o[0],
                    HRXDUAL_Delay_B.eCANReceive6_o2.Data,
                    4 * sizeof(uint16_T));
    }
  }

  /* S-Function (c280xcanrcv): '<S4>/eCAN Receive8' */
  {
    struct ECAN_REGS ECanaShadow;
    if (ECanaRegs.CANRMP.bit.RMP6) {
      /* reenable the mailbox to receive the next message */
      EALLOW;
      ECanaShadow.CANRMP.all = 0x0;
      ECanaShadow.CANRMP.bit.RMP6 = 1;
                                    /* request clear RMP for this mailbox only*/
      ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
                                    /* 32-bit register access is reliable only*/
      EDIS;
      uint16_T len = ECanaMboxes.MBOX6.MSGCTRL.bit.DLC;
      unsigned char rxMsgData[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint16_T idx = 0;
      for (idx = 0; idx<len; idx++) {
        if (idx<len) {
          switch (idx){
           case 0:
            rxMsgData[3] = ECanaMboxes.MBOX6.MDL.byte.BYTE3;
            break;

           case 1:
            rxMsgData[2] = ECanaMboxes.MBOX6.MDL.byte.BYTE2;
            break;

           case 2:
            rxMsgData[1] = ECanaMboxes.MBOX6.MDL.byte.BYTE1;
            break;

           case 3:
            rxMsgData[0] = ECanaMboxes.MBOX6.MDL.byte.BYTE0;
            break;

           case 4:
            rxMsgData[7] = ECanaMboxes.MBOX6.MDH.byte.BYTE7;
            break;

           case 5:
            rxMsgData[6] = ECanaMboxes.MBOX6.MDH.byte.BYTE6;
            break;

           case 6:
            rxMsgData[5] = ECanaMboxes.MBOX6.MDH.byte.BYTE5;
            break;

           case 7:
            rxMsgData[4] = ECanaMboxes.MBOX6.MDH.byte.BYTE4;
            break;
          }
        }
      }

      HRXDUAL_Delay_B.eCANReceive8_o2.Extended = ECanaMboxes.MBOX6.MSGID.bit.IDE;
      HRXDUAL_Delay_B.eCANReceive8_o2.Length = ECanaMboxes.MBOX6.MSGCTRL.bit.DLC;
      uint32_T msgID = ECanaMboxes.MBOX6.MSGID.all;
      if (ECanaMboxes.MBOX6.MSGID.bit.IDE) {
        HRXDUAL_Delay_B.eCANReceive8_o2.ID = (uint32_T)(msgID & ((uint32_T)
          0x1FFFFFFF));
      } else {
        HRXDUAL_Delay_B.eCANReceive8_o2.ID = ((uint32_T)(msgID & ((uint32_T)
          0x1FFC0000))>>18);
      }

      HRXDUAL_Delay_B.eCANReceive8_o2.Data[3] = rxMsgData[0];
      HRXDUAL_Delay_B.eCANReceive8_o2.Data[2] = rxMsgData[1];
      HRXDUAL_Delay_B.eCANReceive8_o2.Data[1] = rxMsgData[2];
      HRXDUAL_Delay_B.eCANReceive8_o2.Data[0] = rxMsgData[3];
      HRXDUAL_Delay_B.eCANReceive8_o2.Data[7] = rxMsgData[4];
      HRXDUAL_Delay_B.eCANReceive8_o2.Data[6] = rxMsgData[5];
      HRXDUAL_Delay_B.eCANReceive8_o2.Data[5] = rxMsgData[6];
      HRXDUAL_Delay_B.eCANReceive8_o2.Data[4] = rxMsgData[7];

      /* -- Call CAN RX Fcn-Call_0 -- */
    }
  }

  /* S-Function (scanunpack): '<S12>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<S12>/CAN Unpack' */
    if ((4 == HRXDUAL_Delay_B.eCANReceive8_o2.Length) &&
        (HRXDUAL_Delay_B.eCANReceive8_o2.ID != INVALID_CAN_ID) ) {
      (void) memcpy(&HRXDUAL_Delay_B.CANUnpack_n[0],
                    HRXDUAL_Delay_B.eCANReceive8_o2.Data,
                    4 * sizeof(uint16_T));
    }
  }

  /* S-Function (c280xcanrcv): '<S4>/eCAN Receive9' */
  {
    struct ECAN_REGS ECanaShadow;
    if (ECanaRegs.CANRMP.bit.RMP11) {
      /* reenable the mailbox to receive the next message */
      EALLOW;
      ECanaShadow.CANRMP.all = 0x0;
      ECanaShadow.CANRMP.bit.RMP11 = 1;
                                    /* request clear RMP for this mailbox only*/
      ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
                                    /* 32-bit register access is reliable only*/
      EDIS;
      uint16_T len = ECanaMboxes.MBOX11.MSGCTRL.bit.DLC;
      unsigned char rxMsgData[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };

      uint16_T idx = 0;
      for (idx = 0; idx<len; idx++) {
        if (idx<len) {
          switch (idx){
           case 0:
            rxMsgData[3] = ECanaMboxes.MBOX11.MDL.byte.BYTE3;
            break;

           case 1:
            rxMsgData[2] = ECanaMboxes.MBOX11.MDL.byte.BYTE2;
            break;

           case 2:
            rxMsgData[1] = ECanaMboxes.MBOX11.MDL.byte.BYTE1;
            break;

           case 3:
            rxMsgData[0] = ECanaMboxes.MBOX11.MDL.byte.BYTE0;
            break;

           case 4:
            rxMsgData[7] = ECanaMboxes.MBOX11.MDH.byte.BYTE7;
            break;

           case 5:
            rxMsgData[6] = ECanaMboxes.MBOX11.MDH.byte.BYTE6;
            break;

           case 6:
            rxMsgData[5] = ECanaMboxes.MBOX11.MDH.byte.BYTE5;
            break;

           case 7:
            rxMsgData[4] = ECanaMboxes.MBOX11.MDH.byte.BYTE4;
            break;
          }
        }
      }

      HRXDUAL_Delay_B.eCANReceive9_o2.Extended =
        ECanaMboxes.MBOX11.MSGID.bit.IDE;
      HRXDUAL_Delay_B.eCANReceive9_o2.Length =
        ECanaMboxes.MBOX11.MSGCTRL.bit.DLC;
      uint32_T msgID = ECanaMboxes.MBOX11.MSGID.all;
      if (ECanaMboxes.MBOX11.MSGID.bit.IDE) {
        HRXDUAL_Delay_B.eCANReceive9_o2.ID = (uint32_T)(msgID & ((uint32_T)
          0x1FFFFFFF));
      } else {
        HRXDUAL_Delay_B.eCANReceive9_o2.ID = ((uint32_T)(msgID & ((uint32_T)
          0x1FFC0000))>>18);
      }

      HRXDUAL_Delay_B.eCANReceive9_o2.Data[3] = rxMsgData[0];
      HRXDUAL_Delay_B.eCANReceive9_o2.Data[2] = rxMsgData[1];
      HRXDUAL_Delay_B.eCANReceive9_o2.Data[1] = rxMsgData[2];
      HRXDUAL_Delay_B.eCANReceive9_o2.Data[0] = rxMsgData[3];
      HRXDUAL_Delay_B.eCANReceive9_o2.Data[7] = rxMsgData[4];
      HRXDUAL_Delay_B.eCANReceive9_o2.Data[6] = rxMsgData[5];
      HRXDUAL_Delay_B.eCANReceive9_o2.Data[5] = rxMsgData[6];
      HRXDUAL_Delay_B.eCANReceive9_o2.Data[4] = rxMsgData[7];

      /* -- Call CAN RX Fcn-Call_0 -- */
    }
  }

  /* S-Function (scanunpack): '<S13>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<S13>/CAN Unpack' */
    if ((2 == HRXDUAL_Delay_B.eCANReceive9_o2.Length) &&
        (HRXDUAL_Delay_B.eCANReceive9_o2.ID != INVALID_CAN_ID) ) {
      (void) memcpy(&HRXDUAL_Delay_B.CANUnpack_hx[0],
                    HRXDUAL_Delay_B.eCANReceive9_o2.Data,
                    2 * sizeof(uint16_T));
    }
  }

  /* Gain: '<Root>/Gain' incorporates:
   *  ArithShift: '<S5>/Shift Arithmetic'
   *  DataTypeConversion: '<S4>/Data Type Conversion18'
   *  DataTypeConversion: '<S5>/Data Type Conversion21'
   *  S-Function (scanunpack): '<S5>/CAN Unpack'
   *  S-Function (sfix_bitop): '<S5>/Bitwise OR'
   */
  Gain = (real_T)((int16_T)HRXDUAL_Delay_B.CANUnpack_k[1] << 8U | (int16_T)
                  HRXDUAL_Delay_B.CANUnpack_k[0]) * HRXDUAL_Delay_P.Gain_Gain;

  /* Gain: '<Root>/Gain1' incorporates:
   *  ArithShift: '<S7>/Shift Arithmetic'
   *  DataTypeConversion: '<S4>/Data Type Conversion2'
   *  DataTypeConversion: '<S7>/Data Type Conversion21'
   *  S-Function (scanunpack): '<S7>/CAN Unpack'
   *  S-Function (sfix_bitop): '<S7>/Bitwise OR'
   */
  Gain1 = (real_T)((int16_T)HRXDUAL_Delay_B.CANUnpack_j[1] << 8U | (int16_T)
                   HRXDUAL_Delay_B.CANUnpack_j[0]) * HRXDUAL_Delay_P.Gain1_Gain;

  /* Gain: '<S4>/Pulses to rad1' incorporates:
   *  ArithShift: '<S8>/Shift Arithmetic'
   *  ArithShift: '<S8>/Shift Arithmetic1'
   *  ArithShift: '<S8>/Shift Arithmetic2'
   *  DataTypeConversion: '<S4>/Data Type Conversion4'
   *  DataTypeConversion: '<S8>/Data Type Conversion21'
   *  S-Function (scanunpack): '<S8>/CAN Unpack'
   *  S-Function (sfix_bitop): '<S8>/Bitwise OR'
   */
  Pulsestorad1 = (real_T)((int32_T)HRXDUAL_Delay_B.CANUnpack_jh[1] << 8U |
    HRXDUAL_Delay_B.CANUnpack_jh[0] | (int32_T)HRXDUAL_Delay_B.CANUnpack_jh[2] <<
    16U | (int32_T)HRXDUAL_Delay_B.CANUnpack_jh[3] << 24U) *
    HRXDUAL_Delay_P.Pulsestorad1_Gain;

  /* Gain: '<S4>/Pulses to rad2' incorporates:
   *  ArithShift: '<S10>/Shift Arithmetic'
   *  ArithShift: '<S10>/Shift Arithmetic1'
   *  ArithShift: '<S10>/Shift Arithmetic2'
   *  DataTypeConversion: '<S10>/Data Type Conversion21'
   *  DataTypeConversion: '<S4>/Data Type Conversion5'
   *  S-Function (scanunpack): '<S10>/CAN Unpack'
   *  S-Function (sfix_bitop): '<S10>/Bitwise OR'
   */
  Pulsestorad2 = (real_T)((int32_T)HRXDUAL_Delay_B.CANUnpack_o[1] << 8U |
    HRXDUAL_Delay_B.CANUnpack_o[0] | (int32_T)HRXDUAL_Delay_B.CANUnpack_o[2] <<
    16U | (int32_T)HRXDUAL_Delay_B.CANUnpack_o[3] << 24U) *
    HRXDUAL_Delay_P.Pulsestorad2_Gain;

  /* S-Function (sfix_bitop): '<S13>/Bitwise OR' incorporates:
   *  ArithShift: '<S13>/Shift Arithmetic'
   *  DataTypeConversion: '<S13>/Data Type Conversion21'
   *  S-Function (scanunpack): '<S13>/CAN Unpack'
   */
  rtb_BitwiseOR_nt = (int16_T)HRXDUAL_Delay_B.CANUnpack_hx[1] << 8U | (int16_T)
    HRXDUAL_Delay_B.CANUnpack_hx[0];

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  ArithShift: '<S11>/Shift Arithmetic'
   *  ArithShift: '<S11>/Shift Arithmetic1'
   *  ArithShift: '<S11>/Shift Arithmetic2'
   *  ArithShift: '<S12>/Shift Arithmetic'
   *  ArithShift: '<S12>/Shift Arithmetic1'
   *  ArithShift: '<S12>/Shift Arithmetic2'
   *  ArithShift: '<S6>/Shift Arithmetic'
   *  Clock: '<Root>/Clock'
   *  DataTypeConversion: '<S11>/Data Type Conversion21'
   *  DataTypeConversion: '<S12>/Data Type Conversion21'
   *  DataTypeConversion: '<S4>/Data Type Conversion6'
   *  DataTypeConversion: '<S4>/Data Type Conversion7'
   *  DataTypeConversion: '<S6>/Data Type Conversion21'
   *  Gain: '<S4>/RPM to rad//s1'
   *  Gain: '<S4>/RPM to rad//s2'
   *  S-Function (scanunpack): '<S11>/CAN Unpack'
   *  S-Function (scanunpack): '<S12>/CAN Unpack'
   *  S-Function (scanunpack): '<S6>/CAN Unpack'
   *  S-Function (sfix_bitop): '<S11>/Bitwise OR'
   *  S-Function (sfix_bitop): '<S12>/Bitwise OR'
   *  S-Function (sfix_bitop): '<S6>/Bitwise OR'
   */
  for (j = 0; j < 499; j++) {
    pos_list_tmp = (j + 1) * 3;
    HRXDUAL_Delay_DW.pos_list[3 * j] = HRXDUAL_Delay_DW.pos_list[pos_list_tmp];
    HRXDUAL_Delay_DW.pos_list[3 * j + 1] =
      HRXDUAL_Delay_DW.pos_list[pos_list_tmp + 1];
    HRXDUAL_Delay_DW.pos_list[3 * j + 2] =
      HRXDUAL_Delay_DW.pos_list[pos_list_tmp + 2];
  }

  HRXDUAL_Delay_DW.pos_list[1497] = Pulsestorad1 + 1.994;
  HRXDUAL_Delay_DW.pos_list[1498] = Pulsestorad2 + 1.835;
  HRXDUAL_Delay_DW.pos_list[1499] = HRXDUAL_Delay_M->Timing.t[0];
  delayed_pos1 = Pulsestorad1 + 1.994;
  delayed_pos2 = Pulsestorad2 + 1.835;
  k = 0.0;
  exitg1 = false;
  while ((!exitg1) && (500.0 - k >= 1.0)) {
    j = ((int16_T)(500.0 - k) - 1) * 3;
    if (HRXDUAL_Delay_DW.pos_list[j + 2] >= HRXDUAL_Delay_DW.pos_list[1499] -
        (real_T)rtb_BitwiseOR_nt / 1000.0) {
      delayed_pos1 = HRXDUAL_Delay_DW.pos_list[j];
      delayed_pos2 = HRXDUAL_Delay_DW.pos_list[j + 1];
      k++;
    } else {
      exitg1 = true;
    }
  }

  switch ((int16_T)HRXDUAL_Delay_B.CANUnpack[1] << 8U | (int16_T)
          HRXDUAL_Delay_B.CANUnpack[0]) {
   case 1:
    Pulsestorad1 = 0.0;
    Gain = 0.0;
    break;

   case 2:
    Pulsestorad1 = (real_T)((int32_T)HRXDUAL_Delay_B.CANUnpack_h[1] << 8U |
      HRXDUAL_Delay_B.CANUnpack_h[0] | (int32_T)HRXDUAL_Delay_B.CANUnpack_h[2] <<
      16U | (int32_T)HRXDUAL_Delay_B.CANUnpack_h[3] << 24U) *
      HRXDUAL_Delay_P.RPMtorads1_Gain * -Gain;
    Gain = (real_T)((int32_T)HRXDUAL_Delay_B.CANUnpack_n[1] << 8U |
                    HRXDUAL_Delay_B.CANUnpack_n[0] | (int32_T)
                    HRXDUAL_Delay_B.CANUnpack_n[2] << 16U | (int32_T)
                    HRXDUAL_Delay_B.CANUnpack_n[3] << 24U) *
      HRXDUAL_Delay_P.RPMtorads2_Gain * -Gain;
    break;

   case 3:
    Pulsestorad1 = ((Pulsestorad1 + 1.994) - delayed_pos2) * -Gain1;
    Gain = ((Pulsestorad2 + 1.835) - delayed_pos1) * -Gain1;
    break;

   case 4:
    Pulsestorad1 = ((Pulsestorad1 + 1.994) - delayed_pos2) * -Gain1 - (real_T)
      ((int32_T)HRXDUAL_Delay_B.CANUnpack_h[1] << 8U |
       HRXDUAL_Delay_B.CANUnpack_h[0] | (int32_T)HRXDUAL_Delay_B.CANUnpack_h[2] <<
       16U | (int32_T)HRXDUAL_Delay_B.CANUnpack_h[3] << 24U) *
      HRXDUAL_Delay_P.RPMtorads1_Gain * Gain;
    Gain = ((Pulsestorad2 + 1.835) - delayed_pos1) * -Gain1 - (real_T)((int32_T)
      HRXDUAL_Delay_B.CANUnpack_n[1] << 8U | HRXDUAL_Delay_B.CANUnpack_n[0] |
      (int32_T)HRXDUAL_Delay_B.CANUnpack_n[2] << 16U | (int32_T)
      HRXDUAL_Delay_B.CANUnpack_n[3] << 24U) * HRXDUAL_Delay_P.RPMtorads2_Gain *
      Gain;
    break;

   default:
    Pulsestorad1 = 0.0;
    Gain = 0.0;
    break;
  }

  Gain1 = 1000.0 * Pulsestorad1;
  if (Gain1 < 0.0) {
    Gain1 = ceil(Gain1);
  } else {
    Gain1 = floor(Gain1);
  }

  /* Saturate: '<Root>/Saturation' */
  if (Gain1 > HRXDUAL_Delay_P.Saturation_UpperSat) {
    Gain1 = HRXDUAL_Delay_P.Saturation_UpperSat;
  } else if (Gain1 < HRXDUAL_Delay_P.Saturation_LowerSat) {
    Gain1 = HRXDUAL_Delay_P.Saturation_LowerSat;
  }

  /* DataTypeConversion: '<S1>/Data Type Conversion19' incorporates:
   *  Saturate: '<Root>/Saturation'
   */
  Gain1 = floor(Gain1);
  if (rtIsNaN(Gain1) || rtIsInf(Gain1)) {
    Gain1 = 0.0;
  } else {
    Gain1 = fmod(Gain1, 65536.0);
  }

  rtb_BitwiseOR_nt = Gain1 < 0.0 ? -(int16_T)(uint16_T)-Gain1 : (int16_T)
    (uint16_T)Gain1;

  /* End of DataTypeConversion: '<S1>/Data Type Conversion19' */

  /* SignalConversion generated from: '<S1>/CAN Pack' incorporates:
   *  ArithShift: '<S1>/Shift Arithmetic3'
   *  ArithShift: '<S2>/Shift Arithmetic3'
   *  DataTypeConversion: '<S1>/Data Type Conversion25'
   *  DataTypeConversion: '<S1>/Data Type Conversion26'
   */
  HRXDUAL_Delay_B.TmpSignalConversionAtCANPackInp[0] = (uint16_T)
    rtb_BitwiseOR_nt & 255U;
  HRXDUAL_Delay_B.TmpSignalConversionAtCANPackInp[1] = (uint16_T)
    (rtb_BitwiseOR_nt >> 8U) & 255U;

  /* MATLAB Function: '<Root>/MATLAB Function' */
  Gain1 = 1000.0 * Gain;
  if (Gain1 < 0.0) {
    Gain1 = ceil(Gain1);
  } else {
    Gain1 = floor(Gain1);
  }

  /* Saturate: '<Root>/Saturation1' */
  if (Gain1 > HRXDUAL_Delay_P.Saturation1_UpperSat) {
    Gain1 = HRXDUAL_Delay_P.Saturation1_UpperSat;
  } else if (Gain1 < HRXDUAL_Delay_P.Saturation1_LowerSat) {
    Gain1 = HRXDUAL_Delay_P.Saturation1_LowerSat;
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion19' incorporates:
   *  Saturate: '<Root>/Saturation1'
   */
  Gain1 = floor(Gain1);
  if (rtIsNaN(Gain1) || rtIsInf(Gain1)) {
    Gain1 = 0.0;
  } else {
    Gain1 = fmod(Gain1, 65536.0);
  }

  rtb_BitwiseOR_nt = Gain1 < 0.0 ? -(int16_T)(uint16_T)-Gain1 : (int16_T)
    (uint16_T)Gain1;

  /* End of DataTypeConversion: '<S2>/Data Type Conversion19' */

  /* SignalConversion generated from: '<S2>/CAN Pack' incorporates:
   *  ArithShift: '<S2>/Shift Arithmetic3'
   *  DataTypeConversion: '<S2>/Data Type Conversion19'
   *  DataTypeConversion: '<S2>/Data Type Conversion25'
   *  DataTypeConversion: '<S2>/Data Type Conversion26'
   */
  HRXDUAL_Delay_B.TmpSignalConversionAtCANPackI_a[0] = (uint16_T)
    rtb_BitwiseOR_nt & 255U;
  HRXDUAL_Delay_B.TmpSignalConversionAtCANPackI_a[1] = (uint16_T)
    (rtb_BitwiseOR_nt >> 8U) & 255U;

  /* S-Function (scanpack): '<S1>/CAN Pack' */
  /* S-Function (scanpack): '<S1>/CAN Pack' */
  HRXDUAL_Delay_B.CANPack.ID = 769U;
  HRXDUAL_Delay_B.CANPack.Length = 2U;
  HRXDUAL_Delay_B.CANPack.Extended = 0U;
  HRXDUAL_Delay_B.CANPack.Remote = 0;
  HRXDUAL_Delay_B.CANPack.Data[0] = 0;
  HRXDUAL_Delay_B.CANPack.Data[1] = 0;
  HRXDUAL_Delay_B.CANPack.Data[2] = 0;
  HRXDUAL_Delay_B.CANPack.Data[3] = 0;
  HRXDUAL_Delay_B.CANPack.Data[4] = 0;
  HRXDUAL_Delay_B.CANPack.Data[5] = 0;
  HRXDUAL_Delay_B.CANPack.Data[6] = 0;
  HRXDUAL_Delay_B.CANPack.Data[7] = 0;

  {
    (void) memcpy((HRXDUAL_Delay_B.CANPack.Data),
                  &HRXDUAL_Delay_B.TmpSignalConversionAtCANPackInp[0],
                  2 * sizeof(uint16_T));
  }

  /* S-Function (c280xcanxmt): '<S1>/eCAN Transmit3' */
  {
    uint32_T messageID = HRXDUAL_Delay_B.CANPack.ID;
    uint16_T isExtended = HRXDUAL_Delay_B.CANPack.Extended;
    config_eCAN_A_mbx (1U, 1,messageID, isExtended, 0U, 0U);
    struct ECAN_REGS ECanaShadow;
    EALLOW;
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = HRXDUAL_Delay_B.CANPack.Length;
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.all &= ~((uint32_T)0x1 << 1);
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX1.MSGID.all &= ~((uint32_T) 0x1FFFFFFF);
    if (isExtended) {
      ECanaMboxes.MBOX1.MSGID.all |= (0x1FFFFFFF & ((uint32_T)
        HRXDUAL_Delay_B.CANPack.ID));
    } else {
      ECanaMboxes.MBOX1.MSGID.all |= (0x1FFFFFFF & ((uint32_T)
        (HRXDUAL_Delay_B.CANPack.ID) << 18));
    }

    ECanaShadow.CANME.all |= ((uint32_T)0x1 << 1);
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX1.MDL.byte.BYTE0 = HRXDUAL_Delay_B.CANPack.Data[3];
    ECanaMboxes.MBOX1.MDL.byte.BYTE1 = HRXDUAL_Delay_B.CANPack.Data[2];
    ECanaMboxes.MBOX1.MDL.byte.BYTE2 = HRXDUAL_Delay_B.CANPack.Data[1];
    ECanaMboxes.MBOX1.MDL.byte.BYTE3 = HRXDUAL_Delay_B.CANPack.Data[0];
    ECanaMboxes.MBOX1.MDH.byte.BYTE4 = HRXDUAL_Delay_B.CANPack.Data[7];
    ECanaMboxes.MBOX1.MDH.byte.BYTE5 = HRXDUAL_Delay_B.CANPack.Data[6];
    ECanaMboxes.MBOX1.MDH.byte.BYTE6 = HRXDUAL_Delay_B.CANPack.Data[5];
    ECanaMboxes.MBOX1.MDH.byte.BYTE7 = HRXDUAL_Delay_B.CANPack.Data[4];
    ECanaRegs.CANTRS.all = (((uint32_T) 0x00000001) << 1);
    EDIS;
    while (ECanaRegs.CANTA.bit.TA1 != 1 ) {
    }                              /* check eCAN Transmit Acknowledge register*/

    ECanaRegs.CANTA.bit.TA1 = 1;
                             /* clear eCAN Transmit Acknowledge register 	    */
  }

  /* S-Function (scanpack): '<S2>/CAN Pack' */
  /* S-Function (scanpack): '<S2>/CAN Pack' */
  HRXDUAL_Delay_B.CANPack_p.ID = 770U;
  HRXDUAL_Delay_B.CANPack_p.Length = 2U;
  HRXDUAL_Delay_B.CANPack_p.Extended = 0U;
  HRXDUAL_Delay_B.CANPack_p.Remote = 0;
  HRXDUAL_Delay_B.CANPack_p.Data[0] = 0;
  HRXDUAL_Delay_B.CANPack_p.Data[1] = 0;
  HRXDUAL_Delay_B.CANPack_p.Data[2] = 0;
  HRXDUAL_Delay_B.CANPack_p.Data[3] = 0;
  HRXDUAL_Delay_B.CANPack_p.Data[4] = 0;
  HRXDUAL_Delay_B.CANPack_p.Data[5] = 0;
  HRXDUAL_Delay_B.CANPack_p.Data[6] = 0;
  HRXDUAL_Delay_B.CANPack_p.Data[7] = 0;

  {
    (void) memcpy((HRXDUAL_Delay_B.CANPack_p.Data),
                  &HRXDUAL_Delay_B.TmpSignalConversionAtCANPackI_a[0],
                  2 * sizeof(uint16_T));
  }

  /* S-Function (c280xcanxmt): '<S2>/eCAN Transmit3' */
  {
    uint32_T messageID = HRXDUAL_Delay_B.CANPack_p.ID;
    uint16_T isExtended = HRXDUAL_Delay_B.CANPack_p.Extended;
    config_eCAN_A_mbx (1U, 2,messageID, isExtended, 0U, 0U);
    struct ECAN_REGS ECanaShadow;
    EALLOW;
    ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = HRXDUAL_Delay_B.CANPack_p.Length;
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.all &= ~((uint32_T)0x1 << 2);
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX2.MSGID.all &= ~((uint32_T) 0x1FFFFFFF);
    if (isExtended) {
      ECanaMboxes.MBOX2.MSGID.all |= (0x1FFFFFFF & ((uint32_T)
        HRXDUAL_Delay_B.CANPack_p.ID));
    } else {
      ECanaMboxes.MBOX2.MSGID.all |= (0x1FFFFFFF & ((uint32_T)
        (HRXDUAL_Delay_B.CANPack_p.ID) << 18));
    }

    ECanaShadow.CANME.all |= ((uint32_T)0x1 << 2);
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX2.MDL.byte.BYTE0 = HRXDUAL_Delay_B.CANPack_p.Data[3];
    ECanaMboxes.MBOX2.MDL.byte.BYTE1 = HRXDUAL_Delay_B.CANPack_p.Data[2];
    ECanaMboxes.MBOX2.MDL.byte.BYTE2 = HRXDUAL_Delay_B.CANPack_p.Data[1];
    ECanaMboxes.MBOX2.MDL.byte.BYTE3 = HRXDUAL_Delay_B.CANPack_p.Data[0];
    ECanaMboxes.MBOX2.MDH.byte.BYTE4 = HRXDUAL_Delay_B.CANPack_p.Data[7];
    ECanaMboxes.MBOX2.MDH.byte.BYTE5 = HRXDUAL_Delay_B.CANPack_p.Data[6];
    ECanaMboxes.MBOX2.MDH.byte.BYTE6 = HRXDUAL_Delay_B.CANPack_p.Data[5];
    ECanaMboxes.MBOX2.MDH.byte.BYTE7 = HRXDUAL_Delay_B.CANPack_p.Data[4];
    ECanaRegs.CANTRS.all = (((uint32_T) 0x00000001) << 2);
    EDIS;
    while (ECanaRegs.CANTA.bit.TA2 != 1 ) {
    }                              /* check eCAN Transmit Acknowledge register*/

    ECanaRegs.CANTA.bit.TA2 = 1;
                             /* clear eCAN Transmit Acknowledge register 	    */
  }

  /* Outputs for Enabled SubSystem: '<S4>/Subsystem5' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  /* Logic: '<S4>/Logical Operator2' incorporates:
   *  Delay: '<S4>/Delay'
   */
  if (!(HRXDUAL_Delay_DW.Delay_DSTATE != 0.0)) {
    /* DataTypeConversion: '<S9>/Data Type Conversion1' incorporates:
     *  Constant: '<S9>/Constant1'
     */
    Gain1 = floor(HRXDUAL_Delay_P.Constant1_Value);
    if (rtIsNaN(Gain1) || rtIsInf(Gain1)) {
      Gain1 = 0.0;
    } else {
      Gain1 = fmod(Gain1, 256.0);
    }

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Subsystem1'
     */
    /* SignalConversion generated from: '<S28>/CAN Pack' incorporates:
     *  DataTypeConversion: '<S9>/Data Type Conversion1'
     */
    HRXDUAL_Delay_B.TmpSignalConversionAtCANPack_aw[0] = (uint16_T)(int16_T)
      Gain1 & 255U;

    /* End of Outputs for S-Function (fcgen): '<S9>/Function-Call Generator1' */

    /* DataTypeConversion: '<S9>/Data Type Conversion2' incorporates:
     *  Constant: '<S9>/Constant2'
     */
    Gain1 = floor(HRXDUAL_Delay_P.Constant2_Value);
    if (rtIsNaN(Gain1) || rtIsInf(Gain1)) {
      Gain1 = 0.0;
    } else {
      Gain1 = fmod(Gain1, 256.0);
    }

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Subsystem1'
     */
    /* SignalConversion generated from: '<S28>/CAN Pack' incorporates:
     *  DataTypeConversion: '<S9>/Data Type Conversion2'
     */
    HRXDUAL_Delay_B.TmpSignalConversionAtCANPack_aw[1] = (uint16_T)(int16_T)
      Gain1 & 255U;

    /* S-Function (scanpack): '<S28>/CAN Pack' */
    /* S-Function (scanpack): '<S28>/CAN Pack' */
    HRXDUAL_Delay_B.CANPack_pu.ID = 0U;
    HRXDUAL_Delay_B.CANPack_pu.Length = 2U;
    HRXDUAL_Delay_B.CANPack_pu.Extended = 0U;
    HRXDUAL_Delay_B.CANPack_pu.Remote = 0;
    HRXDUAL_Delay_B.CANPack_pu.Data[0] = 0;
    HRXDUAL_Delay_B.CANPack_pu.Data[1] = 0;
    HRXDUAL_Delay_B.CANPack_pu.Data[2] = 0;
    HRXDUAL_Delay_B.CANPack_pu.Data[3] = 0;
    HRXDUAL_Delay_B.CANPack_pu.Data[4] = 0;
    HRXDUAL_Delay_B.CANPack_pu.Data[5] = 0;
    HRXDUAL_Delay_B.CANPack_pu.Data[6] = 0;
    HRXDUAL_Delay_B.CANPack_pu.Data[7] = 0;

    {
      (void) memcpy((HRXDUAL_Delay_B.CANPack_pu.Data),
                    &HRXDUAL_Delay_B.TmpSignalConversionAtCANPack_aw[0],
                    2 * sizeof(uint16_T));
    }

    /* S-Function (c280xcanxmt): '<S28>/eCAN Transmit3' */
    {
      uint32_T messageID = HRXDUAL_Delay_B.CANPack_pu.ID;
      uint16_T isExtended = HRXDUAL_Delay_B.CANPack_pu.Extended;
      config_eCAN_A_mbx (1U, 0,messageID, isExtended, 0U, 0U);
      struct ECAN_REGS ECanaShadow;
      EALLOW;
      ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = HRXDUAL_Delay_B.CANPack_pu.Length;
      ECanaShadow.CANME.all = ECanaRegs.CANME.all;
      ECanaShadow.CANME.all &= ~((uint32_T)0x1 << 0);
      ECanaRegs.CANME.all = ECanaShadow.CANME.all;
      ECanaMboxes.MBOX0.MSGID.all &= ~((uint32_T) 0x1FFFFFFF);
      if (isExtended) {
        ECanaMboxes.MBOX0.MSGID.all |= (0x1FFFFFFF & ((uint32_T)
          HRXDUAL_Delay_B.CANPack_pu.ID));
      } else {
        ECanaMboxes.MBOX0.MSGID.all |= (0x1FFFFFFF & ((uint32_T)
          (HRXDUAL_Delay_B.CANPack_pu.ID) << 18));
      }

      ECanaShadow.CANME.all |= ((uint32_T)0x1 << 0);
      ECanaRegs.CANME.all = ECanaShadow.CANME.all;
      ECanaMboxes.MBOX0.MDL.byte.BYTE0 = HRXDUAL_Delay_B.CANPack_pu.Data[3];
      ECanaMboxes.MBOX0.MDL.byte.BYTE1 = HRXDUAL_Delay_B.CANPack_pu.Data[2];
      ECanaMboxes.MBOX0.MDL.byte.BYTE2 = HRXDUAL_Delay_B.CANPack_pu.Data[1];
      ECanaMboxes.MBOX0.MDL.byte.BYTE3 = HRXDUAL_Delay_B.CANPack_pu.Data[0];
      ECanaMboxes.MBOX0.MDH.byte.BYTE4 = HRXDUAL_Delay_B.CANPack_pu.Data[7];
      ECanaMboxes.MBOX0.MDH.byte.BYTE5 = HRXDUAL_Delay_B.CANPack_pu.Data[6];
      ECanaMboxes.MBOX0.MDH.byte.BYTE6 = HRXDUAL_Delay_B.CANPack_pu.Data[5];
      ECanaMboxes.MBOX0.MDH.byte.BYTE7 = HRXDUAL_Delay_B.CANPack_pu.Data[4];
      ECanaRegs.CANTRS.all = (((uint32_T) 0x00000001) << 0);
      EDIS;
      while (ECanaRegs.CANTA.bit.TA0 != 1 ) {
      }                            /* check eCAN Transmit Acknowledge register*/

      ECanaRegs.CANTA.bit.TA0 = 1;
                             /* clear eCAN Transmit Acknowledge register 	    */
    }

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Delay 1ms4'
     */
    HRXDUAL_Delay_Delay1ms4();

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Set Torque Mode of Operation (PDO)1'
     */
    HR_SetTorqueModeofOperationPDO1
      (&HRXDUAL_Delay_B.SetTorqueModeofOperationPDO1,
       &HRXDUAL_Delay_P.SetTorqueModeofOperationPDO1);

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Delay 1ms5'
     */
    HRXDUAL_Delay_Delay1ms4();

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Set Torque Mode of Operation (PDO)2'
     */
    HR_SetTorqueModeofOperationPDO2
      (&HRXDUAL_Delay_B.SetTorqueModeofOperationPDO2,
       &HRXDUAL_Delay_P.SetTorqueModeofOperationPDO2);

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Delay 1ms11'
     */
    HRXDUAL_Delay_Delay1ms4();

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Set Motor Ready (PDO)1'
     */
    HR_SetTorqueModeofOperationPDO1(&HRXDUAL_Delay_B.SetMotorReadyPDO1,
      &HRXDUAL_Delay_P.SetMotorReadyPDO1);

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Delay 1ms6'
     */
    HRXDUAL_Delay_Delay1ms4();

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Set Motor2 Ready (PDO)2'
     */
    HR_SetTorqueModeofOperationPDO2(&HRXDUAL_Delay_B.SetMotor2ReadyPDO2,
      &HRXDUAL_Delay_P.SetMotor2ReadyPDO2);

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Delay 1ms10'
     */
    HRXDUAL_Delay_Delay1ms4();

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Switch On Motor (PDO)1'
     */
    HR_SetTorqueModeofOperationPDO1(&HRXDUAL_Delay_B.SwitchOnMotorPDO1,
      &HRXDUAL_Delay_P.SwitchOnMotorPDO1);

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Delay 1ms7'
     */
    HRXDUAL_Delay_Delay1ms4();

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Switch On Motor2 (PDO)2'
     */
    HR_SetTorqueModeofOperationPDO2(&HRXDUAL_Delay_B.SwitchOnMotor2PDO2,
      &HRXDUAL_Delay_P.SwitchOnMotor2PDO2);

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Delay 1ms9'
     */
    HRXDUAL_Delay_Delay1ms4();

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Enable Motor (PDO)2'
     */
    HR_SetTorqueModeofOperationPDO1(&HRXDUAL_Delay_B.EnableMotorPDO2,
      &HRXDUAL_Delay_P.EnableMotorPDO2);

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Delay 1ms8'
     */
    HRXDUAL_Delay_Delay1ms4();

    /* S-Function (fcgen): '<S9>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S9>/Enable Motor2 (PDO)3'
     */
    HR_SetTorqueModeofOperationPDO2(&HRXDUAL_Delay_B.EnableMotor2PDO3,
      &HRXDUAL_Delay_P.EnableMotor2PDO3);

    /* End of Outputs for S-Function (fcgen): '<S9>/Function-Call Generator1' */
  }

  /* End of Logic: '<S4>/Logical Operator2' */
  /* End of Outputs for SubSystem: '<S4>/Subsystem5' */

  /* Update for Delay: '<S4>/Delay' incorporates:
   *  Constant: '<S4>/Constant20'
   */
  HRXDUAL_Delay_DW.Delay_DSTATE = HRXDUAL_Delay_P.Constant20_Value;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  HRXDUAL_Delay_M->Timing.t[0] =
    ((time_T)(++HRXDUAL_Delay_M->Timing.clockTick0)) *
    HRXDUAL_Delay_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.0001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.0001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    HRXDUAL_Delay_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void HRXDUAL_Delay_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)HRXDUAL_Delay_M, 0,
                sizeof(RT_MODEL_HRXDUAL_Delay_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&HRXDUAL_Delay_M->solverInfo,
                          &HRXDUAL_Delay_M->Timing.simTimeStep);
    rtsiSetTPtr(&HRXDUAL_Delay_M->solverInfo, &rtmGetTPtr(HRXDUAL_Delay_M));
    rtsiSetStepSizePtr(&HRXDUAL_Delay_M->solverInfo,
                       &HRXDUAL_Delay_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&HRXDUAL_Delay_M->solverInfo, (&rtmGetErrorStatus
      (HRXDUAL_Delay_M)));
    rtsiSetRTModelPtr(&HRXDUAL_Delay_M->solverInfo, HRXDUAL_Delay_M);
  }

  rtsiSetSimTimeStep(&HRXDUAL_Delay_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&HRXDUAL_Delay_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(HRXDUAL_Delay_M, &HRXDUAL_Delay_M->Timing.tArray[0]);
  HRXDUAL_Delay_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &HRXDUAL_Delay_B), 0,
                sizeof(B_HRXDUAL_Delay_T));

  {
    HRXDUAL_Delay_B.eCANReceive1_o2 = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.eCANReceive2_o2 = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.eCANReceive3_o2 = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.eCANReceive5_o2 = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.eCANReceive7_o2 = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.eCANReceive6_o2 = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.eCANReceive8_o2 = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.eCANReceive9_o2 = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.CANPack = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.CANPack_p = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.CANPack_pu = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.EnableMotor2PDO3.CANPack = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.EnableMotorPDO2.CANPack = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.SwitchOnMotor2PDO2.CANPack = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.SwitchOnMotorPDO1.CANPack = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.SetMotor2ReadyPDO2.CANPack = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.SetMotorReadyPDO1.CANPack = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.SetTorqueModeofOperationPDO2.CANPack = CAN_DATATYPE_GROUND;
    HRXDUAL_Delay_B.SetTorqueModeofOperationPDO1.CANPack = CAN_DATATYPE_GROUND;
  }

  /* states (dwork) */
  (void) memset((void *)&HRXDUAL_Delay_DW, 0,
                sizeof(DW_HRXDUAL_Delay_T));

  /* Start for S-Function (c280xcanrcv): '<S4>/eCAN Receive1' */

  /* Configure mailbox 7 to receive messages with the ID: 0x666 */
  config_eCAN_A_mbx (0U, 7, 0x666, 0, 0, 0x0);

  /* Initialize out port */
  {
    HRXDUAL_Delay_B.eCANReceive1_o2.Extended = 0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Length = 8;
    HRXDUAL_Delay_B.eCANReceive1_o2.ID = 0x666;
    HRXDUAL_Delay_B.eCANReceive1_o2.Timestamp = 0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Error = 0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Remote = 0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Data[0] = (uint8_T)1.0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Data[1] = (uint8_T)1.0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Data[2] = (uint8_T)1.0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Data[3] = (uint8_T)1.0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Data[4] = (uint8_T)1.0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Data[5] = (uint8_T)1.0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Data[6] = (uint8_T)1.0;
    HRXDUAL_Delay_B.eCANReceive1_o2.Data[7] = (uint8_T)1.0;
  }

  /* Start for S-Function (scanunpack): '<S6>/CAN Unpack' */

  /*-----------S-Function Block: <S6>/CAN Unpack -----------------*/

  /* Start for S-Function (c280xcanrcv): '<S4>/eCAN Receive2' */

  /* Configure mailbox 8 to receive messages with the ID: 0x667 */
  config_eCAN_A_mbx (0U, 8, 0x667, 0, 0, 0x0);

  /* Initialize out port */
  {
    HRXDUAL_Delay_B.eCANReceive2_o2.Extended = 0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Length = 8;
    HRXDUAL_Delay_B.eCANReceive2_o2.ID = 0x667;
    HRXDUAL_Delay_B.eCANReceive2_o2.Timestamp = 0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Error = 0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Remote = 0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Data[0] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Data[1] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Data[2] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Data[3] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Data[4] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Data[5] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Data[6] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive2_o2.Data[7] = (uint8_T)0.0;
  }

  /* Start for S-Function (scanunpack): '<S5>/CAN Unpack' */

  /*-----------S-Function Block: <S5>/CAN Unpack -----------------*/

  /* Start for S-Function (c280xcanrcv): '<S4>/eCAN Receive3' */

  /* Configure mailbox 9 to receive messages with the ID: 0x668 */
  config_eCAN_A_mbx (0U, 9, 0x668, 0, 0, 0x0);

  /* Initialize out port */
  {
    HRXDUAL_Delay_B.eCANReceive3_o2.Extended = 0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Length = 8;
    HRXDUAL_Delay_B.eCANReceive3_o2.ID = 0x668;
    HRXDUAL_Delay_B.eCANReceive3_o2.Timestamp = 0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Error = 0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Remote = 0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Data[0] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Data[1] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Data[2] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Data[3] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Data[4] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Data[5] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Data[6] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive3_o2.Data[7] = (uint8_T)0.0;
  }

  /* Start for S-Function (scanunpack): '<S7>/CAN Unpack' */

  /*-----------S-Function Block: <S7>/CAN Unpack -----------------*/

  /* Start for S-Function (c280xcanrcv): '<S4>/eCAN Receive5' */

  /* Configure mailbox 3 to receive messages with the ID: 0x381 */
  config_eCAN_A_mbx (0U, 3, 0x381, 0, 0, 0x0);

  /* Initialize out port */
  {
    HRXDUAL_Delay_B.eCANReceive5_o2.Extended = 0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Length = 8;
    HRXDUAL_Delay_B.eCANReceive5_o2.ID = 0x381;
    HRXDUAL_Delay_B.eCANReceive5_o2.Timestamp = 0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Error = 0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Remote = 0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Data[0] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Data[1] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Data[2] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Data[3] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Data[4] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Data[5] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Data[6] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive5_o2.Data[7] = (uint8_T)0.0;
  }

  /* Start for S-Function (scanunpack): '<S8>/CAN Unpack' */

  /*-----------S-Function Block: <S8>/CAN Unpack -----------------*/

  /* Start for S-Function (c280xcanrcv): '<S4>/eCAN Receive7' */

  /* Configure mailbox 5 to receive messages with the ID: 0x481 */
  config_eCAN_A_mbx (0U, 5, 0x481, 0, 0, 0x0);

  /* Initialize out port */
  {
    HRXDUAL_Delay_B.eCANReceive7_o2.Extended = 0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Length = 8;
    HRXDUAL_Delay_B.eCANReceive7_o2.ID = 0x481;
    HRXDUAL_Delay_B.eCANReceive7_o2.Timestamp = 0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Error = 0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Remote = 0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Data[0] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Data[1] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Data[2] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Data[3] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Data[4] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Data[5] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Data[6] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive7_o2.Data[7] = (uint8_T)0.0;
  }

  /* Start for S-Function (scanunpack): '<S11>/CAN Unpack' */

  /*-----------S-Function Block: <S11>/CAN Unpack -----------------*/

  /* Start for S-Function (c280xcanrcv): '<S4>/eCAN Receive6' */

  /* Configure mailbox 4 to receive messages with the ID: 0x382 */
  config_eCAN_A_mbx (0U, 4, 0x382, 0, 0, 0x0);

  /* Initialize out port */
  {
    HRXDUAL_Delay_B.eCANReceive6_o2.Extended = 0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Length = 8;
    HRXDUAL_Delay_B.eCANReceive6_o2.ID = 0x382;
    HRXDUAL_Delay_B.eCANReceive6_o2.Timestamp = 0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Error = 0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Remote = 0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Data[0] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Data[1] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Data[2] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Data[3] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Data[4] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Data[5] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Data[6] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive6_o2.Data[7] = (uint8_T)0.0;
  }

  /* Start for S-Function (scanunpack): '<S10>/CAN Unpack' */

  /*-----------S-Function Block: <S10>/CAN Unpack -----------------*/

  /* Start for S-Function (c280xcanrcv): '<S4>/eCAN Receive8' */

  /* Configure mailbox 6 to receive messages with the ID: 0x482 */
  config_eCAN_A_mbx (0U, 6, 0x482, 0, 0, 0x0);

  /* Initialize out port */
  {
    HRXDUAL_Delay_B.eCANReceive8_o2.Extended = 0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Length = 8;
    HRXDUAL_Delay_B.eCANReceive8_o2.ID = 0x482;
    HRXDUAL_Delay_B.eCANReceive8_o2.Timestamp = 0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Error = 0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Remote = 0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Data[0] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Data[1] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Data[2] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Data[3] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Data[4] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Data[5] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Data[6] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive8_o2.Data[7] = (uint8_T)0.0;
  }

  /* Start for S-Function (scanunpack): '<S12>/CAN Unpack' */

  /*-----------S-Function Block: <S12>/CAN Unpack -----------------*/

  /* Start for S-Function (c280xcanrcv): '<S4>/eCAN Receive9' */

  /* Configure mailbox 11 to receive messages with the ID: 0x66A */
  config_eCAN_A_mbx (0U, 11, 0x66A, 0, 0, 0x0);

  /* Initialize out port */
  {
    HRXDUAL_Delay_B.eCANReceive9_o2.Extended = 0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Length = 8;
    HRXDUAL_Delay_B.eCANReceive9_o2.ID = 0x66A;
    HRXDUAL_Delay_B.eCANReceive9_o2.Timestamp = 0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Error = 0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Remote = 0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Data[0] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Data[1] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Data[2] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Data[3] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Data[4] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Data[5] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Data[6] = (uint8_T)0.0;
    HRXDUAL_Delay_B.eCANReceive9_o2.Data[7] = (uint8_T)0.0;
  }

  /* Start for S-Function (scanunpack): '<S13>/CAN Unpack' */

  /*-----------S-Function Block: <S13>/CAN Unpack -----------------*/

  /* InitializeConditions for Delay: '<S4>/Delay' */
  HRXDUAL_Delay_DW.Delay_DSTATE = HRXDUAL_Delay_P.Delay_InitialCondition;

  /* SystemInitialize for MATLAB Function: '<Root>/MATLAB Function' */
  memset(&HRXDUAL_Delay_DW.pos_list[0], 0, 1500U * sizeof(real_T));
}

/* Model terminate function */
void HRXDUAL_Delay_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
