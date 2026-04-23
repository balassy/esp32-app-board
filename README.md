# ESP32 App Board

A custom PCB designed to quickly start projects based on the ESP32-WROOM-32 module.

![Preview top](<./preview-top.jpg>)

![Preview bottom](<./preview-bottom.jpg>)

## Features

- Socket for the ESP32-WROOM-32 module.
- Separate pin headers for all 30 pins of the ESP32-WROOM-32 module with large solder pads on the top layer.
- Screw terminal for the +5V Vin and GND pins.
- 2+1 extra pins for the +3.3V pin.
- 2+1+4 extra pins for the GND pin.
- 2+1+4 extra pins for the +5V pin. 
- 4 GND-5V-GPIO pins positioned to easily connect 4 servos.
- Buzzer.
- Tactile button with pin headers for a parallel external button. 
- 5 GPIO ports with custom resistors (e.g. for external LEDs).
- ZS-042 Real Time Clock module, mounted with battery up.
- Pin headers for external I2C module.
- 5mm RGB LED, either common anode or common cathode.
- 6×8 pin matrix for additional parts.
- 3mm diameter mounting screw holes.

## GPIO Pins

- Button: D32 (other pin connected to GND).
- Buzzer positive (+): D23 (other pin connected to GND).
- Pins with custom resistor: D12, D13, D14, D26, D27. The resistors are marked as R12, R13, R14, R26 and R27 accordingly. Shortcut wires must be installed if these pins are used directly.
- RGB LED: D12, D13, D14. The LED pin header MUST be used to select between common anode (CA) and common cathode (CC) LEDs.
- I2C: SDA D21, SCL D22. 

Which pin to use? Read more: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

## Wiring

![Wiring](<./wiring.jpg>)

## Dimensions

![Dimensions](<./dimensions.jpg>)

The mounting holes of the PCB are 3mm diameter.

The mounting holes of the ZS-042 module are 2mm diameter.

The Fusion 360 model in the [3d](./3d/) folder contains these dimensions.

## What's in this repo

- [3d](./3d/): Fusion 360 models used to generate the dimension drawing, and a 3D printable stand. You can use it to build a custom case for this panel.
- [code](./code/): Simple source code to manual test the features of the PCB.
- [gerber](./gerber/): The Fritzing-generated Gerber files that can be used to manufacture the PCB. 
- [parts](./parts/): The custom Fritzing parts used to build this board.
- [source](./source/): The original, editable source file of this PCB, created with Fritzing.


## Parts used

The following parts have been used in this project:

- 2-pin screw terminal connector with 5mm spacing, created by [Blue](https://forum.fritzing.org/t/35-new-edited-parts/6361).
- ZS-042 Real Time Clock module, created by [György Balássy](https://github.com/balassy/fritzing-parts).
- ESP32-WROOM-32 module, created by [György Balássy](https://github.com/balassy/fritzing-parts).

You can find these in the [parts](./parts/) folder, and they must be imported into Fritzing before opening the PCB.


## Autoroute steps

Follow these steps to generate the PCB wiring:

1. Routing --> Autorouter/DRC Settings: Custom - Trace width: thin (16 mil)
2. Routing --> Select All Autoroutable Traces --> Delete
3. Routing --> Select All Vias --> Delete
4. Routing --> Autoroute
5. Routing --> Show Unrouted. `There are no unrouted connections` message should appear. If not, try increasing the iteration count in the Autoroute dialog.
6. Routing --> Design Rules Check (DRC). Click the errors one by one to highlight the problem with red (they are hard to see). Hide the silkscreen and the unrelated copper layer and reposition the wires. Turn off View --> Aligh to Grid.
7. Re-run the Design Rules Check until `Your sketch is ready for production` message appers.
8. Routing --> Ground Fill --> Ground Fill (top and bottom).


## Verify the layout

Follow these steps to print the design onto paper with 1:1 dimentions:

1. In Fritzing click File --> Export --> as Image --> SVG. 
2. Open the SVG in Inkscape or other editing program.
3. Remove the unnecessary items (e.g. Fritzing logo)
4. Change the Format to A4 in Document Properties.
5. Print to paper.

## Generate Gerber files

The latest Gerber files to manufacture the PCB is available in the [gerber](./gerber/) folder.

To re-generate them in Fritzing click File --> Export --> for Production --> Extended Gerber, then select the [gerber](./gerber/) folder.

## About the author

This project is created and maintained by [György Balássy](https://www.linkedin.com/in/balassy).