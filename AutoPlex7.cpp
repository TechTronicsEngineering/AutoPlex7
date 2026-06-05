#include "AutoPlex7.h"

void AutoPlex7::begin(bool displayType, uint8_t digits, uint8_t digitPins[], uint8_t segmentPins[]) {
    switch (displayType) {
      case COMMON_ANODE: segmentOn = LOW; digitOn = HIGH; break;
      case COMMON_CATHODE: segmentOn = HIGH; digitOn = LOW; break;
    }
    segmentOff = !segmentOn;
    digitOff = !digitOn;
    digitsClass = digits;
    for (uint8_t i = 0; i < digitsClass; i++) { digitPinsClass[i] = digitPins[i]; }
    for (uint8_t i = 0; i < 8; i++) { segmentPinsClass[i] = segmentPins[i]; }

    A = segmentPinsClass[0];
    B = segmentPinsClass[1];
    C = segmentPinsClass[2];
    D = segmentPinsClass[3];
    E = segmentPinsClass[4];
    F = segmentPinsClass[5];
    G = segmentPinsClass[6];
    DP = segmentPinsClass[7];

    cli();
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    OCR1A = 249;                         // 16MHz/(64*1000Hz)-1
    TCCR1B |= (1 << WGM12);              // CTC mode
    TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler 64
    TIMSK1 |= (1 << OCIE1A);             // enable compare match A interrupt
    sei();                               // enable global interrupts
      
    for (uint8_t i = 0; i < digitsClass; i++) { pinMode(digitPinsClass[i], OUTPUT); }
    for (uint8_t i = 0; i < 8; i++) { pinMode(segmentPinsClass[i], OUTPUT); }

    clear();
}

size_t AutoPlex7::filterDecimals(const char* string) {
    size_t count = 0;
    for (uint8_t i = 0; i < strlen(string); i++) {
      if (string[i] != '.') count++;
    }
    return count;
}
void AutoPlex7::wipeDisplay() {
    for (uint8_t i = 0; i < digitsClass; i++) { digitalWrite(digitPinsClass[i], digitOff); }
    for (uint8_t i = 0; i < 8; i++) { digitalWrite(segmentPinsClass[i], segmentOff); }
}

void AutoPlex7::showNumber(int32_t num) {
      noInterrupts();
      char temporary[12];
      itoa(num, temporary, 10);
      if (strlen(temporary) > MAX_DIGITS) { buffer[0] = '\0'; } else { itoa(num, buffer, 10); }
      interrupts();
    }
    void AutoPlex7::showNumberF(double num, uint8_t decimalPlaces) {
      noInterrupts();
      dtostrf(num, 0, decimalPlaces, buffer);
      interrupts();
    }
    void AutoPlex7::print(const char* text) {
      noInterrupts();
      if (strlen(text) > MAX_DIGITS) { buffer[0] = '\0'; } else { strcpy(buffer, text); }
      interrupts();
    }
    void AutoPlex7::testDisplay(unsigned long ms) {
      print("8.8.8.8.");
      delay(ms);
    }
    void AutoPlex7::clear() {
      buffer[0] = '\0';
      wipeDisplay();
    }

void AutoPlex::multiplex() {
      static uint8_t currentDigit = 0;
      static uint8_t displayPosition = 0;
      if (buffer[0] == '\0') {
        wipeDisplay();
        return;
      }
      if (currentDigit >= strlen(buffer)) { currentDigit = 0; displayPosition = 0; }
      wipeDisplay();
      if (buffer[currentDigit] == '.') { currentDigit++; return; }
      digitalWrite(digitPinsClass[(displayPosition + (digitsClass - filterDecimals(buffer)))], digitOn);
      for(uint8_t i = 0; i < digitsClass; i ++){if(i != (displayPosition + (digitsClass - filterDecimals(buffer)))){digitalWrite(digitPinsClass[i], digitOff);}}
      switch(buffer[currentDigit]) {
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
      if (currentDigit + 1 < strlen(buffer) && buffer[currentDigit + 1] == '.') { digitalWrite(DP, segmentOn); }
      displayPosition++;
      if (currentDigit <= strlen(buffer)) { currentDigit++; }
    }
