# Hygro/Thermometer

 End to end project to build and display temperature/humidity in local environment.

## components:
* RPI Pico controller
* LCD1062A display
* DHT11 sensor
* 3.3 (KΩ) resistor - must
* 220 (Ω) resistor - optinal

notice that the display can require different resistence from the must resistor (recommended first to check with variable resistor 50KΩ).

## suggestions:

**Work with LCD1602A** - this device has a lot of dependencies on voltage input, so i recommend to use the electrical scheme.

**Saving power** - I tried to apply 2 methods to reduce power consumption:
1. optional resistor - effect the screen brightness.
2. change Pico frequency to 50 (MHZ) - below that the screen didn't response.

Minimum device consumption - 17 (mA)

**Wiring** - the pins in the electric shceme defined in the code, so if you wish to change some of them make sure you stay consistent.

**Modeling Box** - created in SolidWorks.
This model builded to be suitable to my soldered board, most of the distances are reletive so you can easily change them.

## Photos of proccess:

![Alt text](/photos/1.jpeg)

![Alt text](/photos/2.jpeg)

![Alt text](/photos/3.jpeg)