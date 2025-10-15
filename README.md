# AutoPlex7
### Control seven segment displays with ease.

AutoPlex7 is a simple and versatile Arduino library for controlling seven segment displays with up to four digits. Unlike many other libraries for this purpose, AutoPlex7 automatically multipexes itself using Timer2. This means no calls to refresh the display; enabling AutoPlex7 to work with delays in your code.

## Features
- Automatic multiplexing
- Built to work with delays in your code
- Works with both common cathode and common anode displays
- Has a flexible pin layout; letting you connect any display pin to any of Arduino's digital pins
- Built-in, global "display" object

## Warning
When using AutoPlex7 (or any other direct seven segment display controller software), it is extremely important to use a current limiting resistor in your circuit. Failure to do this can and will damage both the microcontroller and display. With a 5V supply, it is advised to use a resistor of at least 270 ohms on the digit pins.

## Setup
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
**IMPOTANT NOTE:** Even if your display does not have four digits, you'll still need to define the pins for the digits you don't have. Just leave these pins unconnected. For instance, if you use a two digit display, you could write that D1 is connnected to pin 1, D2 to 2, D3 to 3, and D4 is 4. You would wire it so that D1 connects to pin 3, and D2 to pin 4. Leave pins 1 and 2 unused.
(Essentially, just wire it so that the largest pin number is connected to the same pin in the code as it is in the circuit, and connect each pin moving backwards from there.)

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

After you're done setting up the paremeters, you'll need to initiallize the seven segment display in ```setup()```. This can be done by calling:
```C++
display.begin();
```
This will complete the setup process and activate the display.
It's generally recommended that, after calling ```display.begin()``` you use the built in display test command to ensure functionality of the display.
```C++
display.testDisplay();
```
This will light up all digits, segments, and decimals.
After this, you can use ```delay(1000)``` to wait one second, and then clear the display.
```C++
display.clearDisplay();
```
This turns off all digits, segments, and decimals. The display is ready for use.

## Commands
Now that you've initiallized ths display, you can start using it. Let's take a look at the commands you can use to control the screen. We'll start with the most straightforward:

### Show a number
```C++
display.showNumber(int number);
```
This command simply shows any number you put in the parenthesis on the screen. For example, if you wish to display "1234," you can do this:
```C++
display.showNumber(1234);
```
You can also put a variable in the parenthesis.
```C++
display.showNumber(voltageatpinA5);
```

### Clearing the display
From time to time, you'll need to clear the display. That can be done using:
```C++
display.clearDisplay();
```

### Working with decimals
If you need to show a decimal, you can use these two commands in combination:
```C++
display.setDigit(// Choose which digit to show the decimal on by typing it's number);
display.showDecimal():
```
To get rid of a decimal:
```C++
display.setDigit(// Choose which digit to clear the decimal on by typing it's number);
display.clearDecimal();
```

## Copyright Notice
MIT License

Copyright (c) 2025 TechTronicsEngineering

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE
