# TC-Charger CAN-Steuerung

CAN-Bus-Steuerung für TC/Elcon-Ladegeräte auf einem **Arduino Leonardo CAN-BUS Board (CANBed)**.

Board / FQBN: `arduino:avr:leonardo` · CS-Pin des MCP2515: **17** · CAN 250 kBit/s
Protokoll 1430: Sende-ID `0x1806E5F4`, Empfangs-ID `0x18FF50E5`.

> CC/CV regelt das Ladegerät selbst: der Arduino sendet nur Sollspannung + Maxstrom
> (jede Sekunde als Watchdog). Das Gerät fährt Konstantstrom bis zur Sollspannung,
> danach Konstantspannung mit frei fallendem Strom.

## Sketches

### `TCCharger_simple_cccv/`
Schlanke Variante ohne Display/Tasten/Poti. Sendet fix 116,2 V / 32 A und gibt
Spannung & Strom jede Sekunde über USB (Serial, 115200 Baud) aus.

Benötigte Bibliothek:
- `CAN_BUS_Shield` (Leonardo-CAN-BUS-kompatible Variante, `begin(CAN_250KBPS)`)
  aus dem Repo [DanyEarth/TC-Charger-CAN-controller](https://github.com/DanyEarth/TC-Charger-CAN-controller).
  **Nicht** `coryjfowler/mcp_can` (dort braucht `begin()` 3 Argumente).

### `TCCharger_automatic_start/`
Vollständige menübasierte Variante mit LCD + Tasten (LcdKeypad/MenuManager).

Benötigte Bibliotheken:
- `CAN_BUS_Shield` (s. o.)
- `LiquidCrystal`, `TimerOne`
- klassische `SimpleTimer` (Marcello Romani, mit `setInterval(long, callback)` + `run()`)
  — **nicht** die SimpleTimer 1.0.0 aus dem Library Manager (andere API).

## Build & Flash

```sh
arduino-cli compile --fqbn arduino:avr:leonardo TCCharger_simple_cccv
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo TCCharger_simple_cccv
arduino-cli monitor -p /dev/ttyACM0 --config baudrate=115200
```
