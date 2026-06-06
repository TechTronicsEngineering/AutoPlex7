# AutoPlex7
### Control seven segment displays with ease.

AutoPlex7 is a simple and versatile Arduino library for controlling seven segment displays with up to eight digits. Unlike many other libraries for this purpose, AutoPlex7 automaticallyhandles multiplexing in the background using Timer1. This means no calls to refresh the display; enabling AutoPlex7 to work with delays or other blocking functions in your code.

## Features
- Automatic multiplexing
- Built to work with delays in your code
- Works with both common cathode and common anode displays with up to 8 digits (can be easily modified to support over 200)
- Has a flexible pin layout; letting you connect any display pin to any of Arduino's digital pins

## Warning
When using AutoPlex7 (or any other direct seven segment display controller software), it is extremely important to use current limiting resistors in your circuit. Failure to do this can and will damage both the microcontroller and display. With a 5V supply, it is advised to use a resistor of at least 270 ohms on the digit pins.

## Setup
At the top of your sketch, you'll need to configure a few parameters for the library to work properly. First, we'll need to state that we are using AutoPlex7, like this:
```C++
#include <AutoPlex7.h>
```

Afterwards, we'll need to create an instance of the AutoPlex7 class. You can name it whatever you like, but in this example, let's call it "MyDisplay."
```C++
AutoPlex7 MyDisplay;
```

Now that we have a display object, we need to enable it's multiplexing. AutoPlex7 utilizes Timer1 to generate an interrupt every millisecond, and when this happens, the library should render the next character on the display. Setting this up is very easy, and takes just three lines of code:
```C++
ISR(DISPLAY_REFRESH) {
  MyDisplay.multiplex();
}
```

Next, you'll need to configure a few settings and initiallize the display. This should be done within setup(). 
```C++
void setup() {
  bool displayType = /* Select either "COMMON_CATHODE" or "COMMON_ANODE" */;
  byte displayDigits = /* Replace this comment with the number of digits your display has */;
  byte digitPins[] = { /* D1, D2, D3... */ }; // Replace with your desired pin numbers
  byte segmentPins[] = { /* A, B, C, D, E, F, G, DP */ }; // Replace with your desired pin numbers

  MyDisplay.begin(displayType, displayDigits, digitPins, segmentPins); // Initiallize the display and pass the parameters to it
}
```
This will complete the setup process and activate the display. Here's an example of what the beginning of a sketch using AutoPlex7 could look like.
```C++
#include <AutoPlex7>

AutoPlex7 MyDisplay;

ISR(DISPLAY_REFRESH) {
  MyDisplay.multiplex();
}

void setup() {
  bool displayType = COMMON_CATHODE;
  byte displayDigits = 4;
  byte digitPins[] = {1, 2, 3, 4};
  byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12};

  MyDisplay.begin(displayType, displayDigits, digitPins, segmentPins);
}
```
It's generally recommended that, after calling ```MyDisplay.begin()``` you use the built in display test command to ensure functionality of the display.
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
