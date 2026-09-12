#include "AutoPlex7.h"

font systemFont[] = {
  { U'8', 0b1111111 }, // Display test
  END
};
font defaultFont[] = {
  { U' ', 0b0000000 }, // Space
  { U'0', 0b1111110 }, // Zero
  { U'1', 0b0110000 }, // One
  { U'2', 0b1101101 }, // Two
  { U'3', 0b1111001 }, // Three
  { U'4', 0b0110011 }, // Four
  { U'5', 0b1011011 }, // Five
  { U'6', 0b1011111 }, // Six
  { U'7', 0b1110000 }, // Seven
  { U'8', 0b1111111 }, // Eight
  { U'9', 0b1111011 }, // Nine
  { U'-', 0b0000001 }, // Hyphen
  { U'_', 0b0001000 }, // Underscore
  { U'=', 0b0001001 }, // Equals
  { U'|', 0b0000110 }, // Vertical pipe
  { U'*', 0b1100011 }, // Asterisk
  { U'/', 0b0100101 }, // Forward slash
  { U'>', 0b1111000 }, // Greater than
  { U'<', 0b1001110 }, // Less than
  { U'?', 0b1100101 }, // Question
  { U',', 0b0011000 }, // Comma
  { U'`', 0b1000000 }, // Backtick
  { U'^', 0b1100010 }, // Caret
  { U'(', 0b1001110 }, // Opening parenthesis
  { U')', 0b1111000 }, // Closing parenthesis
  { U'{', 0b0110001 }, // Opening curly brace
  { U'}', 0b0000111 }, // Closing curly brace
  { U'[', 0b1001110 }, // Opening square bracket
  { U']', 0b1111000 }, // Closing square bracket
  { U'~', 0b0100101 }, // Tilde
  { U'"', 0b0100010 }, // Double quotes
  { U'€', 0b1001111 }, // Euro
  { U'°', 0b1100011 }, // Degree
  { U'£', 0b1001111 }, // Pound
  { U'⁋', 0b1100111 }, // Paragraphus
  { U'A', 0b1110111 }, // Uppercase A
  { U'a', 0b1111101 }, // Lowercase a
  { U'B', 0b1111111 }, // Uppercase B
  { U'b', 0b0011111 }, // Lowercase b
  { U'C', 0b1001110 }, // Uppercase C
  { U'c', 0b0001101 }, // Lowercase c
  { U'D', 0b1111110 }, // Uppercase D
  { U'd', 0b0111101 }, // Lowercase d
  { U'E', 0b1001111 }, // Uppercase E
  { U'e', 0b1101111 }, // Lowercase e
  { U'F', 0b1000111 }, // Uppercase F
  { U'f', 0b1000111 }, // Lowercase f
  { U'G', 0b1011110 }, // Uppercase G
  { U'g', 0b1111011 }, // Lowercase g
  { U'H', 0b0110111 }, // Uppercase H
  { U'h', 0b0010111 }, // Lowercase h
  { U'I', 0b0000110 }, // Uppercase I
  { U'i', 0b1000100 }, // Lowercase i
  { U'J', 0b0111000 }, // Uppercase J
  { U'j', 0b0111100 }, // Lowercase j
  { U'K', 0b0110111 }, // Uppercase K
  { U'k', 0b0110111 }, // Lowercase k
  { U'L', 0b0001110 }, // Uppercase L
  { U'l', 0b0000110 }, // Lowercase l
  { U'M', 0b1010100 }, // Uppercase M
  { U'm', 0b1010100 }, // Lowercase m
  { U'N', 0b1110110 }, // Uppercase N
  { U'n', 0b0010101 }, // Lowercase n
  { U'O', 0b1111110 }, // Uppercase O
  { U'o', 0b0011101 }, // Lowercase o
  { U'P', 0b1100111 }, // Uppercase P
  { U'p', 0b1100111 }, // Lowercase p
  { U'Q', 0b1110011 }, // Uppercase Q
  { U'q', 0b1110011 }, // Lowercase q
  { U'R', 0b1110111 }, // Uppercase R
  { U'r', 0b0000101 }, // Lowercase r
  { U'S', 0b1011011 }, // Uppercase S
  { U's', 0b1011011 }, // Lowercase s
  { U'T', 0b0001111 }, // Uppercase T
  { U't', 0b0001111 }, // Lowercase t
  { U'U', 0b0111110 }, // Uppercase U
  { U'u', 0b0011100 }, // Lowercase u
  { U'V', 0b0111110 }, // Uppercase V
  { U'v', 0b0011100 }, // Lowercase v
  { U'W', 0b0011100 }, // Uppercase W
  { U'w', 0b0011100 }, // Lowercase w
  { U'X', 0b0110111 }, // Uppercase X
  { U'x', 0b0110111 }, // Lowercase x
  { U'Y', 0b0111011 }, // Uppercase Y
  { U'y', 0b0111011 }, // Lowercase y
  { U'Z', 0b1101101 }, // Uppercase Z
  { U'z', 0b1101101 }, // Lowercase z
  { U'×', 0b0110111 }, // Multiplication
  { U'μ', 0b0100111 }, // Mu
  { U'µ', 0b0100111 }, // Micro
  END
};

