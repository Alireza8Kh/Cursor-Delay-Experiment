using System.Collections.Generic;
using UnityEngine;
using System;

using Peak.Can.Basic;
using TPCANHandle = System.UInt16;
using TPCANTimestampFD = System.UInt64;

public class CANRecorder : MonoBehaviour
{
    // Number of CAN channels monitored
    private int ChannelCount = 2;
    // Human-readable names for each channel, used when building CANinfo
    private List<string> IDNames = new List<string> { "Position1", "Velocity1" };
    // CAN message IDs: 0x381 = joint position, 0x481 = joint velocity
    private List<uint> CANIDs = new List<uint> { 0x381, 0x481 };
    // Byte length of each message: 4 bytes for position (Int32), 2 bytes for velocity (Int16)
    private List<int> ByteLengths = new List<int> { 4, 2 };

    // Raw bytes read from the CAN bus each FixedUpdate
    private byte[] CANData;
    // Dictionary mapping each CAN ID to its (name, byteLength) pair, built in Start
    private Dictionary<uint, Tuple<string, int>> CANinfo = new Dictionary<uint, Tuple<string, int>>();

    // Decoded robot state — updated every FixedUpdate from incoming CAN messages
    private float pos1 = 0.0f; // joint position [rad], with mechanical offset applied
    private float vel1 = 0.0f; // joint velocity [rad/s]

    void Start()
    {
        // Build the lookup dictionary from the parallel lists above
        CANinfo.Clear();
        for (int i = 0; i < ChannelCount; i++)
            CANinfo.Add(CANIDs[i], Tuple.Create(IDNames[i], ByteLengths[i]));
    }

    private void FixedUpdate()
    {
        // Poll every registered CAN ID and update pos1 / vel1 when new data arrives
        foreach (uint id in CANIDs)
        {
            if (!CANController.GetCANMessageData(id, out CANData)) continue;

            if (CANinfo[id].Item2 == 4 && id == 0x381)
            {
                // 4-byte Int32: convert encoder counts to radians and apply mechanical offset
                pos1 = BitConverter.ToInt32(CANData, 0) * 2 * Mathf.PI / 25600 + 1.994f; // [rad]
            }
            else if (CANinfo[id].Item2 == 2 && id == 0x481)
            {
                // 2-byte Int16: convert RPM-scaled integer to rad/s
                vel1 = BitConverter.ToInt16(CANData, 0) * 2f * Mathf.PI / 60f; // [rad/s]
            }
        }
    }

    // Returns the current robot state by index: 0 = position [rad], 1 = velocity [rad/s]
    public float GetCurrentHRXData(int reqData)
    {
        if (reqData == 0) return pos1;
        if (reqData == 1) return vel1;
        return -1;
    }

    // Sends the joint damping viscosity (joKd) to the robot over CAN.
    // Additional parameters (coKp, coKd, haptic delay) are commented out below for future use.
    public void SendCtrlConfig(float joKd)
    {
        // Scale float to integer (multiply by 1000 to preserve 3 decimal places)
        int joKd_int = (int)(joKd * 1000f);
        // int coKp_int = (int)(coKp * 1000f);
        // int coKd_int = (int)(coKd * 1000f);
        // int th_int   = (int)(th);

        // Convert to Int16 bytes for CAN transmission
        // Int16 ctrlMode_Int16 = Convert.ToInt16(Convert.ToSingle(ctrlMode));
        // byte[] ctrlMode_Byte = BitConverter.GetBytes(ctrlMode_Int16);
        Int16 joKd_Int16 = Convert.ToInt16(Convert.ToSingle(joKd_int));
        byte[] joKd_Byte = BitConverter.GetBytes(joKd_Int16);
        // Int16 coKp_Int16 = Convert.ToInt16(Convert.ToSingle(coKp_int));
        // byte[] coKp_Byte = BitConverter.GetBytes(coKp_Int16);
        // Int16 coKd_Int16 = Convert.ToInt16(Convert.ToSingle(coKd_int));
        // byte[] coKd_Byte = BitConverter.GetBytes(coKd_Int16);
        // Int16 th_Int16   = Convert.ToInt16(Convert.ToSingle(th_int));
        // byte[] th_Byte   = BitConverter.GetBytes(th_Int16);

        // Send active parameters over CAN
        // CANController.SendCANMessage(0x666, 2, ctrlMode_Byte);
        CANController.SendCANMessage(0x667, 2, joKd_Byte);
        // CANController.SendCANMessage(0x668, 2, coKp_Byte);
        // CANController.SendCANMessage(0x669, 2, coKd_Byte);
        // CANController.SendCANMessage(0x66A, 2, th_Byte);
    }
}
