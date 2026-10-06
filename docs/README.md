# TC Charger CAN Control

Arduino-based CAN control for TC/Elcon chargers using an Arduino Leonardo-compatible CANBed.

The project provides both a compact fixed-setpoint CC/CV controller and a more complete user-interface variant with display and controls.

## Core idea

The charger performs the CC/CV regulation internally. The controller periodically transmits the requested voltage and maximum current over CAN and reads charger feedback.

The documented implementation uses the TC/Elcon protocol 1430 at 250 kbit/s.

Continue with [System Overview](system-overview.md), [CAN Protocol](can-protocol.md), [Controller Variants](controller-variants.md), [Build & Flash](build-and-flash.md), and [Safety & Integration](safety-and-integration.md).

---

**Renewable Energy Design**  
Engineering · Energy · Embedded Systems · Automation
