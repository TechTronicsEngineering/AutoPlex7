# AutoPlex7
### Control seven segment displays with ease.

AutoPlex7 is a simple and versatile Arduino library for controlling seven segment displays with up to four digits. Unlike many other libraries for this purpose, AutoPlex7 automatically multipexes itself using Timer2. This means no calls to refresh the display; enabling AutoPlex7 to work with delays in your code.

### Features
- Automatic multiplexing
- Built to work with delays in your code
- Works with both common cathode and common anode displays
- Has a flexible pin layout; letting you connect any display pin to any of Arduino's digital pins
- Built-in, global "display" object

### Usage
At the top of your sketch, you'll need to define a few paremeters. Firstly, we'll tell the Arduino what type of display you're using, like this:
```C++
int displayType = COMMON_ANODE
```
If you're using a common cathode display, just replace "COMMON_ANODE" with "COMMON_CATHODE."
Next, we'll need to define the digital pins your seven segment display is connected to. We'll start with the digit pins.
```
int D1 = // Type the digital pin D1 is connected to here
int D2 = // Type the digital pin D2 is connected to here
int D3 = // Type the digital pin D3 is connected to here
int D4 = // Type the digital pin D4 is connected to here.
```
**IMPOTANT NOTE:** Even if your display does not have four digits, you'll still need to define the pins for the digits you don't have. Just leave these pins unconnected.
