#ifndef AUTOPLEX7_H
#define AUTOPLEX7_H

#include <Arduino.h>

#define COMMON_CATHODE 1
#define COMMON_ANODE 0
#define DISPLAY_REFRESH TIMER1_COMPA_vect
#define MAX_DIGITS 8 // Defines the maximum number of digits the library can support. You may increase this if you plan to use larger displays, at the cost of more memory usage

class AutoPlex7 {
private:
    uint8_t digitsClass, digitPinsClass[MAX_DIGITS], segmentPinsClass[8];
    uint8_t A, B, C, D, E, F, G, DP;
    bool segmentOn, segmentOff;
    bool digitOn, digitOff;
    volatile uint8_t currentDigit = 0; // The character within the buffer which the multiplexing logic is currently on
    volatile uint8_t displayPosition = 0; // The physical position of the current character on the display
    char buffer[(MAX_DIGITS * 2) + 1] = ""; // Buffer to hold the contents of the display. Enough space for MAX_DIGITS characters, decimal points, and a null termination
    size_t filterDecimals(const char* string);
    void wipeDisplay();
public:
    void begin(bool displayType, uint8_t digits, uint8_t digitPins[], uint8_t segmentPins[]);
    void testDisplay(unsigned long ms);
    void multiplex();
    void append(const char* text);
    void clear();
    void showNumber(int32_t num);
    void showNumberF(double num, uint8_t decimalPlaces);
    void print(const char* text);
};

#endif
