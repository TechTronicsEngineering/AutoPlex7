/*
  Second Counter

  This sketch will count seconds since the last reset on a four-digit seven segment display.

  The circuit:
  - Display pin A -> Arduino digital pin 5
  - Display pin B -> Arduino digital pin 6
  - Display pin C -> Arduino digital pin 7
  - Display pin D -> Arduino digital pin 8
  - Display pin E -> Arduino digital pin 9
  - Display pin F -> Arduino digital pin 10
  - Display pin G -> Arduino digital pin 11
  - Display pin DP -> Arduino digital pin 12
  - Display Digit pin 1 -> 270Ω -> Arduino pin 1
  - Display Digit pin 2 -> 270Ω -> Arduino pin 2
  - Display Digit pin 3 -> 270Ω -> Arduino pin 3
  - Display Digit pin 4 -> 270Ω -> Arduino pin 4

  created 10/12/2025
  by Nyjah

  This example sketch is in the public domain.
*/

#include <AutoPlex7.h>

AutoPlex7 display; // Create a display object

// Create counter variable
unsigned long seconds = 0;

void setup() {
  bool displayType = COMMON_CATHODE; // Change to COMMON_ANODE if using a common anode display
  byte displayDigits = 4; // The display has 4 digits
  byte digitPins[] = {1, 2, 3, 4}; // D1, D2, D3, D4
  byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12}; // A, B, C, D, E, F, G, DP

  display.begin(displayType, displayDigits, digitPins, segmentPins); // Initialize the display
  display.testDisplay(1000); // Show all digits, numbers, and decimals for one second
}

void loop() {
  display.showNumber(seconds); // Show the current number of seconds counted
  delay(1000); // Wait one second
  seconds++; // Add 1 to the seconds counter
}
