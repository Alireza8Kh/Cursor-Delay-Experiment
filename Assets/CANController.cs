using System;
using UnityEngine;
using System.Threading;
using Peak.Can.Basic;
using System.Collections.Generic;
using TPCANHandle = System.UInt16;
using TPCANTimestampFD = System.UInt64;

public class CANController : MonoBehaviour
{
    private TPCANHandle PCANhandle = 0;

    private bool m_DLLFound;
    private Thread m_ReadThread;
    private bool m_ThreadRun;

    private static IDictionary<uint, TPCANMsg> inCANMessages  = new Dictionary<uint, TPCANMsg>();
    private static IDictionary<uint, TPCANMsg> outCANMessages = new Dictionary<uint, TPCANMsg>();

    void Awake()
    {
        Time.fixedDeltaTime = 0.001f;

        m_DLLFound = CheckForLibrary();
        if (!m_DLLFound) return;

        PCANhandle = GetPCANHandle();
        if (PCANhandle == 0) return;

        TPCANStatus PCANStatus = PCANBasic.Initialize(PCANhandle, TPCANBaudrate.PCAN_BAUD_1M);
        if (PCANStatus != TPCANStatus.PCAN_ERROR_OK)
        {
            Debug.Log("PCAN Initialize Failed");
            Debug.Log(GetFormattedError(PCANStatus));
            return;
        }

        m_ReadThread = new Thread(new ThreadStart(ThreadExecute));
        m_ThreadRun  = true;
        m_ReadThread.Start();
    }

    void FixedUpdate()
    {
        SendCANMessages();
    }

    public static bool GetCANMessageData(uint ID, out byte[] data)
    {
        data = new byte[] { };
        if (inCANMessages.ContainsKey(ID))
        {
            data = inCANMessages[ID].DATA;
            return true;
        }
        return false;
    }

    // Adds a message to the outgoing queue (overwrites if same ID already queued this frame)
    public static void SendCANMessage(uint CanID, byte len, byte[] data)
    {
        var msg = new TPCANMsg();
        msg.DATA    = data;
        msg.ID      = CanID;
        msg.LEN     = len; // if len < data.Length the message is cropped to len bytes
        msg.MSGTYPE = TPCANMessageType.PCAN_MESSAGE_STANDARD;

        outCANMessages[CanID] = msg;
    }

    private void SendCANMessages()
    {
        foreach (var kvp in outCANMessages)
            WriteCANMessage(kvp.Value);

        outCANMessages.Clear();
    }

    private void WriteCANMessage(TPCANMsg msg)
    {
        TPCANStatus status = PCANBasic.Write(PCANhandle, ref msg);
        if (status != TPCANStatus.PCAN_ERROR_OK)
        {
            Debug.Log("Error Sending CAN Message");
            Debug.Log(GetFormattedError(status));
        }
    }

    private void ThreadExecute()
    {
        // Register a receive-event so the thread wakes on incoming frames instead of busy-polling
        AutoResetEvent evtReceiveEvent = new AutoResetEvent(false);
        UInt32 iBuffer = Convert.ToUInt32(evtReceiveEvent.SafeWaitHandle.DangerousGetHandle().ToInt32());
        TPCANStatus stsResult = PCANBasic.SetValue(PCANhandle, TPCANParameter.PCAN_RECEIVE_EVENT, ref iBuffer, sizeof(UInt32));

        if (stsResult != TPCANStatus.PCAN_ERROR_OK)
        {
            ShowStatus(stsResult);
            return;
        }

        while (m_ThreadRun)
            if (evtReceiveEvent.WaitOne(50))
                ReadMessages();

        // Unregister the receive-event on exit
        iBuffer   = 0;
        stsResult = PCANBasic.SetValue(PCANhandle, TPCANParameter.PCAN_RECEIVE_EVENT, ref iBuffer, sizeof(UInt32));
        if (stsResult != TPCANStatus.PCAN_ERROR_OK)
            ShowStatus(stsResult);

        evtReceiveEvent.Dispose();
    }

