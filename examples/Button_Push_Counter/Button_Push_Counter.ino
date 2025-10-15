/*
  Button Push Counter

  This sketch will count how many times a button is pressed and show it on a seven segment display.

  The circuit:
  - Pushbutton connected between pin 13 and ground
  - Display pin A -> 270Ω -> Arduino digital pin 5
  - Display pin B -> 270Ω -> Arduino digital pin 6
  - Display pin C -> 270Ω -> Arduino digital pin 7
  - Display pin D -> 270Ω -> Arduino digital pin 8
  - Display pin E -> 270Ω -> Arduino digital pin 9
  - Display pin F -> 270Ω -> Arduino digital pin 10
  - Display pin G -> 270Ω -> Arduino digital pin 11
  - Display pin DP -> 270Ω -> Arduino digital pin 12
  - Display Digit pin 1 -> Arduino pin 1
  - Display Digit pin 2 -> Arduino pin 2 (if you don't have two digits, just leave pin 2 unused)
  - Display Digit pin 3 -> Arduino pin 3 (if you don't have three digits, just leave pin 3 unused)
  - Display Digit pin 4 -> Arduino pin 4 (if you don't have four digits, just leave pin 4 unused)

  created 10/12/2025
  by Nyjah

  This example sketch is in the public domain.
*/

#include <AutoPlex7.h>

// Set up the display type and connections
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

const int buttonPin = 13; // Define what pin the button is connected to

int buttonPushCounter = 0; // Counter for the number of button presses
int buttonState = 0; // Current state of the button
int lastButtonState = 0; // Previous state of the button

void setup() {
pinMode(buttonPin, INPUT);  // Set this pin as an input
display.begin(); // Activate the display
display.testDisplay(); // Show all digits, numbers, and decimals
delay(1000); // Wait one second
display.clearDisplay(); // Clear the display
}

void loop() {
  // Watch for button presses
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
    }
    delay(50);
  }

  lastButtonState = buttonState;

  if (buttonPushCounter == 10000) {
    buttonPushCounter = 0; // Reset counter so it doesn’t get too large
  }

  display.showNumber(buttonPushCounter); // Display the number of presses
}
