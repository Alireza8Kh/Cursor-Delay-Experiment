using UnityEngine;
using TMPro;

public class Trajectory : MonoBehaviour
{
    // Elapsed seconds since the trial started — read by HandleExperiment for CSV timestamps
    public static float relativetime;
    // Set to true when the trajectory reaches below the cursor y position, triggers HandleExperiment to start recording and time from this point onward
    public static bool StartRecordingBool = false;
    // Set to true when the trajectory last point reaches below the cursor y position, stops all scripts and Recording data
    public static bool EndRecordingBool = false;

    private float StartTime;     // latched on the first active frame
    private float TrialDuration; // read from the UI at Start, in seconds

    [Header("Prebuild")]
    public int samples = 600; // number of discrete points in the pre-built path

    [Header("X Trajectory")]
    // x(t) = offsetX + sum_i  A[i] * sin(2π * f[i] * t + p[i])
    public float offsetX = 0.0f;
    public float[] A = { 50.0f, 30.0f, 15.0f,  8.0f }; // amplitudes   [pixels]
    public float[] f = {  0.20f, 0.45f, 0.90f, 1.60f }; // frequencies  [Hz]
    public float[] p = {  0.0f,  0.0f,  0.0f,  0.0f  }; // phase offsets [rad]

    [Header("Y Motion")]
    public float yStart = 300.0f;
    public float descendVelocity = 100.0f; // units/s — positive moves the path downward

    [Header("Scroll In Update")]
    public bool scrollDown = true; // when true the pre-built path scrolls down each frame

    [Header("Render")]
    public LineRenderer line; // assign in inspector, or auto-found via GetComponent
    public float z = 0.0f;   // z-depth of the trajectory line

    private Vector3[] points; // pre-built world-space path points

    public string DurationName; // name of the duration input field GameObject in the master canvas
    private GameObject DurationObj;

    public GameObject cursor; // assign in inspector 

    void Start()
    {
        // Reset static state so a new trial does not inherit the previous trial state
        relativetime = 0.0f;
        StartRecordingBool = false;
        EndRecordingBool = false;

        // Read trial duration from the UI input field
        DurationObj   = GameObject.Find(DurationName);
        TrialDuration = float.Parse(DurationObj.GetComponent<TMP_InputField>().text);

        if (line == null) line = GetComponent<LineRenderer>();

        // Make the trajectory line white
        line.startColor = Color.white;
        line.endColor = Color.white;

        // Use an unlit shader so the line is not affected by scene lighting
        line.material = new Material(Shader.Find("Sprites/Default"));
        line.material.color = Color.white;

        samples = Mathf.Max(2, samples);
        points  = new Vector3[samples];

        // Pre-build the full path by sampling t uniformly over [0, TrialDuration]:
        //   x(t) = offsetX + sum of sinusoids (see arrays A, f, p above)
        //   y(t) = yStart + descendVelocity * t
        for (int i = 0; i < samples; i++)
        {
            float t = (float)i / (samples - 1) * TrialDuration; // maps index to [0 .. TrialDuration]

            float x = offsetX;
            for (int j = 0; j < A.Length; j++)
                x += A[j] * Mathf.Sin(2.0f * Mathf.PI * f[j] * t + p[j]);

            float y = yStart + descendVelocity * t;

            points[i] = new Vector3(x, y, z);
        }

        // Push the pre-built points to the LineRenderer so the path is visible at scene start
        if (line != null)
        {
            line.positionCount = points.Length;
            line.SetPositions(points);
        }
    }

    void Update()
    {
        if (HandleCountdown.StartScrollingBool && !EndRecordingBool) // start scrolling and recording when the countdown finishes, until the trajectory last point reaches below the cursor y position
        {
            if (points == null || cursor == null) return;

            if (!scrollDown) return;

            // Scroll the entire pre-built path downward at descendVelocity each frame
            float dy = descendVelocity * Time.deltaTime;
            for (int i = 0; i < points.Length; i++)
                points[i].y -= dy;

            if (line != null)
                line.SetPositions(points);

            // Latch the start time on the first active frame
            // start recording and time when first point descends past the cursor y position 
            if (!StartRecordingBool && points[0].y < cursor.transform.position.y)
            {
                StartTime = Time.time;
                relativetime = 0.0f;
                StartRecordingBool = true; // signals HandleExperiment to start recording Robot and EMG by pressing F5 
            }

            if (StartRecordingBool)
            {
                relativetime = Time.time - StartTime;
            }

            // End the trial once the trajectory last point descends past the cursor y position
            if (StartRecordingBool && points[points.Length - 1].y < cursor.transform.position.y)
            {
                EndRecordingBool = true;
                Debug.Log("Game ended.");
            }

            // End the trial once the elapsed time exceeds the configured duration
            if (StartRecordingBool && relativetime > TrialDuration)
            {
                EndRecordingBool = true;
                Debug.Log("Game ended.");
            }
        }
    }
}