    private void ReadMessages()
    {
        // Drain the queue: read until empty or error
        TPCANStatus stsResult;
        do
        {
            stsResult = ReadMessage();
            if (stsResult != TPCANStatus.PCAN_ERROR_OK && stsResult != TPCANStatus.PCAN_ERROR_QRCVEMPTY)
            {
                ShowStatus(stsResult);
                return;
            }
        }
        while (!Convert.ToBoolean(stsResult & TPCANStatus.PCAN_ERROR_QRCVEMPTY));
    }

    private TPCANStatus ReadMessage()
    {
        TPCANStatus stsResult = PCANBasic.Read(PCANhandle, out TPCANMsg CANMsg, out TPCANTimestamp CANTimeStamp);
        if (stsResult != TPCANStatus.PCAN_ERROR_QRCVEMPTY)
            ProcessMessageCan(CANMsg, CANTimeStamp);

        return stsResult;
    }

    private void ProcessMessageCan(TPCANMsg msg, TPCANTimestamp itsTimeStamp)
    {
        // Timestamp formula if needed: itsTimeStamp.micros + (1000UL * itsTimeStamp.millis) + (0x100_000_000UL * 1000UL * itsTimeStamp.millis_overflow)

        if (inCANMessages.ContainsKey(msg.ID))
            inCANMessages[msg.ID] = msg;
        else
            inCANMessages.Add(msg.ID, msg);
    }

    private void PrintinCANMessages()
    {
        Debug.Log("CAN Message list");
        foreach (var kvp in inCANMessages)
        {
            TPCANMsg msg = kvp.Value;
            Debug.Log("ID: " + GetIdString(msg.ID, msg.MSGTYPE) + " Data: " + GetDataString(msg.DATA, msg.MSGTYPE, msg.LEN));
        }
    }

    private TPCANHandle GetPCANHandle()
    {
        const string DeviceType = "PCAN_USB";
        //const string DeviceID         = "";
        //const string ControllerNumber = "";
        //const string IPAddress        = "";

        string sParameters = "";
        if (DeviceType != "")
            sParameters += PCANBasic.LOOKUP_DEVICE_TYPE + "=" + DeviceType;

        //if (DeviceID != "")
        //    sParameters += ", " + PCANBasic.LOOKUP_DEVICE_ID + "=" + DeviceID;
        //if (ControllerNumber != "")
        //    sParameters += ", " + PCANBasic.LOOKUP_CONTROLLER_NUMBER + "=" + ControllerNumber;
        //if (IPAddress != "")
        //    sParameters += ", " + PCANBasic.LOOKUP_IP_ADDRESS + "=" + IPAddress;

        TPCANStatus stsResult = PCANBasic.LookUpChannel(sParameters, out TPCANHandle handle);

        if (stsResult == TPCANStatus.PCAN_ERROR_OK)
        {
            if (handle != PCANBasic.PCAN_NONEBUS)
            {
                stsResult = PCANBasic.GetValue(handle, TPCANParameter.PCAN_CHANNEL_FEATURES, out uint iFeatures, sizeof(uint));
                if (stsResult == TPCANStatus.PCAN_ERROR_OK)
                {
                    Debug.Log("Channel found: " + FormatChannelName(handle, (iFeatures & PCANBasic.FEATURE_FD_CAPABLE) == PCANBasic.FEATURE_FD_CAPABLE));
                    return handle;
                }
                else
                    Debug.Log("Could not retrieve channel features");
            }
            else
                Debug.Log("No handle found for these lookup criteria");
        }

        if (stsResult != TPCANStatus.PCAN_ERROR_OK)
            Debug.Log("Device lookup failed — is any hardware channel attached?");

        return 0;
    }

