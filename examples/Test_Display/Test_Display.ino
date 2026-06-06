/*
  Test Display

  This code will show a series of animations on a four-digit seven segment display.

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

// Enable automatic multiplexing
ISR(DISPLAY_REFRESH) {
  display.multiplex();
}

void hello() { // This function draws a scrolling "HELLO" animation
  display.print("   H");
  delay(100);
  display.print("  HE");
  delay(100);
  display.print(" HEL");
  delay(100);
  display.print("HELL");
  delay(100);
  display.print("ELLO");
  delay(100);
  display.print("LLO ");
  delay(100);
  display.print("LO  ");
  delay(100);
  display.print("O   ");
  delay(100);
  display.clear();
  delay(100);
}

void introduceAutoPlex7() {
  // Write an animation that explains AutoPlex7 on the display
  display.print("I AM");
  delay(250);
  display.print("  A");
  delay(100);
  display.print("7SEG");
  delay(250);
  display.print(" And");
  delay(250);
  display.print(" You");
  delay(250);
  display.print(" Can");
  delay(250);
  display.print(" USE");
  delay(250);
  display.clear();
  delay(100);
  display.print("   A");
  delay(100);
  display.print("  Au");
  delay(100);
  display.print(" Aut");
  delay(100);
  display.print("Auto");
  delay(100);
  display.print("utoP");
  delay(100);
  display.print("toPL");
  delay(100);
  display.print("oPLE");
  delay(100);
  display.print("PLEX");
  delay(100);
  display.print("LEX7");
  delay(100);
  display.print("EX7 ");
  delay(100);
  display.print("X7  ");
  delay(100);
  display.print("7   ");
  delay(100);
  display.clear();
  delay(100);
  display.print(" to ");
  delay(250);
  display.print("ctrL.");
  delay(250);
  display.print(" ME ");
  delay(500);
  display.clear();
  delay(100);
}

void setup() {
  bool displayType = COMMON_CATHODE; // Change to COMMON_ANODE if using a common anode display
  byte displayDigits = 4; // The display has 4 digits
  byte digitPins[] = {1, 2, 3, 4}; // D1, D2, D3, D4
  byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12}; // A, B, C, D, E, F, G, DP

  display.begin(displayType, displayDigits, digitPins, segmentPins); // Initialize the display
  display.testDisplay(1000); // Show all digits, numbers, and decimals for one second

  hello();
  introduceAutoPlex7();
}

void loop() {
  // Render dots across the display
  display.print(" .   ");
  delay(250);
  display.print(" . .  ");
  delay(250);
  display.print(" . . . ");
  delay(250);
  display.print(" . . . .");
  delay(250);

  // Showcase numbers on the display
  display.showNumber(1234); // Display "1234"
  delay(1000); // Wait one second
  display.showNumber(2345); // Show the next number "2345"
  delay(100); // Wait a tenth of a second..
  display.showNumber(3456);
  delay(100);
  display.showNumber(4567);
  delay(100);
  display.showNumber(5678);
  delay(100);
  display.showNumber(6789);
  delay(100);
  display.showNumber(7890);
  delay(1000);
  display.clear();

  // Slide dashes across display
  display.print("   -");
  delay(250);
  display.print("  --");
  delay(250);
  display.print(" ---");
  delay(250);
  display.print("----");
  delay(250);
  display.print(" ---");
  delay(250);
  display.print("  --");
  delay(250);
  display.print("   -");
  delay(250);

  // Showcase the alphabetical display
  display.print("Abcd");
  delay(250);
  display.print("EFGH");
  delay(250);
  display.print("iJKL");
  delay(250);
  display.print("MnoP");
  delay(250);
  display.print("qrSt");
  delay(250);
  display.print("UvWX");
  delay(250);
  display.print(" YZ ");
  delay(500);
  
  display.clear(); // Clear the display
  delay(500);
}
