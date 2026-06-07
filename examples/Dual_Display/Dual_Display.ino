/*
  Dual Display

  This sketch demonstrates how AutoPlex7 may be used to manipulate two displays simultaneously.
  
  In this example, we'll use 2x 3-digit 7-segment displays.
  The first display ("SecondsDisplay") will display the whole number of seconds since the last reset.
  The second display ("FractionalDisplay") will show the fractional number of seconds (with three digits precision) since the last reset.
  
  This example sketch is for use on large AVR boards (e.g., Arduino Mega) only, as it uses up twenty-two digital pins.

  The circuit:
  - Display1 pin A -> Arduino digital pin 4
  - Display1 pin B -> Arduino digital pin 5
  - Display1 pin C -> Arduino digital pin 6
  - Display1 pin D -> Arduino digital pin 7
  - Display1 pin E -> Arduino digital pin 8
  - Display1 pin F -> Arduino digital pin 9
  - Display1 pin G -> Arduino digital pin 10
  - Display1 pin DP -> Arduino digital pin 11
  - Display1 Digit pin 1 -> 270Ω -> Arduino pin 1
  - Display1 Digit pin 2 -> 270Ω -> Arduino pin 2
  - Display1 Digit pin 3 -> 270Ω -> Arduino pin 3
  - Display2 pin A -> Arduino digital pin 17
  - Display2 pin B -> Arduino digital pin 18
  - Display2 pin C -> Arduino digital pin 19
  - Display2 pin D -> Arduino digital pin 20
  - Display2 pin E -> Arduino digital pin 21
  - Display2 pin F -> Arduino digital pin 22
  - Display2 pin G -> Arduino digital pin 23
  - Display2 pin DP -> Arduino digital pin 24
  - Display2 Digit pin 1 -> 270Ω -> Arduino pin 14
  - Display2 Digit pin 2 -> 270Ω -> Arduino pin 15
  - Display2 Digit pin 3 -> 270Ω -> Arduino pin 16

  created 10/12/2025
  by Nyjah

  This example sketch is in the public domain.
*/

#include <AutoPlex7.h>

AutoPlex7 SecondsDisplay; // Create an instance of AutoPlex7 for the seconds display
AutoPlex7 FractionalDisplay; // Create an instance of AutoPlex7 for the fractional display

ISR(DISPLAY_REFRESH) { // Set up automatic multiplexing for each display
  SecondsDisplay.multiplex();
  FractionalDisplay.multiplex();
}

void setup() {
  bool displayType1 = COMMON_CATHODE; // Change to "COMMON_ANODE" if using a common anode display
  byte displayDigits1 = 3; // Display has 3 digits
  byte digitPins1[] = {1, 2, 3}; // D1, D2, D3
  byte segmentPins1[] = {4, 5, 6, 7, 8, 9, 10, 11}; // A, B, C, D, E, F, G, DP

  SecondsDisplay.begin(displayType1, displayDigits1, digitPins1, segmentPins1);

  bool displayType2 = COMMON_CATHODE; // Change to "COMMON_ANODE" if using a common anode display
  byte displayDigits2 = 3; // Display has 3 digits
  byte digitPins2[] = {14, 15, 16}; // D1, D2, D3
  byte segmentPins2[] = {17, 18, 19, 20, 21, 22, 23, 24}; // A, B, C, D, E, F, G, DP

  FractionalDisplay.begin(displayType2, displayDigits2, digitPins2, segmentPins2);
}

void loop() {
  unsigned long seconds = millis() / 1000; // Calculate the whole number of seconds
  unsigned long fraction = millis() % 1000; // Calculate the number after the decimal
  SecondsDisplay.showNumber(seconds); // Show the number of elapsed seconds on the first display
  SecondsDisplay.append("."); // Append a decimal to highlight that the next display shows the numbers after the dot. Be careful with the append() function and auto-multiplexing. It may cause flicker if used heavily. Used sparingly, as shown, is okay
  FractionalDisplay.showNumber(fraction); // Show the numbers after the decimal on the 2nd display
}