uint8_t _displayIndex = 0; // The array index of the last display instance

size_t AutoPlex7::strlen32(const char32_t* string) { // A helper function - used internally - for determining the length of a 32-bit character array
  size_t len = 0;
  for (uint8_t i = 0; string[i] != U'\0'; i++) { len++; }
  return len;
}
char32_t* AutoPlex7::strcpy32(char32_t* dest, const char32_t* src) { // Used internally to copy a 32-bit char array into another
  char32_t* original = dest;
  while ((*dest++ = *src++) != U'\0');
  return original;
}
char32_t* AutoPlex7::strcpy8to32(char32_t* dest, const char* src) { // Used internally to copy an 8 bit string into a 32 bit string
  char32_t* original = dest;
  uint8_t endIndex = 0;
  for (uint8_t i = 0; src[i] != '\0'; i++) {
    dest[i] = (char32_t)src[i];
    endIndex++;
  }
  dest[endIndex] = U'\0';
  return original;
}
size_t AutoPlex7::filterDecimals(const char32_t* string) { // Used internally to count how many non-decimal characters are in a wide character array
  size_t count = 0;
  for (uint8_t i = 0; i < strlen32(string); i++) {
    if (string[i] != U'.') { count++; }
  }
  return count;
}
size_t AutoPlex7::filterDecimals(const char* string) { // Used internally to count how many non-decimal characters are in a character array
  size_t count = 0;
  for (uint8_t i = 0; i < strlen(string); i++) {
    if (string[i] != '.') { count++; }
  }
  return count;
}
void AutoPlex7::wipeDisplay() { // Used internally to turn the display off without clearing the buffer
  for (uint8_t i = 0; i < digitsClass; i++) { fastWrite(digitPinsClass[i], digitOff); }
  for (uint8_t i = 0; i < 8; i++) { fastWrite(segmentPinsClass[i], segmentOff); }
}
bool AutoPlex7::begin(uint8_t displayType, uint8_t digits, uint8_t digitPins[], uint8_t segmentPins[], bool multiplexing) { // Initializes the display; returns true if successful
  if (digits > MAX_DIGITS || digits < 1) { return false; } // Validate arguments
  for (uint8_t i = 0; i < digits; i++) { if (digitalPinToPort(digitPins[i]) == NOT_A_PIN) { return false; } } // Validate digit pins
  for (uint8_t i = 0; i < 8; i++) { if (digitalPinToPort(segmentPins[i]) == NOT_A_PIN) { return false; } } // Validate segment pins
  // Decide based on the type of display what "on" represents
  switch (displayType) {
    case COMMON_ANODE: segmentOn = LOW; digitOn = HIGH; break;
    case COMMON_CATHODE: segmentOn = HIGH; digitOn = LOW; break;
    case CAWDDT: segmentOn = LOW; digitOn = LOW; break;
    case CCWDDT: segmentOn = HIGH; digitOn = HIGH; break;
    default: return false; break;
  }
  // Define "off" as the inverse of "on"
  segmentOff = !segmentOn;
  digitOff = !digitOn;

  digitsClass = digits; // Store the number of digits on the display inside the class
  for (uint8_t i = 0; i < digitsClass; i++) { digitPinsClass[i] = digitPins[i]; } // Save digit pins to the class
  for (uint8_t i = 0; i < 8; i++) { segmentPinsClass[i] = segmentPins[i]; } // Save segment pins to class

  // Configure display pins as outputs
  for (uint8_t i = 0; i < digitsClass; i++) { pinMode(digitPinsClass[i], OUTPUT); }
  for (uint8_t i = 0; i < 8; i++) { pinMode(segmentPinsClass[i], OUTPUT); }

  if (multiplexing == AUTOPLEX) { // Check if multiplexing should be performed automatically
    // If so, and too many displays have already been registered, that's an error
    if (_displayIndex >= MAX_DISPLAYS) {
      return false;
    }
    manualplexing = false;
    noInterrupts();
    displays[_displayIndex++] = this; // Register new display instance
    if (!timerConfigured) { // If it hasn't already been set up, configure Timer0 for automatic multiplexing
      OCR0A = 0xAF;
      TIMSK0 |= _BV(OCIE0A);
      timerConfigured = true;
    }
    interrupts();
  }else{
    manualplexing = true;
  }

  clear(); // Ensure display is blank
  return true;
}
void AutoPlex7::clear() { // Empty the display buffer and deactivate all digits and segments
  noInterrupts();
  buffer[0] = U'\0';
  displayPos = 0; bufferPos = 0;
  wipeDisplay();
  interrupts();
}
void AutoPlex7::setFont(font* newFont) {
  noInterrupts();
  currentFont = newFont;
  interrupts();
}
void AutoPlex7::print(const char32_t* text) { // Shows a string on the display; works with any Unicode character the selected font defines
  noInterrupts();
  if (filterDecimals(text) > digitsClass) { // If new string does NOT fit on the display...
    // Show dashes instead
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
  }else{
    strcpy32(buffer, text); // Else copy the new string into the buffer for display contents
  }
  interrupts();
}
void AutoPlex7::print(const char* text) { // Shows a string on the display; only works with ASCII characters
  noInterrupts();
  if (filterDecimals(text) > digitsClass) { // If new string does NOT fit on the display...
    // Show dashes
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
  }else{
    strcpy8to32(buffer, text); // Else paste the new contents into the buffer
  }
  interrupts();
}
void AutoPlex7::print(int num) { // Set the seven segment display's buffer to an integer
  char temporary[11];
  itoa(num, temporary, 10);
  noInterrupts();
  if (strlen(temporary) > digitsClass) { // If number is too large to fit on the display...
    // Print dashes instead
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
  }else{
    strcpy8to32(buffer, temporary); // Else, paste the number into the display buffer
  }
  interrupts();
}
void AutoPlex7::print(double num) { // Set the seven segment display's buffer to a double/float
  int32_t numInt = num; // Truncate the float into an integer
  char numIntString[11]; itoa(numInt, numIntString, 10); // Create a string containing the input as an integer
  uint16_t decimalPlaces = digitsClass - strlen(numIntString); // Calculate how many decimal places can fit on the display
  char temporary[11]; dtostrf(num, 0, decimalPlaces, temporary); // Create a string for the display
  noInterrupts();
  if (filterDecimals(temporary) > digitsClass) { // If the new number is too large for the display...
    // Show dashes
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
  }else{
    strcpy8to32(buffer, temporary); // Copy the number into the display buffer
  }
  interrupts();
}
void AutoPlex7::print(double num, uint8_t decimalPlaces) { // Set the seven segment display's buffer to a double/float, with a fixed number of digits after the decimal point
  char temporary[11];
  dtostrf(num, 0, decimalPlaces, temporary);
  noInterrupts();
  if (filterDecimals(temporary) > digitsClass) { // If number too large for display...
    // Show dashes
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
  }else{
    strcpy8to32(buffer, temporary); // Copy the new number into the buffer
  }
  interrupts();
}
void AutoPlex7::append(const char32_t* text) { // Add a 32-bit string suffix to the current display contents
  noInterrupts();
  if (filterDecimals(buffer) + filterDecimals(text) > digitsClass) { // If the current display contents + new contents is longer than the display...
    // Show dashes instead
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
    interrupts();
    return;
  }
  uint8_t i = 0;
  while (buffer[i] != U'\0') { i++; } // Find the number of indexes before termination
  for (uint8_t u = 0; text[u] != U'\0'; u++) { // Add the suffix
    buffer[i++] = text[u];
  }
  buffer[i] = U'\0'; // Terminate string
  interrupts();
}
void AutoPlex7::append(const char* text) { // Add an ASCII string suffix to the current display contents
  noInterrupts();
  if (filterDecimals(buffer) + filterDecimals(text) > digitsClass) { // If the current display contents + new contents is longer than the display...
    // Show dashes instead
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
    interrupts();
    return;
  }
  uint8_t i = 0;
  while (buffer[i] != U'\0') { i++; } // Find the number of indexes before termination
  for (uint8_t u = 0; text[u] != U'\0'; u++) { // Add the suffix
    buffer[i++] = (char32_t)text[u];
  }
  buffer[i] = U'\0'; // Terminate string
  interrupts();
}
void AutoPlex7::append(int num) { // Add an integer suffix to the current display contents
  char string8[11];
  itoa(num, string8, 10);
  char32_t string32[11];
  strcpy8to32(string32, string8);
  noInterrupts();
  if (filterDecimals(buffer) + strlen32(string32) > digitsClass) { // If the current display contents + new contents is longer than the display...
    // Show dashes instead
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
    interrupts();
    return;
  }
  uint8_t i = 0;
  while (buffer[i] != U'\0') { i++; } // Find the number of indexes before termination
  for (uint8_t u = 0; string32[u] != U'\0'; u++) { // Add the suffix
    buffer[i++] = string32[u];
  }
  buffer[i] = U'\0'; // Terminate string
  interrupts();
}
void AutoPlex7::append(double num, uint8_t decimalPlaces) { // Add a double suffix to the current display contents
  char string8[11];
  dtostrf(num, 0, decimalPlaces, string8);
  char32_t string32[11];
  strcpy8to32(string32, string8);

  noInterrupts();
  if (filterDecimals(buffer) + filterDecimals(string32) > digitsClass) { // If the current display contents + new contents is longer than the display...
    // Show dashes instead
    uint8_t position = 0;
    for (uint8_t i = 0; i < digitsClass; i++) {
      buffer[position++] = U'-';
    }
    buffer[position] = U'\0'; // Terminate string
    interrupts();
    return;
  }
  uint8_t i = 0;
  while (buffer[i] != U'\0') { i++; } // Find the number of indexes before termination
  for (uint8_t u = 0; string32[u] != U'\0'; u++) { // Add the suffix
    buffer[i++] = string32[u];
  }
  buffer[i] = U'\0'; // Terminate string
  interrupts();
}
void AutoPlex7::testDisplay(unsigned long ms) {
  uint8_t position = 0;
  font* lastFont = currentFont;
  noInterrupts();
  currentFont = systemFont;
  for (uint8_t i = 0; i < digitsClass; i++) {
    buffer[position++] = U'8'; // Light all seven segments...
    buffer[position++] = U'.'; // ... and the decimal point
  }
  buffer[position] = U'\0';
  interrupts();
  unsigned long testStart = millis();
  unsigned long lastPlex = millis();
  while (millis() - testStart < ms) { if (manualplexing && millis() - lastPlex >= 1) { lastPlex = millis(); multiplex(); } }
  noInterrupts();
  currentFont = lastFont;
  buffer[0] = U'\0';
  interrupts();
}
void AutoPlex7::multiplex() { // Render the buffer onto the screen
  wipeDisplay();
  if (buffer[0] == U'\0') { // If string empty...
    return; // Do nothing else, return
  }
  if (strlen32(buffer) <= bufferPos) { displayPos = 0; bufferPos = 0; } // If all characters in the buffer have been rendered, cycle back to the first
  if (buffer[bufferPos] == U'.') { bufferPos++; } // If the current character is a decimal, simply move on to the next
  uint8_t digitPos = (displayPos + (digitsClass - filterDecimals(buffer)));
  fastWrite(digitPinsClass[digitPos], digitOn); // Right align the text on the display
  for (uint8_t i = 0; i < digitsClass; i++) { if (i != (digitPos)) { fastWrite(digitPinsClass[i], digitOff); } } // Turn off all digits besides the current one
  if (strlen32(buffer) > bufferPos && buffer[bufferPos + 1] == U'.') { fastWrite(segmentPinsClass[7], segmentOn); } // Turn on this digit's DP if the next character is a decimal

  bool charFound = false; // A boolean flag that tracks whether the requested character has been found in the selected font
  bool qmarkFound = false; // A boolean flag that tracks whether a '?' has been found in the selected font. This is displayed if charFound == false
  uint16_t bitmap = 0b0000000; // Stores the bitmap for the desired character
  uint16_t qmark_btmp = 0b0000000; // Stores the bitmap for an unknown character / question mark

  for (uint16_t i = 0; currentFont[i].identifier != 0; i++) { // Search through the font for the desired character
    if (currentFont[i].identifier == U'?') { qmarkFound = true; qmark_btmp = currentFont[i].bitmap; } // Save the question mark bitmap, if found
    if (currentFont[i].identifier == buffer[bufferPos]) { charFound = true; bitmap = currentFont[i].bitmap; break; } // If the requsted character is found, save it and stop searching
  }

  if (!charFound) { // If the requested character could not be located in the current font...
    if (qmarkFound) { // Check if a question mark is available
      bitmap = qmark_btmp; // If so, log this as the bitmap for display
    }else{
      bitmap = 0b0000000; // Else, do not display anything
    }
  }

  // Read the bitmap and write to the segments
  for (int8_t i = 6; i >= 0; i--) {
    fastWrite(segmentPinsClass[6 - i], bitRead(bitmap, i) ? segmentOn : segmentOff);
  }

  displayPos++; bufferPos++; // Move on to the next character when the next call occurs
}

AutoPlex7* AutoPlex7::displays[MAX_DISPLAYS] = { nullptr };
bool AutoPlex7::timerConfigured = false;

ISR(TIMER0_COMPA_vect) {
  for (uint8_t i = 0; i < _displayIndex; i++) {
    AutoPlex7::displays[i]->multiplex();
  }
}
