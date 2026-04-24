# TrajectoryDelay

TrajectoryDelay is a Unity-based experiment for motor control research. A sinusoidal trajectory descends down the screen while a subject tracks it with a cursor using an HRX robotic wrist interface. The cursor movement can be delayed by a defined amount relative to the subject’s wrist movement. EMG and eye-gaze communication triggers are also implemented.

---

## Hardware Requirements

| Component | Details |
|---|---|
| HRX-1 robot | Connected via PCAN-USB adapter at 1 Mbit/s |
| EMG / gaze recorder | Software triggered by F5 to start and F6 to stop |
| OS | Windows, required for `user32.dll` keyboard events |

---

## Software Requirements

- Unity 2022.3.18f1
- MATLAB Simulink
- [PEAK PCAN-USB adapter](https://www.peak-system.com/PCAN-USB.199.0.html) with `PCANBasic.dll`
- EMG recording software listening for F5 and F6 keyboard shortcuts
- TextMeshPro, included via Unity Package Manager

---

## Scene Flow

```text
Space key pressed
      │
      ▼
Countdown: "Be Ready!" → 3 → 2 → 1 → GO!
      │
      ▼  HandleCountdown.StartScrollingBool = true
Trajectory begins scrolling downward
      │
      ▼  points[0].y crosses cursor y level
StartRecordingBool = true  →  F5 pressed  →  CSV recording starts
      │
      ▼  points[last].y crosses cursor y level OR relativetime > TrialDuration
EndRecordingBool = true    →  F6 pressed  →  CSV recording stops
```

---

## Setup

1. Clone the repository and open the project in Unity 2022.3.18f1.
2. Place `PCANBasic.dll` in the project’s `Assets/Plugins/` folder, if it is not already there.
3. Connect the PCAN-USB adapters.
4. With the robot turned off, open `HRXDUAL_Delay.slx` in Simulink and run it. Press **Build & Run** in the top-right corner.
5. Place the robot in the reset orientation, corresponding to maximum flexion, and turn the robot on. Then press the reset button on the CAN controller.
6. In the `Cometa/` folder, run `CometaWindowsForms.exe` with your chosen header name. This handles communication with the EMG and gaze instruments.

   Unity automatically triggers the start and stop of EMG and gaze recording, so no further action is required during the trial.

7. Open the `game` scene.
8. In the **MasterCanvas** UI, fill in the experiment parameters listed below.
9. Press the **Space** key to start the experiment. When the specified duration is reached, the game and all data recording channels stop automatically.

---

## Experiment Parameters

Set these parameters in the UI before each trial.

| Parameter | Description |
|---|---|
| Subject ID | Integer identifier for the subject |
| Trial Number | Trial index, used in output file naming |
| Duration (s) | Trial duration in seconds |
| Joint Viscosity (`joKd`) | Damping applied to each robot’s velocity, in N·m·s/rad |
| Delay (ms) | Visual delay applied to the cursor relative to the performed wrist movement |

---

## Project Structure

```text
Assets/
├── Scripts/
│   ├── CANController.cs      # Low-level CAN bus communication using PCAN-USB and threaded reading
│   ├── CANRecorder.cs        # Reads robot states and sends control configurations
│   ├── Cursor.cs             # Moves the subject's cursor based on HRX1 joint position
│   ├── HandleCountdown.cs    # Manages countdown UI and experiment start trigger
│   ├── HandleExperiment.cs   # Handles experiment logic, data saving, EMG triggers, and parameter configuration
│   └── Trajectory.cs         # Generates and scrolls the descending target trajectory
├── Scenes/
│   └── game.unity            # Main experiment scene
ProjectSettings/              # Unity project configuration
```

---

## Scripts

### `HandleCountdown.cs`

Runs the pre-trial countdown, swaps canvases, and sets `StartScrollingBool`.

**Inspector fields**

| Field | Assign |
|---|---|
| `countdownText` | `TMP_Text` object on the countdown canvas |
| `GameCanvas` | Canvas active during the trial |
| `CountdownCanvas` | Canvas active during the countdown |

---

### `Trajectory.cs`

Pre-builds the sinusoidal path, scrolls it each frame, and manages the recording state flags.

**X trajectory formula**

```text
x(t) = offsetX + Σ A[i] × sin(2π × f[i] × t + p[i])
```

Default values: four sinusoidal components at 0.20, 0.45, 0.90, and 1.60 Hz.

**Y motion**

The path is pre-built with:

```text
y = yStart + descendVelocity × t
```

During play, all points shift downward by:

```text
descendVelocity × deltaTime
```

on each frame. Therefore, the bottom point, `points[0]`, descends toward the cursor.

**Timing**

| Event | Condition |
|---|---|
| Recording starts | `points[0].y < cursor.y` |
| Recording ends | `points[last].y < cursor.y` or `relativetime > TrialDuration` |

**Inspector fields**

| Field | Assign |
|---|---|
| `samples` | Number of path points, default 600 |
| `A`, `f`, `p` | Sinusoid amplitudes in px, frequencies in Hz, and phases in rad |
| `yStart` | Initial y position of the bottom path point |
| `descendVelocity` | Scroll speed in units/s |
| `scrollDown` | Enables or disables scrolling |
| `line` | `LineRenderer` component |
| `DurationName` | Name of the Duration `TMP_InputField` GameObject |
| `cursor` | Cursor GameObject whose y position is used as the trigger level |

**Public static fields**

These fields are read by other scripts.

| Field | Meaning |
|---|---|
| `relativetime` | Seconds elapsed since recording started |
| `StartRecordingBool` | `true` once the trajectory passes the cursor level |
| `EndRecordingBool` | `true` once the trial ends |

---

### `HandleExperiment.cs`

Reads robot state over CAN, writes one CSV row per frame, and triggers F5/F6 to start and stop EMG and gaze recording.

**UI parameters**

These values are read from `TMP_InputField` GameObjects at startup.

| Parameter | Type | Description |
|---|---|---|
| `subjId` | int | Subject identifier |
| `joKd` | float | Joint damping coefficient sent to the robot |
| `visual_delay` | float, ms | Visual feedback delay applied to the cursor |
| `TrialDuration` | float, s | Maximum recording duration and safety cutoff |
| `TrialNumber` | int | Trial index used in the output filename |

**Inspector fields**

Set each field to the name of the matching `TMP_InputField` GameObject:

```text
cursorName
scriptCANName
DurationName
joKdName
subjIdName
VisualDelayName
TrialNumberName
```

---

### `Cursor.cs`

Moves the cursor horizontally using a delayed joint angle from the robot.

**Delay formula**

```text
x = -21.11 × (180 / π) × angle(t - visual_delay) + 422.22
```

**Inspector fields**

| Field | Assign |
|---|---|
| `scriptCANName` | Name of the GameObject holding `CANRecorder` |

---

### `CANRecorder.cs`

Decodes incoming CAN frames into position and velocity values.

| CAN ID | Bytes | Decoding | Output |
|---|---|---|---|
| `0x381` | 4, `Int32` | `counts × 2π / 25600 + 1.994` | `pos1` in rad |
| `0x481` | 2, `Int16` | `value × 2π / 60` | `vel1` in rad/s |
| `0x667` | 2, `Int16` | Send only | Joint damping `joKd` |

Use:

```csharp
GetCurrentHRXData(0)
```

to read position, and:

```csharp
GetCurrentHRXData(1)
```

to read velocity.

---

### `CANController.cs`

Manages the PCAN-USB connection on a background thread.

- Initializes the connection at 1 Mbit/s in `Awake`.
- Uses a background thread that wakes on a receive event, avoiding busy polling.
- Queues outgoing messages and flushes them in `FixedUpdate`.
- Uses a 1 ms fixed timestep.
- Automatically discovers the first available PCAN-USB channel.

---

## Data Output

There are three types of data output:

1. Robot data
2. EMG data
3. Eye-gaze data

---

### Robot Data

Robot data is saved automatically to:

```text
./Robot Data/S{id1}S{id2}/
```

as a CSV file.

The filename encodes the experimental parameters:

```text
S{id1}S{id2}_Ctrl_{mode}_Kp{coKp}_Visual_{visual_delay}_Haptic_{haptic_delay}_TrialNum_{n}.csv
```

Each row contains:

```text
time, cursor1_x, pos1, vel1, torque1, cursor2_x, pos2, vel2, torque2, posAvg
```

Units:

| Variable | Unit |
|---|---|
| Time | seconds |
| Position | radians |
| Velocity | rad/s |
| Torque | N·m |

Files are saved relative to the Unity project root, or relative to the build executable when running a build. The folder is created automatically if it does not exist. If a file with the same name already exists, it is overwritten at the start of the trial.

---

### EMG Data

EMG data is saved automatically to:

```text
./Cometa/CustomData/EMG/
```

as a `.txt` file.

The filename format is:

```text
{your_given_header}_{run_number}
```

where `run_number` corresponds to the trial number.

The data is organized into data blocks. Each block corresponds to one data package sent to the computer every 100 ms. Each package contains 8 rows, one for each EMG sensor, and 200 EMG data points per 100 ms.

Sampling frequency: 2 kHz.

Unit: mV.

---

### Eye-Gaze Data

Eye-gaze data is saved automatically to:

```text
./Cometa/CustomData/Gaze/
```

as a `.json` file.

The filename format is:

```text
{your_given_header}_{run_number}
```

where `run_number` corresponds to the trial number.

Each data block contains:

```text
Gaze_x, Gaze_y, time
```

Units:

| Field | Unit |
|---|---|
| `Gaze_x` | Normalized horizontal gaze coordinate on the monitor |
| `Gaze_y` | Normalized vertical gaze coordinate on the monitor |
| `time` | Absolute timestamp in microseconds |

---

## Inspector Setup Checklist

1. **HandleCountdown**
   - Assign `countdownText`.
   - Assign `GameCanvas`.
   - Assign `CountdownCanvas`.

2. **Trajectory**
   - Assign `line`, the `LineRenderer`.
   - Assign `cursor`, the Cursor GameObject.
   - Fill `DurationName`.

3. **HandleExperiment**
   - Fill all `*Name` string fields to match the corresponding UI GameObjects.

4. **Cursor**
   - Fill `scriptCANName`.

5. **CANController / CANRecorder**
   - Place both components on the same GameObject.
   - No additional fields are required.
