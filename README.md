# AutoPlex7
### Control seven segment displays with ease.
AutoPlex7 is a simple and versatile Arduino library for controlling seven segment displays with up to eight digits. Unlike traditional seven segment libraries, AutoPlex7 automatically handles multiplexing in the background using Timer0. This means no calls to refresh the display; enabling AutoPlex7 to work with delays or other blocking functions in your code.

## Features
- Automatic multiplexing
- Built to work with delays in your code
- Works with both common cathode and common anode displays with up to eight digits (can be internally modified to support well beyond eight)
- Has a flexible pin layout; letting you connect any display pin to any of Arduino's digital pins

## How to install
To use AutoPlex7 in an Arduino sketch, you'll need to install it.
This can be done one of two ways:

##### 1. Through Github
Locate the large green button labeled "Code" on this repository's homepage. Click it and select "Download ZIP."
Launch the Arduino IDE and locate the menu labelled "Sketch" on the top left. Open it, select "Include library" -> "Add .ZIP library." Navigate to your recent downloads and select AutoPlex7.
This method ensures you get the latest version of the library.

##### 2. Directly from the Arduino IDE
Open the IDE. Find the icon on the left with the stack of books and hover text "library manager," then click on it. This should open a small menu. Search for "AutoPlex7," and click install.

Once the library has been successfully installed, you may proceed.

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

Next, you'll need to configure a few settings and initialize the display. This should be done within setup(). 
```C++
void setup() {
  bool displayType = /* Select either "COMMON_CATHODE" or "COMMON_ANODE" */;
  byte displayDigits = /* Replace this comment with the number of digits your display has */;
  byte digitPins[] = { /* D1, D2, D3... */ }; // Replace with your desired pin numbers
  byte segmentPins[] = { /* A, B, C, D, E, F, G, DP */ }; // Replace with your desired pin numbers

  MyDisplay.begin(displayType, displayDigits, digitPins, segmentPins); // Initialize the display and pass the parameters to it
}
```
This will complete the setup process and activate the display. Here's an example of what the beginning of a sketch using AutoPlex7 could look like for a four digit common cathode display.
```C++
#include <AutoPlex7.h>

AutoPlex7 MyDisplay;

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
MyDisplay.testDisplay(1000);
```
###### *The "1000" means the test lasts for 1,000 milliseconds (1 second). A different test duration can be input if desired, or none at all if you'd like to calculate the timing manually.*

## Commands
Now that you've initialized and tested your display, you can start using it. Let's take a look at the functions you can use to control the screen. We'll start with the most straightforward:

### Writing to the display
AutoPlex7 allows for display of three distinct data types using the `print()` method: integers, floats, and strings.

###### For integers:
To show a whole number on the seven segment display, you can use:
```C++
MyDisplay.print(int32_t num);
```
This shows any integer you pass to it on the display. For example, if you wish to show "1234"...
```C++
MyDisplay.print(1234);
```

###### Displaying a float
The `print()` method also accepts floats/doubles.
```C++
MyDisplay.print(double num, uint8_t decimalPlaces);
```
This method takes two arguments. The first one is the value to print, and the second is the number of digits to show after the decimal point.

###### Displaying a string
Recent versions of AutoPlex7 also accept C-style string/character array input.
```C++
MyDisplay.print(const char* text);
```
This allows you to show a wide variety of characters - numbers, decimals, symbols, and all 26 letters (though some are approximations) of the alphabet.
Using it to show something like "Abcd" is as simple as this:
```C++
MyDisplay.print("Abcd");
```

### Appending characters to the display
The AutoPlex7 library uses a char[] buffer to internally store the contents of the display. It is possible to append more characters directly to this buffer without clearing its original contents. This is especially useful if you're looking to display numeric data alongside units. Appending new display contents may be performed with:
```C++
MyDisplay.append(...);
```
The `append()` method can handle character arrays, integers, and floats/doubles.

If you want to append a character array, say "°C", to the display:
```C++
MyDisplay.append("*C"); // "*" is displayed as "°"
```

An integer:
```
MyDisplay.append(10);
```

Or a float:
```
MyDisplay.append(3.1415926536, 3); // Shows pi with 3 digits after the decimal
```

###### *NOTE: it is strongly discouraged to use this method heavily with automated multiplexing. Should you choose to, you may notice significant flicker on the display. This is due to rendering of temporary or partially overwritten display states caused by interrupts. If you need to use the ```append()``` method often, it's best disable automatic multiplexing and call `multiplex()` manually within ```loop().``` Be aware that this will mandate non-blocking code.*

### Clearing the display
From time to time, you might find yourself needing to clear the display. That can be done by simply calling:
```C++
MyDisplay.clear();
```

### Multiplexing
AutoPlex7 features a built-in `MyDisplay.multiplex()` method that refreshes the display. In AutoPlex7's typical configuration, it is called automatically on an interrupt under the hood. However, this can be disabled per-instance if desired. This allows you to call `multiplex()` from `loop(),` granting you finer control over the display. As this mandates non-blocking code, it is not recommended for starters, but automatic display refreshes may be disabled when calling `begin()` on a new display object.
Instead of calling:
```MyDisplay.begin(displayType, displayDigits, digitPins, segmentPins);```
... to initialize a new display, you can replace it with:
```Mydisplay.begin(displayType, displayDigits, digitPins, segmentPins, MANUALPLEX);```
This avoids registering display instance for the multiplexing interrupt routine.

## Using multiple displays
Recent updates of AutoPlex7 were redesigned to support the use of multiple displays at once.
Using two displays is almost identical to using one; just make sure to name the parameter variables differently for each instance to prevent compilation errors.

A simple sketch using two displays:
```C++
#include <AutoPlex7.h> // Include the AutoPlex7 library

AutoPlex7 display1; // First display
AutoPlex7 display2; // Second display

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

  // Segment test the displays
  display1.testDisplay();
  display2.testDisplay();
  delay(1000); // 1 second segment test
  display1.clear();
  display2.clear();
}

void loop() {
  display1.print(1234);
  display2.print("HI.");
}
```

## Using transistor drivers for improved brightness
AutoPlex7 can also run displays that use transistor drivers on the digit pins, a technique used to prouduce higher, more even brightness. When you initialize the display, simply swap displayType for a byte, as opposed to a bool, and set it to either CCWDDT (**C**ommon **C**athode **W**ith **D**igit **D**rive **T**ransistors) or CAWDDT (**C**ommon **A**node **W**ith **D**igit **D**rive **T**ransistors)
###### Note that common anode displays will require PNP transistor drivers, whereas common cathodes need NPN drivers.
```C++
void setup() {
  byte displayType = CCWDDT; // Change to CAWDDT if using a common anode display
  ...
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
