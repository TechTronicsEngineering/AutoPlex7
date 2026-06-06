#include "AutoPlex7.h"

void AutoPlex7::begin(bool displayType, uint8_t digits, uint8_t digitPins[], uint8_t segmentPins[]) {
    // Decide based on the type of display what "on" represents
    switch (displayType) {
      case COMMON_ANODE: segmentOn = LOW; digitOn = HIGH; break;
      case COMMON_CATHODE: segmentOn = HIGH; digitOn = LOW; break;
    }
    // Define "off" as the inverse of "on"
    segmentOff = !segmentOn;
    digitOff = !digitOn;
    digitsClass = digits; // Store the number of digits on the display, inside the class
    // Store display pinout within the class
    for (uint8_t i = 0; i < digitsClass; i++) { digitPinsClass[i] = digitPins[i]; }
    for (uint8_t i = 0; i < 8; i++) { segmentPinsClass[i] = segmentPins[i]; }

    // Get segments from the pin array
    A = segmentPinsClass[0];
    B = segmentPinsClass[1];
    C = segmentPinsClass[2];
    D = segmentPinsClass[3];
    E = segmentPinsClass[4];
    F = segmentPinsClass[5];
    G = segmentPinsClass[6];
    DP = segmentPinsClass[7];

    // Configure timer1 for multiplexing at 1kHz
    cli();
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    OCR1A = 249;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    sei();

    // Configure display pins as outputs
    for (uint8_t i = 0; i < digitsClass; i++) { pinMode(digitPinsClass[i], OUTPUT); }
    for (uint8_t i = 0; i < 8; i++) { pinMode(segmentPinsClass[i], OUTPUT); }

    clear(); // Ensure display is blank
}

size_t AutoPlex7::filterDecimals(const char* string) { // Used internally to count how many non-decimal characters are in a character array
    size_t count = 0;
    for (uint8_t i = 0; i < strlen(string); i++) {
      if (string[i] != '.') count++;
    }
    return count;
}
void AutoPlex7::wipeDisplay() { // Used internally to turn the display off without clearing the buffer
    for (uint8_t i = 0; i < digitsClass; i++) { digitalWrite(digitPinsClass[i], digitOff); }
    for (uint8_t i = 0; i < 8; i++) { digitalWrite(segmentPinsClass[i], segmentOff); }
}

void AutoPlex7::showNumber(int32_t num) { // Set the seven segment display's buffer to an integer
      noInterrupts();
      char temporary[12];
      itoa(num, temporary, 10);
      if (strlen(temporary) > MAX_DIGITS) { buffer[0] = '\0'; } else { itoa(num, buffer, 10); }
      interrupts();
    }
    void AutoPlex7::showNumberF(double num, uint8_t decimalPlaces) { // Set the seven segment display's buffer to a double/float
      noInterrupts();
      dtostrf(num, 0, decimalPlaces, buffer);
      interrupts();
    }
    void AutoPlex7::print(const char* text) { // Set the seven segment display's buffer to a string
      noInterrupts();
      if (strlen(text) > MAX_DIGITS) { buffer[0] = '\0'; } else { strcpy(buffer, text); }
      interrupts();
    }
    void AutoPlex7::testDisplay(unsigned long ms) { // Segment test
      print("8.8.8.8.8.8.8.8.");
      delay(ms);
    }
    void AutoPlex7::clear() { // Empty the display buffer and deactivate all digits and segments
      buffer[0] = '\0';
      wipeDisplay();
    }

void AutoPlex7::multiplex() { // Render the buffer onto the screen
      static uint8_t currentDigit = 0; // The character within the buffer which the multiplexing logic is currently on
      static uint8_t displayPosition = 0; // The physical position of the current character on the display
      if (buffer[0] == '\0') { // If string empty...
        wipeDisplay(); // Disable all digits and segments on the display
        return; // Do nothing else, return
      }
      if (currentDigit >= strlen(buffer)) { currentDigit = 0; displayPosition = 0; } // Return to the start of the string when the end is reached
      wipeDisplay(); // Ensure display is blank before rendering a character
      if (buffer[currentDigit] == '.') { currentDigit++; return; } // If current character is a decimal, move on
      digitalWrite(digitPinsClass[(displayPosition + (digitsClass - filterDecimals(buffer)))], digitOn); // Right align the text on the display
      for(uint8_t i = 0; i < digitsClass; i++){if(i != (displayPosition + (digitsClass - filterDecimals(buffer)))){digitalWrite(digitPinsClass[i], digitOff);}}
      switch(buffer[currentDigit]) { // Render the current character
        case '0': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case '1': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case '2': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case '3': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case '4': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case '5': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case '6': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case '7': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case '8': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case '9': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case '-': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case '_': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case '/': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case '|': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case '(': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case ')': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case '[': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case ']': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case '{': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case '}': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case '^': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case '*': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case '?': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case '=': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case ',': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case 'A': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'a': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case 'B': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'b': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'C': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'c': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case 'D': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'd': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case 'E': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'e': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'F': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'f': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'G': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'g': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'H': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'h': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'I': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'i': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case 'J': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case 'j': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case 'K': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'k': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'L': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'l': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'M': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case 'm': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case 'N': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'n': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case 'O': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'o': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case 'P': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'p': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'Q': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'q': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'R': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'r': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case 'S': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 's': digitalWrite(A, segmentOn); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'T': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 't': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'U': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'u': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case 'V': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'v': digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
        case 'W': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'w': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOff); break;
        case 'X': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'x': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOff); digitalWrite(E, segmentOn); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'Y': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'y': digitalWrite(A, segmentOff); digitalWrite(B, segmentOn); digitalWrite(C, segmentOn); digitalWrite(D, segmentOn); digitalWrite(E, segmentOff); digitalWrite(F, segmentOn); digitalWrite(G, segmentOn); break;
        case 'Z': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        case 'z': digitalWrite(A, segmentOn); digitalWrite(B, segmentOn); digitalWrite(C, segmentOff); digitalWrite(D, segmentOn); digitalWrite(E, segmentOn); digitalWrite(F, segmentOff); digitalWrite(G, segmentOn); break;
        default: digitalWrite(A, segmentOff); digitalWrite(B, segmentOff); digitalWrite(C, segmentOff); digitalWrite(D, segmentOff); digitalWrite(E, segmentOff); digitalWrite(F, segmentOff); digitalWrite(G, segmentOff); break;
      }
      if (currentDigit + 1 < strlen(buffer) && buffer[currentDigit + 1] == '.') { digitalWrite(DP, segmentOn); } // If next character is a decimal, activate the DP on this digit
      displayPosition++; // Increase the counter that corresponds to physical display position
      if (currentDigit <= strlen(buffer)) { currentDigit++; } // Move on to the next digit when the next cycle is reached
    }
