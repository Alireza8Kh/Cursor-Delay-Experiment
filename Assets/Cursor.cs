using UnityEngine;

public class Cursor : MonoBehaviour
{
    private Rigidbody cursor;

    public string scriptCANName; // name of the GameObject holding the CANRecorder component
    private GameObject scriptCAN;

    // 2-row circular buffer: row 0 = joint angle samples [rad], row 1 = timestamps [s]
    // 500 samples at ~60 Hz gives roughly 8 seconds of history — enough for any practical visual delay
    private float[,] pos = new float[2, 500];

    // Angle sample delayed by HandleExperiment.visual_delay milliseconds, used to position the cursor
    private float delayed_angle;

    public const double mathPI = 3.1415926535897931;

    private Vector3 posUpdate;

    void Start()
    {
        cursor    = GetComponent<Rigidbody>();
        scriptCAN = GameObject.Find(scriptCANName);

        // Pre-fill the time row with the current time so the delay lookup never stalls on zeros
        float t0 = Time.time;
        for (int i = 0; i < 500; i++)
        {
            pos[0, i] = 0.0f;
            pos[1, i] = t0;
        }
    }

    void Update()
    {
        float time     = Time.time;
        float newAngle = scriptCAN.GetComponent<CANRecorder>().GetCurrentHRXData(0);

        // Shift the buffer left, discarding the oldest sample
        for (int i = 0; i < 499; i++)
        {
            pos[0, i] = pos[0, i + 1];
            pos[1, i] = pos[1, i + 1];
        }

        // Append the newest sample at the end
        pos[0, 499] = newAngle;
        pos[1, 499] = time;

        // Walk backward through the buffer to find the sample closest to (now - visual_delay)
        // visual_delay is in ms, so multiply by 0.001 to convert to seconds
        float targetTime  = pos[1, 499] - 0.001f * HandleExperiment.visual_delay;
        delayed_angle     = pos[0, 0]; // fallback: oldest sample (delay larger than buffer history)
        int k = 0;
        while (k < 499 && pos[1, 499 - k] > targetTime)
        {
            delayed_angle = pos[0, 499 - k];
            k++;
        }

        // Convert delayed joint angle [rad] to cursor screen x position [pixels]
        // Formula: x = gain * (180/π) * angle + offset   (gain = -21.11, offset = 422.22)
        posUpdate.x = -21.11f * 180f / (float)mathPI * delayed_angle + 422.22f;
        posUpdate.y = cursor.position.y;
        posUpdate.z = cursor.position.z;
        cursor.MovePosition(posUpdate);
    }
}
