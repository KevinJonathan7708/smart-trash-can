# 🗑️ Smart Automatic Trashcan Lid

A low-cost, sensor-driven trashbin lid that automatically opens when a person approaches within **1 meter** and closes when they move away. Features hysteresis thresholds, distance averaging, and synchronized dual-servo control for smooth, jitter-free operation.

Designed as a foundational embedded systems project by first-year students at **Karunya University Build Club**.

## ✨ Key Features
- **Proximity Activation:** HC-SR04 ultrasonic sensor triggers lid at ≤100 cm
- **Hysteresis Logic:** Closes only after ≥150 cm to prevent rapid toggling
- **Dual-Servo Sync:** Two SG90 servos move in unison for reliable lid actuation
- **Beginner-Friendly:** Pure Arduino C++, no external frameworks or complex wiring
- **Battery Powered:** Runs wirelessly on parallel 9V batteries with common-ground stability
