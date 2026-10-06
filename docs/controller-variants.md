# Controller Variants

## Simple CC/CV

`TCCharger_simple_cccv/` is the compact reference implementation. It has no display, buttons or potentiometer and is useful for understanding the minimum CAN control path.

The current repository version contains fixed example setpoints. These values are application-specific and must not be copied to another battery system without verifying the battery, BMS and charger limits.

## Automatic-start / UI variant

`TCCharger_automatic_start/` is the larger implementation with LCD and menu handling. Supporting classes provide keypad and menu functionality.

This variant is appropriate when the charger controller itself should provide local configuration and status interaction.

## Design principle

Keeping a small reference sketch next to the full controller makes protocol debugging easier: CAN communication can be verified without the additional UI state machine.
