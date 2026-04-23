# Tester for the esp32-app-board

The [esp32_app_bpard_tester](./esp32_app_board_tester/) folder contains sample code that can be used to manual test the various features of this board.

## Prerequisites

To test the Real-Time Clock feature of the board install the following libraries:
- [Adafruit BusIO by Adafruit](https://github.com/adafruit/Adafruit_BusIO)
- [RTCLib by Adafruit](https://github.com/adafruit/RTClib)

## Configuration

Select which feature you want to test by setting the value of the `#define`-d constant at the top of the file to `1`. 

For example to test the RGB LED:

```cpp
#define TEST_RGB_LED_CA 1
```

NOTE: The tests are not designed to execute at the same time, so all other constant must be set to `0` !