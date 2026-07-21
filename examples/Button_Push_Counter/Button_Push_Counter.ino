/*
  Button Push Counter

  This sketch will count how many times a button is pressed and show it on a four-digit seven segment display.

  The circuit:
  - Pushbutton connected between pin 13 (which is pulled high through a 10K resistor) and ground
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

const byte buttonPin = 13; // The pin the pushbutton is connected to

unsigned int buttonPushCounter = 0; // Counter for the number of button presses
bool buttonState = 0; // Current state of the button
bool lastButtonState = 0; // Previous state of the button

void setup() {
  pinMode(buttonPin, INPUT);  // Set the button pin as an input
  bool displayType = COMMON_CATHODE; // Change to COMMON_ANODE if using a common anode display
  byte displayDigits = 4; // The display has 4 digits
  byte digitPins[] = {1, 2, 3, 4}; // D1, D2, D3, D4
  byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12}; // A, B, C, D, E, F, G, DP

  display.begin(displayType, displayDigits, digitPins, segmentPins); // Initialize the display
  display.testDisplay(1000); // Show all digits, numbers, and decimals for one second
}

void loop() {
  // Watch for button presses
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) { // If the buttonState changed...
    if (buttonState) { // If the buttonPun is HIGH...
      buttonPushCounter++; // Increment the button push variable
    }
    delay(50); // Debounce
  }

  lastButtonState = buttonState;

  if (buttonPushCounter >= 10000) {
    buttonPushCounter = 0; // Reset counter so it doesn’t get too large
  }

  display.showNumber(buttonPushCounter); // Display the number of presses
}
