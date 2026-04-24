using System;
using System.Threading;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using WaveX; // Ensure this namespace is correct for DaqSystem
using WaveX.Interfaces;
using WaveX.Common.Definitions;
using Tobii.Research;
using System.IO;
using System.Text;
using System.Text.Json;
using System.Runtime.Serialization;
using System.Text.Json.Serialization;



public partial class Form1 : Form
{
    public static volatile bool isRecroding = false;
    private static List<float[,]> recordedData = new List<float[,]>();
    public static IDaqSystem daqSystem = new DaqSystem();
    public static volatile bool saveData = false;  // flag for the main thread to send message
    private DateTime startTime;
    public static int fileCount = 1;
    private string filePathHeader = "default";  //"CustomData\\recordedData";
    // Eye tracking fields
    private IEyeTracker? eyeTracker;
    //private List<GazeDataEventArgs> gazeDataList = new List<GazeDataEventArgs>();
    // english comment: Store simple gaze DTOs instead of SDK types
    private List<SerializableGazeData> gazeDataList = new List<SerializableGazeData>();


    // Import necessary Windows API functions
    [DllImport("user32.dll")]
    private static extern bool RegisterHotKey(IntPtr hWnd, int id, uint fsModifiers, uint vk);
    [DllImport("user32.dll")]
    private static extern bool UnregisterHotKey(IntPtr hWnd, int id);

    private const int HOTKEY_ID1 = 1;
    private const int HOTKEY_ID2 = 2;
    private const uint MOD_NONE = 0x0000; // No modifier
    private const uint VK_F5 = 0x74; // F5 key
    private const uint VK_F6 = 0x75;    //F6 key

    private readonly string baseDataDir = Path.Combine(Application.StartupPath, "CustomData");
    public Form1()
    {
        InitializeComponent();
        // Register the hotkey (F5)
        RegisterHotKey(this.Handle, HOTKEY_ID1, MOD_NONE, VK_F5);
        RegisterHotKey(this.Handle, HOTKEY_ID2, MOD_NONE, VK_F6);
        Directory.CreateDirectory(baseDataDir);
    }

    protected override void WndProc(ref Message m)
    {
        const int WM_HOTKEY = 0x0312;
        if (m.Msg == WM_HOTKEY && m.WParam.ToInt32() == HOTKEY_ID1)
        {
            // Call the method when F5 is pressed to generate start trigger
            daqSystem.GenerateInternalStartTrigger();
            infolabel.Text = $"Start trigger generated.";
        }
        if (m.Msg == WM_HOTKEY && m.WParam.ToInt32() == HOTKEY_ID2)
        {
            // Call the method when F6 is pressed           
            daqSystem.GenerateInternalStopTrigger();
            infolabel.Text = $"Stop trigger generated.";
        }
        base.WndProc(ref m);
    }

    private void CheckTimer_Tick(object sender, EventArgs e)
    {
        if (saveData)
        {
            //string filePath = $"CustomData\\{filePathHeader}_{fileCount}.txt";
            //SaveRecordedData(filePath);
            //infolabel.Text = $"Data saved to {filePath}";

            // save EMG data
            string emgDir = Path.Combine(baseDataDir, "EMG");
            Directory.CreateDirectory(emgDir);
            string emgPath = Path.Combine(emgDir, $"{filePathHeader}_{fileCount}.txt");
            SaveRecordedData(emgPath);
            infolabel.Text = $"EMG data saved to {emgPath}\n";

            // save eye tracking data
            string gazeDir = Path.Combine(baseDataDir, "Gaze");
            Directory.CreateDirectory(gazeDir);
            string gazePath = Path.Combine(gazeDir, $"{filePathHeader}_{fileCount}.json");
            SaveGazeDataFullJson(gazePath);
            infolabel.Text += $"Gaze data saved to {gazePath}\n";

            fileCount += 1;
            saveData = false;
            // clear the recorded data
            recordedData.Clear();
            gazeDataList.Clear();

            // Check if max time have passed
            if ((DateTime.Now - startTime).TotalSeconds >= 10000)
            {
                checkTimer.Stop();
                infolabel.Text = "Stopped after time up.";
                Application.Exit();
            }
        }
    }


