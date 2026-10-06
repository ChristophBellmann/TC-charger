# Build & Flash

The project can be built with Arduino CLI.

## Target

Board/FQBN:

`arduino:avr:leonardo`

## Simple controller

```sh
arduino-cli compile --fqbn arduino:avr:leonardo TCCharger_simple_cccv
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo TCCharger_simple_cccv
arduino-cli monitor -p /dev/ttyACM0 --config baudrate=115200
```

The project README documents the required CAN library as the Leonardo-CANBed-compatible `CAN_BUS_Shield` variant. The full UI version additionally depends on its display/timer/menu support libraries.

Verify library/API compatibility before changing CAN libraries: similarly named MCP2515 libraries can expose different initialization APIs.
