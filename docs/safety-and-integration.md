# Safety & Integration

Battery chargers can involve hazardous DC voltage, high current and significant stored energy.

## Integration requirements

Before using the controller on a real battery system, verify at minimum:

- charger model and CAN protocol compatibility,
- battery chemistry and series-cell count,
- maximum charge voltage,
- maximum permissible charge current,
- BMS limits and shutdown behavior,
- contactors/interlocks and emergency behavior,
- conductor, connector and fuse ratings,
- charger isolation and grounding requirements.

The example firmware values are development settings, not universal charging recommendations.

## Failure behavior

A software command path should not be the only protection against battery overvoltage, overcurrent or unsafe temperature. Independent BMS and hardware protections remain necessary.

Changes should first be verified with a safe test setup and CAN monitoring before connecting a high-energy battery.
