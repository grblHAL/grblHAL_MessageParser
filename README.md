# grblHAL message parsers

Unified parsers for grblHAL and legacy Grbl serial message protocols and the grblHAL [I2C display protocol](https://github.com/grblHAL/Plugin_keypad/tree/master/display).

__NOTE:__ The code is intended for developers that wants to implement displays, pendants etc - it is not compilable as a standalone project.


The code provides a middle layer between a low level HAL driver layer that handles communication and the application layer.
The HAL layer is implemented as _weak_ functions that has to be overridden.
Data from the communication layer has to be polled in a tight loop by the application, the parsed data is routed back to the application via callbacks \(events\).

The code originates from my [grblHAL DRO & MPG](https://github.com/terjeio/GRBL_MPG_DRO_BoosterPack) code, I'll soon update that to reference this repo as a submodule.  

If there is any interest in using this code I'll add documentation...

---
2023-03-05
