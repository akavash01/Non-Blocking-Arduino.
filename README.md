# Level 2 — Non-Blocking Arduino Sensor Loop

## Overview

This project reads a photoresistor and controls an LED without using `delay()`.

- **Board:** Arduino Uno
- **Sensor:** Photoresistor module, analog output connected to `A0`
- **LED:** Connected to digital pin `9` through a `220 Ω` resistor
- **Behavior:** When the sensor reading is below `500`, the LED turns on; otherwise it turns off.

## Two tasks at different rates

| Task | Interval | Rate |
|---|---:|---:|
| Read the sensor and update the LED | 100 ms | 10 times/second |
| Print the latest reading to Serial Monitor | 1000 ms | Once/second |

## Why the loop is non-blocking

The sketch uses `millis()` to check elapsed time independently for each task. `millis()` is maintained by the Arduino core using a hardware timer (Timer0) on the Uno. The loop does not wait for either task to finish; it keeps checking both schedules, so the faster sensor task and slower reporting task can run at their own rates.

The elapsed-time pattern:

```cpp
if (now - lastTaskTime >= interval) {
  lastTaskTime = now;
  // Do the task
}
```

uses unsigned subtraction, which also handles the `millis()` counter rollover safely.

## Files

- `sketch.ino` — Arduino program
- `diagram.json` — Wokwi circuit diagram
- `README.md` — project explanation and run instructions

## Run in Wokwi

1. Open [Wokwi Arduino Uno](https://wokwi.com/projects/new/arduino-uno).
2. Replace the starter sketch with the contents of `sketch.ino`.
3. Open the diagram editor and use the contents of `diagram.json` (or create the same connections shown below).
4. Start the simulation.
5. Open the Serial Monitor to see a reading once per second.
6. Change the photoresistor's light level in the simulator. The LED should turn on when the analog reading is below `500`.

## Run on a physical Arduino Uno

1. Connect the photoresistor module: `VCC` to `5V`, `GND` to `GND`, and `AO` to `A0`.
2. Connect Arduino pin `9` to a `220 Ω` resistor, then to the LED anode. Connect the LED cathode to `GND`.
3. Open `sketch.ino` in the Arduino IDE, select **Arduino Uno** and the correct port, then upload.
4. Open Serial Monitor at **9600 baud**.

## GitHub submission

Create a **public** repository named `Level-2-Non-Blocking-Arduino`, then upload these three files to the repository root:

- `sketch.ino`
- `diagram.json`
- `README.md`

After uploading, open the repository link in a private/incognito browser window to confirm it is publicly accessible. Submit that repository URL.
