using System.Collections;
using TMPro;
using UnityEngine;

public class HandleCountdown : MonoBehaviour
{
    // True after the countdown finishes — signals Trajectory to start scrolling
    public static bool StartScrollingBool;

    public TMP_Text countdownText;      // TextMeshPro component that displays the countdown
    public GameObject GameCanvas;       // Canvas shown during the active trial
    public GameObject CountdownCanvas;  // Canvas shown during the countdown phase

    void Start()
    {
        StartScrollingBool = false;
        GameCanvas.SetActive(false);       // hide the trial canvas until the countdown finishes
        CountdownCanvas.SetActive(true);   // show the countdown canvas at scene start

        if (countdownText == null)
            Debug.LogError("Countdown Text was not assigned.");
    }

    void Update()
    {
        // Press Space to begin the countdown (only once per run)
        if (Input.GetKeyDown(KeyCode.Space) && !StartScrollingBool)
        {
            Debug.Log("Space key pressed. Starting countdown.");
            StartCoroutine(Countdown());
        }
    }

    public IEnumerator Countdown()
    {
        if (countdownText == null)
        {
            Debug.LogError("Countdown Text not assigned.");
            yield break;
        }

        WaitForSeconds wait1s = new(1f); // cached to avoid per-frame allocations

        countdownText.enabled = true;

        countdownText.text = "Be Ready!";
        yield return wait1s;
        countdownText.text = "3";
        yield return wait1s;
        countdownText.text = "2";
        yield return wait1s;
        countdownText.text = "1";
        yield return wait1s;
        countdownText.text = "GO!";
        yield return wait1s;
        countdownText.enabled = false;
        yield return wait1s;

        // Switch canvases and release the trial
        CountdownCanvas.SetActive(false);
        GameCanvas.SetActive(true);
        StartScrollingBool = true; // triggers Trajectory moving downward
    }
}
