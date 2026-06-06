# AutoPlex7
### Control seven segment displays with ease.

AutoPlex7 is a simple and versatile Arduino library for controlling seven segment displays with up to eight digits. Unlike many other libraries for this purpose, AutoPlex7 automatically handles multiplexing in the background using Timer1. This means no calls to refresh the display; enabling AutoPlex7 to work with delays or other blocking functions in your code.

## Features
- Automatic multiplexing
- Built to work with delays in your code
- Works with both common cathode and common anode displays with up to 8 digits (can be easily modified to support over 200)
- Has a flexible pin layout; letting you connect any display pin to any of Arduino's digital pins

## How to install
To use AutoPlex7 in an Arduino sketch, you'll need to install it.
This can be done one of two ways:

##### 1. Through Github
Locate the large green button labeled "Code" on this repository's homepage. Click it and select "Download ZIP."
Launch the Arduino IDE and locate the menu labled "Sketch" on the top left. Open it, select "Include library" -> "Add .ZIP library." Navigate to your recent downloads and select AutoPlex7.
This method ensures you get the latest version of AutoPlex7.

##### 2. Directly from the Arduino IDE
Open the IDE. Find the icon on the left with the stack of books and hover text "library manager," then click on it. This should open a small menu. Search for "AutoPlex7," and click install.

Once the library has been succesfully installed, you may proceed.

## Setting up AutoPlex7
When using AutoPlex7, you'll need to configure a few parameters at the top of your sketch for the library to work properly.
First, we'll need to state that the program is using AutoPlex7, like this:
```C++
#include <AutoPlex7.h>
```

Below that, we'll need to create an instance of the AutoPlex7 class. You can name it whatever you like, but in this example, we'll call it "MyDisplay."
```C++
AutoPlex7 MyDisplay;
```

Now that we have a display object, we need to enable it's automated multiplexing. AutoPlex7 utilizes Timer1 to generate an interrupt every millisecond, and when this happens, the library should render the next character on the display. Setting this up is very easy, and takes just three lines of code:
```C++
ISR(DISPLAY_REFRESH) {
  MyDisplay.multiplex();
}
```
###### *If you're using more than one display, make sure to call multiplex() on all instances within the ISR.*

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
This will complete the setup process and activate the display. Here's an example of what the beginning of a sketch using AutoPlex7 could look like for a four digit common cathode display.
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
It's generally recommended that, after calling ```begin()``` you use the built in segment test command to ensure functionality of the display.
```C++
display.testDisplay(1000);
```
###### *The "1000" means the test lasts for 1,000 milliseconds (1 second). A different test duration can be input if desired. This is a blocking function.*

## Commands
Now that you've initiallized and tested your display, you can start using it. Let's take a look at the functions you can use to control the screen. We'll start with the most straightforward:

### Writing to the display
AutoPlex7 features three distinct functions for printing different data types on the display.

###### For integers:
To show a whole number on the seven segment display, you can call:
```C++
MyDisplay.showNumber(int32_t num);
```
This function shows any integer you pass to it on the display. For example, if you wish to show "1234," you can do this:
```C++
MyDisplay.showNumber(1234);
```
However, it does not support decimals, and that's where the next function comes in:

###### Displaying a float
AutoPlex7 features a separate function for displaying floats/doubles.
```C++
MyDisplay.showNumberF(double num, uint8_t decimalPlacses)
```
This special ```setNumberF``` function accepts two arguments. The first one is the value to print, and the second is the number of digits to show after the decimal point.

###### Displaying a string
The most recent versions of AutoPlex7 also accept string input.
```C++
MyDisplay.print(const char* text)
```
This is considered the easiest way to manipulate the display, and also the most versatile. It supports many different characters - numbers, decimals, symbols, and all 26 letters (though some are approximations) of the alphabet.
Using ```print()``` to show something like "Abcd" is as simple as this:
```C++
MyDisplay.print("Abcd")
```

### Clearing the display
From time to time, you mignt fudn yourself needing to clear the display. That can be done by sinply calling:
```C++
MyDisplay.clear();
```
### Multiplexing
AutoPlex7 features a built-in
```C++
MyDisplay.multiplex()
```
function that refreshes the display. It's deisgned to be continuously called from an ISR, but it may be removed from that and multiplexing performed manually if desired.

## Using multiple displays
Recent updates of AutoPlex7 were redesigned to support the use of multiple displays at once.
Using two displays is almost exactky the same as using one; but just make sure to call multiplex() on all AutoPlex7 instances within the ISR and name paremeter variables differently for each display to prevent compilation errors.

A simple sketch using two displays:
```C++
#include <AutoPlex7.h> // Include the AutoPlex7 library

AutoPlex7 display1; // First display
AutoPlex7 display2; // Second display

ISR(DISPLAY_REFRESH) {
  // Multiplex both displays
  display1.multiplex();
  display2.multiplex();
}

void setup() {
  // Assuming display1 is a 4-digit common cathode...
  bool displayType1 = COMMON_CATHODE;
  byte displayDigits1 = 4;
  byte digitPins1[] = {1, 2, 3, 4};
  byte segmentPins1[] = {5, 6, 7, 8, 9, 10, 11, 12};
  display1.begin(displayType1, displayDigits1, digitPins1, segmentPins1);

  // Assuming display2 is a two-digit common anode...
  bool displayType2 = COMMON_ANODE;
  byte displayDigits2 = 2;
  byte digitPins2[] = {13, 14};
  byte segmentPins2[] = {15, 16, 17, 18, 19, 20, 21, 22};
  display2.begin(displayType2, displayDigits2, digitPins2, segmentPins2);

  // Segment test the displays. Must be done manually with two displays; if you wish them to test simultaneously.
  display1.print("8.8.8.8.");
  display2.print("8.8.");
  delay(1000); // 1 second segment test
  display1.clear();
  display2.clear();
}

void loop() {
  display1.showNumber(1234);
  display2.print("HI.");
}
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
