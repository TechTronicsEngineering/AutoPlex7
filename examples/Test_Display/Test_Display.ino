/*
  Test Display

  This code will show a series of numbers, decimals, animations, and other functions. It works best on four digit displays.

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

// Set up the type of display and connections
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

void setup() {
display.begin(); // Initialize the display
display.testDisplay(); // Activate all digits, segments, and decimals
delay(1000); // Wait one second
display.clearDisplay(); // Clear the display
}

void loop() {
display.showNumber(1234); // Display "1234"
delay(1000); // Wait one second
display.clearDisplay(); // Clear the display
display.showNumber(2345); // Show the next number "2345"
delay(100); // Wait one second
display.clearDisplay(); // Clear the display...
display.showNumber(3456);
delay(100);
display.clearDisplay();
display.showNumber(4567);
delay(100);
display.clearDisplay();
display.showNumber(5678);
delay(100);
display.clearDisplay();
display.showNumber(6789);
delay(100);
display.clearDisplay();
display.showNumber(7890);
delay(1000);
display.clearDisplay();

delay(250); // Wait 0.25 seconds

display.setDigit(1); // Select a digit
display.showDecimal(); // Show the decimal
delay(100); // Wait 0.1 seconds
display.setDigit(2); // Move to the next digit
display.showDecimal(); // Show this decimal
delay(100); // Wait 0.1 seconds...
display.setDigit(3);
display.showDecimal();
delay(100);
display.setDigit(4);
display.showDecimal();
delay(1000);
display.showNumber(1234); // Display the number "1234"
delay(1000); // Wait one second
display.clearDisplay(); // Clear the display
}
