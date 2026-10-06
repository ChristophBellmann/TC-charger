# CAN Protocol

The project targets TC/Elcon protocol 1430.

## Bus configuration

- CAN bitrate: 250 kbit/s
- Command identifier: `0x1806E5F4`
- Charger response identifier: `0x18FF50E5`

The firmware encodes charger setpoints into CAN frames and decodes returned voltage/current information.

## Control model

Voltage and maximum-current commands define the requested charging envelope. The charger itself performs the transition from constant-current operation to constant-voltage operation.

CAN commands should be treated as one part of a complete charger integration. They do not replace hardware interlocks, battery-management limits or charger/manufacturer safety requirements.