    private string FormatChannelName(TPCANHandle handle, bool isFD)
    {
        TPCANDevice devDevice;
        byte byChannel;

        // Decode owner device and channel number from the handle value
        if (handle < 0x100)
        {
            devDevice = (TPCANDevice)(handle >> 4);
            byChannel = (byte)(handle & 0xF);
        }
        else
        {
            devDevice = (TPCANDevice)(handle >> 8);
            byChannel = (byte)(handle & 0xFF);
        }

        if (isFD)
            return string.Format("{0}:FD {1} ({2:X2}h)", devDevice, byChannel, handle);

        return string.Format("{0} {1} ({2:X2}h)", devDevice, byChannel, handle);
    }

    private string GetFormattedError(TPCANStatus error)
    {
        var strTemp = new System.Text.StringBuilder(256);
        if (PCANBasic.GetErrorText(error, 0x09, strTemp) != TPCANStatus.PCAN_ERROR_OK)
            return string.Format("An error occurred. Error-code's text ({0:X}) couldn't be retrieved", error);
        return strTemp.ToString();
    }

    private bool CheckForLibrary()
    {
        try
        {
            PCANBasic.Uninitialize(PCANBasic.PCAN_NONEBUS);
            return true;
        }
        catch (DllNotFoundException)
        {
            Debug.Log("Unable to find the library: PCANBasic.dll !");
        }
        return false;
    }

    private void ShowStatus(TPCANStatus status)
    {
        Debug.Log(GetFormattedError(status));
    }

    private string GetMsgTypeString(TPCANMessageType msgType)
    {
        if ((msgType & TPCANMessageType.PCAN_MESSAGE_STATUS) == TPCANMessageType.PCAN_MESSAGE_STATUS)
            return "STATUS";

        if ((msgType & TPCANMessageType.PCAN_MESSAGE_ERRFRAME) == TPCANMessageType.PCAN_MESSAGE_ERRFRAME)
            return "ERROR";

        string strTemp;
        if ((msgType & TPCANMessageType.PCAN_MESSAGE_EXTENDED) == TPCANMessageType.PCAN_MESSAGE_EXTENDED)
            strTemp = "EXT";
        else
            strTemp = "STD";

        if ((msgType & TPCANMessageType.PCAN_MESSAGE_RTR) == TPCANMessageType.PCAN_MESSAGE_RTR)
        {
            strTemp += "/RTR";
        }
        else if ((int)msgType > (int)TPCANMessageType.PCAN_MESSAGE_EXTENDED)
        {
            strTemp += " [";
            if ((msgType & TPCANMessageType.PCAN_MESSAGE_FD)  == TPCANMessageType.PCAN_MESSAGE_FD)  strTemp += " FD";
            if ((msgType & TPCANMessageType.PCAN_MESSAGE_BRS) == TPCANMessageType.PCAN_MESSAGE_BRS) strTemp += " BRS";
            if ((msgType & TPCANMessageType.PCAN_MESSAGE_ESI) == TPCANMessageType.PCAN_MESSAGE_ESI) strTemp += " ESI";
            strTemp += " ]";
        }

        return strTemp;
    }

    private string GetIdString(uint id, TPCANMessageType msgType)
    {
        if ((msgType & TPCANMessageType.PCAN_MESSAGE_EXTENDED) == TPCANMessageType.PCAN_MESSAGE_EXTENDED)
            return string.Format("{0:X8}h", id);

        return string.Format("{0:X3}h", id);
    }

    private string GetTimeString(TPCANTimestampFD time)
    {
        return (time / 1000.0).ToString("F1");
    }

    /// <summary>Returns the data bytes of a CAN message as a hex string.</summary>
    private string GetDataString(byte[] data, TPCANMessageType msgType, int dataLength)
    {
        if ((msgType & TPCANMessageType.PCAN_MESSAGE_RTR) == TPCANMessageType.PCAN_MESSAGE_RTR)
            return "Remote Request";

        string strTemp = "";
        for (int i = 0; i < dataLength; i++)
            strTemp += string.Format("{0:X2} ", data[i]);

        return strTemp;
    }
}