    private void btnStart_Click(object sender, EventArgs e)
    {
        if (btnStart.Text == "Start")
        {
            // Change the text to End
            btnStart.Text = "End";

            // Set the file path
            filePathHeader = headerTextBox.Text;
            // set the timer
            startTime = DateTime.Now;
            checkTimer.Start();

            // Add eye tracking step
            // Browsing
            var list = EyeTrackingOperations.FindAllEyeTrackers();  // Use official Tobii API
            if (list.Any())
            {
                eyeTracker = list.First();
                infolabel.Text = $"Connected to eye tracker: {eyeTracker.DeviceName}\n";

                // Serialize calibration data to JSON file
                var calibrationData = eyeTracker.RetrieveCalibrationData();
                string calibDir = Path.Combine(baseDataDir, "Calibration");
                Directory.CreateDirectory(calibDir);
                string calibPath = Path.Combine(calibDir, $"{filePathHeader}_calibration.json");
                // Serialize full CalibrationData to JSON
                File.WriteAllText(calibPath,
                    JsonSerializer.Serialize(calibrationData, new JsonSerializerOptions { WriteIndented = true })
                );




                infolabel.Text += $"Calibration data saved to {calibPath}\n";

                // Subscribe
                eyeTracker.GazeDataReceived += OnGazeDataReceived;
            }
            else
            {
                infolabel.Text += "No eye tracker found.\n";
                MessageBox.Show("Tobii device not detected");
            }

            // Original EMG startup
            // Device startup
            DeviceError initialError = daqSystem.InitialError;
            DeviceState currentState = daqSystem.State;
            infolabel.Text +=
                $"The initial error is: {initialError}.\n" +
                $"The current device state is: {currentState}.\n" +
                "Start Capturing.\n";
            // Start capturing data and acquisition
            daqSystem.StartCapturing(DataAvailableEventPeriod.ms_100);

            // Register the event handler for data available
            daqSystem.DataAvailable += OnDataAvailable;
        }
        else
        {
            //// Serialize gaze data list to XML file
            //string gazeDir = Path.Combine(baseDataDir, "Gaze");
            //Directory.CreateDirectory(gazeDir);
            //string gazePath = Path.Combine(gazeDir, $"{filePathHeader}_gaze.json");
            //SaveGazeDataFullJson(gazePath);
            //infolabel.Text += $"Gaze data saved to {gazePath}\n";
            // finish the program
            Application.Exit();
        }

    }

    private void OnDataAvailable(object sender, DataAvailableEventArgs e)
    {
        // If no trigger is detected, returns zeros, set the default option as follows
        int startscan = e.StartTriggerScan;
        int endscan = e.ScanNumber;
        if (e.StartTriggerDetected)
        {
            isRecroding = true;
        }
        if (e.StopTriggerDetected)
        {
            // If end trigger is detected, change the end scan number
            endscan = e.StopTriggerScan;
            isRecroding = false;
            // add the data as it will be excluded from the isRecording condition
            recordedData.Add(ProcessData(e.EmgSamples, startscan, endscan));
            // save the data
            saveData = true;
        }
        if (isRecroding)
        {
            recordedData.Add(ProcessData(e.EmgSamples, startscan, endscan));
        }
    }
    private void OnGazeDataReceived(object? sender, GazeDataEventArgs e)
    {
        if (!isRecroding)
            return;
        // Read normalized gaze point for left and right eyes
        double lx = e.LeftEye.GazePoint.PositionOnDisplayArea.X;
        double ly = e.LeftEye.GazePoint.PositionOnDisplayArea.Y;
        double rx = e.RightEye.GazePoint.PositionOnDisplayArea.X;
        double ry = e.RightEye.GazePoint.PositionOnDisplayArea.Y;

        // Compute binocular average
        double avgX = (lx + rx) / 2.0;
        double avgY = (ly + ry) / 2.0;

        // Map into our serializable DTO
        var dto = new SerializableGazeData
        {
            DeviceTimestamp = e.DeviceTimeStamp,   // raw device time (µs)
            SystemTimestamp = e.SystemTimeStamp,   // host system time (µs)
            LeftX = lx,                  // left eye X
            LeftY = ly,                  // left eye Y
            RightX = rx,                  // right eye X
            RightY = ry,                  // right eye Y
            GazeX = avgX,                // binocular average X
            GazeY = avgY                 // binocular average Y
        };

        // Add to the list
        gazeDataList.Add(dto);

        //// Update UI every 50 samples so user sees progress
        //if (gazeDataList.Count % 50 == 0)
        //{
        //    infolabel.Invoke((Action)(() =>
        //        infolabel.Text += $"Received {gazeDataList.Count} gaze samples.\n"
        //    ));
        //}
    }


