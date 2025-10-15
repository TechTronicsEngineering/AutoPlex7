/*
  Second Counter

  This sketch will count seconds since the last reset on a seven segment display.

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
  - Display Digit pin 2 -> 270Ω -> Arduino pin 2 (if you don't have two digits, just leave pin 2 unused)
  - Display Digit pin 3 -> 270Ω -> Arduino pin 3 (if you don't have three digits, just leave pin 3 unused)
  - Display Digit pin 4 -> 270Ω -> Arduino pin 4 (if you don't have four digits, just leave pin 4 unused)

  created 10/12/2025
  by Nyjah

  This example sketch is in the public domain.
*/

#include <AutoPlex7.h>

// Set up display
int displayType = COMMON_ANODE; // Change to "COMMON_CATHODE" if using a common cathode display
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

// Create counter variables
unsigned long previousMillis = 0;
const long interval = 1000;
long seconds = 0;

void setup() {
display.begin(); // Initialize the display
display.testDisplay(); // Run test to ensure functionality
delay(1000); // Wait one second
display.clearDisplay(); // Clears the display
}

void loop() {
unsigned long currentMillis = millis(); // Get the current time

  if (currentMillis - previousMillis >= interval) {
    // Save the last time you updated the counter
    previousMillis = currentMillis;

    seconds++; // Increment the seconds counter

    display.showNumber(seconds); // Show the number of seconds on the screen
  }
}
