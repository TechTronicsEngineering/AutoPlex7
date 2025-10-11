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
At the top of your sketch, you'll need to set up a few things for the library to work properly. Firstly, we'll need to state that we are using AutoPlex7, like this.
```C++
#include <AutoPlex7.h>
```
Next, let's define a few paremeters. Right under the last line of code, you can tell the Arduino what type of display you're using, like this:
```C++
int displayType = COMMON_ANODE;
```
If you're using a common cathode display, just replace "COMMON_ANODE" with "COMMON_CATHODE."

Now, we'll define the digital pins your seven segment display is connected to. We'll start with the digit pins.
```C++
int D1 = // Type the digital pin D1 is connected to here;
int D2 = // Type the digital pin D2 is connected to here;
int D3 = // Type the digital pin D3 is connected to here;
int D4 = // Type the digital pin D4 is connected to here;
```
**IMPOTANT NOTE:** Even if your display does not have four digits, you'll still need to define the pins for the digits you don't have. Just leave these pins unconnected. For instance, if you use a two digit display, you could write that D3 and D4 are connected to pins 12 and 13. Leave pins 12 and 13 unused.

Next, we'll define what Arduino pins the display's segment pins are connected to.
```C++
int A = // Type the digital pin A is connected to here;
int B = // Type the digital pin B is connected to here;
int C = // Type the digital pin C is connected to here;
int D = // Type the digital pin D is connected to here;
int E = // Type the digital pin E is connected to here;
int F = // Type the digital pin F is connected to here;
int G = // Type the digital pin G is connected to here;
int DP = // Type the digital pin the decimal point is connected to here;
```
That's it for the paremeters we have to define! Here's an example of what the beginning of a sketch using AutoPlex7 could look like.
```C++
#include <AutoPlex7.h>

int displayType = COMMON_CATHODE;
int D1 = 1;
int D2 = 2;
int D3 = 3;
int D4 = 4;
int A = 5;
int B = 6;
int C = 7;
int D = 8;
int E = 9;
int F = 10;
int G = 11;
int DP = 12;
```
