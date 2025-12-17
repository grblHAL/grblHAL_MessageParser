# grblHAL message parsers

Unified parsers for grblHAL and legacy Grbl serial message protocols and the grblHAL [I2C display protocol](https://github.com/grblHAL/Plugin_keypad/tree/master/display).

> [!NOTE]
> The code is intended for developers that wants to implement displays, pendants etc - it is not compilable as a standalone project.

The code provides a middle layer between a low level HAL driver layer that handles communication and the application layer.
The HAL layer is implemented as _weak_ functions that has to be overridden.
Data from the communication layer has to be polled in a tight loop by the application, the parsed data is routed back to the application via callbacks \(events\).

The code originates from my [grblHAL DRO & MPG](https://github.com/terjeio/GRBL_MPG_DRO_BoosterPack) code, I'll soon update that to reference this repo as a submodule.  

The parser can assign a color to each machine state,
a datatype holding the color and a list of color values has to be provided for that to work and
color handling has to be enabled in [parser.h](https://github.com/grblHAL/grblHAL_MessageParser/blob/main/parser.c) by removing the comment from `#define PARSER_ADD_COLOR`.

An example include for the color type and predefined colors can be found [here](https://github.com/terjeio/GRBL_MPG_DRO_BoosterPack/blob/master/Firmware/RP2040/src/LCD/colorRGB.h).

If there is any interest in using this code I'll add more documentation...

---
2025-12-17
