using System.Text;
using TMPro;
using UnityEngine;
using System.IO;
using System.Runtime.InteropServices;
using System;

public class HandleExperiment : MonoBehaviour
{
    // Names of master-canvas GameObjects — assign in the Unity inspector.
    // The user sets these names to match the GameObjects in the scene, so the canvas layout can be changed without editing this script.
    public string cursorName, scriptCANName, DurationName, joKdName, subjIdName, VisualDelayName, TrialNumberName;

    // Experiment parameters read from the UI at startup:
    // visual_delay  (float, ms): cursor shows robot position delayed — x(t) = a*q(t - visual_delay) + b
    // joKd          (float):     joint viscosity applied to each subject's velocity: mu_v * qd(t)
    // TrialNumber     (int):     1–5, determines the save subfolder
    // TrialDuration (float, s):  total trial length
    public static int subjId, TrialNumber;
    public static float joKd, visual_delay, TrialDuration;

    // Internal references to scene objects (resolved in Start from the name strings above)
    private GameObject cursor, scriptCAN, joKdObj, subjIdObj, VisualDelayObj, TrialNumberObj, DurationObj;
    private TMP_Text countdownText;

    private float[] robotsState = new float[2]; // [0] = pos1, [1] = vel1
    public static float RelativeTime; // elapsed time since experiment start, written to CSV
    private float StartTime;
    private bool StartFlag = false; // latched true on first active frame to record StartTime
    private bool EndFlag   = false; // prevents the F6 stop-event firing more than once

    private const int VK_F5 = 0x74, VK_F6 = 0x75, KEYEVENTF_KEYDOWN = 0x0; // F5 starts, F6 stops EMG/Gaze recording

    private float cursor1; // current cursor x position
    private string outPath; // full path to the output CSV file

    void Start()
    {
        // Resolve all scene objects by name
        cursor         = GameObject.Find(cursorName);
        scriptCAN      = GameObject.Find(scriptCANName);
        subjIdObj      = GameObject.Find(subjIdName);
        joKdObj        = GameObject.Find(joKdName);
        VisualDelayObj = GameObject.Find(VisualDelayName);
        TrialNumberObj = GameObject.Find(TrialNumberName);
        DurationObj    = GameObject.Find(DurationName);

        // Read all experiment parameters from the UI input fields
        subjId        = int.Parse(subjIdObj.GetComponent<TMP_InputField>().text);
        joKd          = float.Parse(joKdObj.GetComponent<TMP_InputField>().text);
        visual_delay  = float.Parse(VisualDelayObj.GetComponent<TMP_InputField>().text);
        TrialDuration = float.Parse(DurationObj.GetComponent<TMP_InputField>().text);
        TrialNumber   = int.Parse(TrialNumberObj.GetComponent<TMP_InputField>().text);

        // Build output file path and create the folder if it does not exist
        string folderpath = "./RobotData/S" + subjId + "/";
        outPath = folderpath + "S" + subjId
                + "_Kd_" + joKd + "_Delay_" + visual_delay
                + "_TrialNum_" + TrialNumber + ".csv";

        if (!Directory.Exists(folderpath)) Directory.CreateDirectory(folderpath);
        if (File.Exists(outPath))          File.Delete(outPath);

        countdownText = GameObject.Find("CountdownText").GetComponent<TMP_Text>();
        if (countdownText == null)
            Debug.LogError("Countdown Text was not assigned.");
    }

    void Update()
    {
        if (Trajectory.StartRecordingBool && !Trajectory.EndRecordingBool) // start recording Robot and EMG when the trajectory descends past the cursor y position, until the trial duration elapses
        {
            if (!StartFlag)
            {
                StartTime = Time.time;
                StartFlag = true;
                keybd_event(VK_F5, 0, KEYEVENTF_KEYDOWN, IntPtr.Zero); // virtually press F5 to start EMG recording
                Debug.Log("Experiment started. EMG recording started.");
            }

            // Elapsed time since experiment start, used as the timestamp column in the CSV
            RelativeTime = Time.time - StartTime;

            // Read robot state from CAN
            for (int i = 0; i < 2; i++)
                robotsState[i] = scriptCAN.GetComponent<CANRecorder>().GetCurrentHRXData(i);

            cursor1 = cursor.transform.position.x;

            WriteStateToFiles(robotsState[0], robotsState[1]);
        }
        else if (Trajectory.EndRecordingBool && !EndFlag)
        {
            EndFlag = true;
            keybd_event(VK_F6, 0, KEYEVENTF_KEYDOWN, IntPtr.Zero); // virtually press F6 to stop EMG recording
            Debug.Log("Experiment ended. EMG recording stopped.");
        }
    }

    [DllImport("user32.dll")]
    public static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, IntPtr dwExtraInfo);

    // Appends one CSV row: [RelativeTime, cursor1, pos1, vel1]
    private void WriteStateToFiles(float pos1, float vel1)
    {
        string[] fields = {
            RelativeTime.ToString(),
            cursor1.ToString(),
            pos1.ToString(),
            vel1.ToString()
        };

        string line = string.Join(",", fields) + Environment.NewLine;

        if (!File.Exists(outPath))
            File.WriteAllText(outPath, line);
        else
            File.AppendAllText(outPath, line);
    }
}
