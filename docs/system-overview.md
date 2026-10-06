# System Overview

The project controls compatible TC/Elcon chargers through CAN bus.

## Hardware

The documented controller platform is an Arduino Leonardo-compatible CANBed with an MCP2515 CAN controller. The project configuration uses chip-select pin 17 and a CAN bitrate of 250 kbit/s.

## Charging control

The external controller does not implement the power-stage CC/CV loop itself. Instead, it transmits requested output voltage and maximum current. The charger regulates its own output and returns operating data over CAN.

Periodic transmission also acts as part of the command/watchdog behavior expected by the charger.

Two firmware variants are maintained: a minimal fixed-setpoint implementation and a larger menu/display implementation.
