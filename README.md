# TrajectoryDelay

An experiment for motor control research written in Unity. A sinusoidal trajectory descends down the screen while a subject tracks it with a cursor using a Robotic wrist interface. The cursor movement has a defined amount of delay compared to subject's wrist movements. EMG and Eye-gaze communication codes has also been implemented.

---

## Hardware requirements

| Component | Detail |
|---|---|
| HRX Robot| Connected via PCAN-USB adapter at 1 Mbit/s |
| EMG / Gaze recorder | Software triggered by F5 (start) and F6 (stop) |
| OS | Windows (requires `user32.dll` for keyboard events) |

---

## Scene flow

```
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
      ▼  points[last].y crosses cursor y level  OR  relativetime > TrialDuration
EndRecordingBool = true   →  F6 pressed  →  CSV recording stops
```

---

## Scripts

### `HandleCountdown.cs`
Runs the pre-trial countdown, swaps canvases, and sets `StartScrollingBool`.

**Inspector fields**

| Field | Assign |
|---|---|
| `countdownText` | TMP_Text on the countdown canvas |
| `GameCanvas` | Canvas active during the trial |
| `CountdownCanvas` | Canvas active during the countdown |

---

### `Trajectory.cs`
Pre-builds the sinusoidal path, scrolls it each frame, and manages the recording state flags.

**X trajectory formula**

```
x(t) = offsetX + Σ A[i] * sin(2π * f[i] * t + p[i])
```

Default values: 4 sinusoidal components at 0.20, 0.45, 0.90, 1.60 Hz.

**Y motion**

The path is pre-built with `y = yStart + descendVelocity * t`. During play, all points shift down by `descendVelocity * deltaTime` each frame, so the bottom point (`points[0]`) descends toward the cursor.

**Timing**

| Event | Condition |
|---|---|
| Recording starts | `points[0].y < cursor.y` |
| Recording ends | `points[last].y < cursor.y` OR `relativetime > TrialDuration` |

**Inspector fields**

| Field | Assign |
|---|---|
| `samples` | Number of path points (default 600) |
| `A`, `f`, `p` | Sinusoid amplitudes (px), frequencies (Hz), phases (rad) |
| `yStart` | Initial y position of the bottom path point |
| `descendVelocity` | Scroll speed in units/s |
| `scrollDown` | Enable/disable scrolling |
| `line` | LineRenderer component |
| `DurationName` | Name of the Duration `TMP_InputField` GameObject |
| `cursor` | Cursor GameObject (y position used as the trigger level) |

**Public static fields** (read by other scripts)

| Field | Meaning |
|---|---|
| `relativetime` | Seconds elapsed since recording started |
| `StartRecordingBool` | True once trajectory passes cursor level |
| `EndRecordingBool` | True once trial ends |

---

### `HandleExperiment.cs`
Reads robot state over CAN, writes one CSV row per frame, and fires F5/F6.

**Output CSV**

Path: `./Robot Data/S{subjId}/S{subjId}_Kd{joKd}_Delay_{visual_delay}_TrialNum_{TrialNumber}.csv`

Columns: `RelativeTime, CursorX, JointPosition [rad], JointVelocity [rad/s]`

**UI parameters** (read from `TMP_InputField` GameObjects at startup)

| Parameter | Type | Description |
|---|---|---|
| `subjId` | int | Subject identifier |
| `joKd` | float | Joint damping coefficient sent to robot |
| `visual_delay` | float (ms) | Visual feedback delay applied to cursor |
| `TrialDuration` | float (s) | Maximum recording duration (safety cutoff) |
| `TrialNumber` | int | Trial index, used in the output filename |

**Inspector fields** — set each to the name of the matching `TMP_InputField` GameObject:
`cursorName`, `scriptCANName`, `DurationName`, `joKdName`, `subjIdName`, `VisualDelayName`, `TrialNumberName`

---

### `Cursor.cs`
Moves the cursor horizontally using a delayed joint angle from the robot.

**Delay formula**

```
x = -21.11 * (180/π) * angle(t - visual_delay) + 422.22
```

A 500-sample circular buffer stores the joint angle history at the Unity frame rate. On each frame the buffer is walked backward to find the sample closest to `now - visual_delay`.

**Inspector fields**

| Field | Assign |
|---|---|
| `scriptCANName` | Name of the GameObject holding `CANRecorder` |

---

### `CANRecorder.cs`
Decodes incoming CAN frames into position and velocity values.

| CAN ID | Bytes | Decoding | Output |
|---|---|---|---|
| `0x381` | 4 (Int32) | `counts × 2π / 25600 + 1.994` | `pos1` [rad] |
| `0x481` | 2 (Int16) | `value × 2π / 60` | `vel1` [rad/s] |
| `0x667` | 2 (Int16) | send only | joint damping `joKd` |

Call `GetCurrentHRXData(0)` for position, `GetCurrentHRXData(1)` for velocity.

---

### `CANController.cs`
Manages the PCAN-USB connection on a background thread.

- Initialises at 1 Mbit/s in `Awake`
- Background thread wakes on a receive event (no busy-polling)
- Outgoing messages are queued and flushed each `FixedUpdate` (1 ms timestep)
- Auto-discovers the first available PCAN-USB channel

---

## Inspector setup checklist

1. **HandleCountdown** — assign `countdownText`, `GameCanvas`, `CountdownCanvas`
2. **Trajectory** — assign `line` (LineRenderer), `cursor` (Cursor GameObject), fill `DurationName`
3. **HandleExperiment** — fill all `*Name` string fields to match your UI GameObjects
4. **Cursor** — fill `scriptCANName`
5. **CANController / CANRecorder** — placed on the same GameObject; no extra fields needed

---

## Output data

Files are saved to `./Robot Data/` relative to the Unity project root (or build executable). The folder is created automatically if it does not exist. An existing file with the same name is overwritten at the start of each trial.