    private static float[,] ProcessData(float[,] data, int startscan, int endscan)
    {
        float[,] validData = new float[8, Math.Abs(endscan - startscan)];
        // check data shape is valid
        if (data.GetLength(0) < 8)
        {
            Console.WriteLine("Warning: data dimension 0 size smaller than total sensor count.(Should be 36)");
        }
        int dim0 = 8;
        if (data.GetLength(1) < endscan || data.GetLength(1) < startscan || endscan <= startscan)
        {
            Console.WriteLine("Warning: data dimension 1 size smaller than start or end scan.");
        }

        // take the first 8 channels, from start to end scan
        for (int i = 0; i < dim0; i++)
        {
            for (int j = startscan; j < endscan; j++)
            {
                Console.Write($"{data[i, j]} ");
                validData[i, j - startscan] = data[i, j];
            }
            Console.WriteLine();
        }
        Console.WriteLine($"Data dimension: {dim0}x{endscan - startscan}");
        return validData;
    }
    private static void SaveRecordedData(string filePath)
    {
        // check if the directory exists
        if (!Directory.Exists(Path.GetDirectoryName(filePath)))
        {
            Directory.CreateDirectory(Path.GetDirectoryName(filePath));
        }
        using (StreamWriter writer = new StreamWriter(filePath))
        {
            foreach (var data in recordedData)
            {
                int dim0 = data.GetLength(0);
                int dim1 = data.GetLength(1);

                for (int i = 0; i < dim0; i++)
                {
                    for (int j = 0; j < dim1; j++)
                    {

                        writer.Write($"{data[i, j]} ");
                    }
                    writer.WriteLine();
                }
                writer.WriteLine();
                //writer.WriteLine("-----");
            }
        }
    }

    protected override void OnFormClosing(FormClosingEventArgs e)
    {
        // Unregister the hotkey when the form is closing
        UnregisterHotKey(this.Handle, HOTKEY_ID1);
        UnregisterHotKey(this.Handle, HOTKEY_ID2);
        // Stop capturing data
        daqSystem.StopCapturing();
        infolabel.Text = "Capturing done.";
        base.OnFormClosing(e);
    }

    public class SerializableGazeData
    {
        public long DeviceTimestamp { get; set; }  // Tobii device timestamp (µs)
        public long SystemTimestamp { get; set; }  // Host system timestamp (µs)
        public double LeftX { get; set; }  // Left eye normalized gaze X (0–1)
        public double LeftY { get; set; }  // Left eye normalized gaze Y (0–1)
        public double RightX { get; set; }  // Right eye normalized gaze X (0–1)
        public double RightY { get; set; }  // Right eye normalized gaze Y (0–1)
        public double GazeX { get; set; }  // Binocular average gaze X (0–1)
        public double GazeY { get; set; }  // Binocular average gaze Y (0–1)
    }

    // Serialize gazeDataList to JSON file, allowing NaN/Infinity literals
    private void SaveGazeDataFullJson(string path)
    {
        var dir = Path.GetDirectoryName(path);
        if (!Directory.Exists(dir))
            Directory.CreateDirectory(dir);

        var options = new JsonSerializerOptions
        {
            WriteIndented = true,
            NumberHandling = JsonNumberHandling.AllowNamedFloatingPointLiterals
        };
        File.WriteAllText(path,
            JsonSerializer.Serialize(gazeDataList, options)
        );
    }

}




