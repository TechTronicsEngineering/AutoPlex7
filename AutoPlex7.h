#ifndef AUTOPLEX7_H
#define AUTOPLEX7_H

#include <Arduino.h>

#define COMMON_ANODE 0
#define COMMON_CATHODE 1
#define CAWDDT 2 // Common Anode With Digit Drive Transistors
#define CCWDDT 3 // Common Cathode With Digit Drive Transistors
#define DISPLAY_REFRESH TIMER1_COMPA_vect
#define MAX_DIGITS 8 // Defines the maximum number of digits the library can support per display. You may increase this if you plan to use larger displays, at the cost of more memory usage
#define MAX_DISPLAYS 8 // Defines the maximum number of total individual displays the library can control simultaneously. May be increased at the price of more memory usage
#define AUTOPLEX 1 // Automatic interrupt-based multiplexing
#define MANUALPLEX 0 // Manual multiplexing flag

extern uint8_t _displayIndex;
class AutoPlex7 {
private:
    uint8_t digitsClass, digitPinsClass[MAX_DIGITS], segmentPinsClass[8];
    uint8_t A, B, C, D, E, F, G, DP;
    bool segmentOn, segmentOff;
    bool digitOn, digitOff;
    volatile uint8_t currentDigit = 0; // The character within the buffer which the multiplexing logic is currently on
    volatile uint8_t displayPosition = 0; // The physical position of the current character on the display
    char buffer[(MAX_DIGITS * 2) + 1] = ""; // Buffer to hold the contents of the display. Enough space for MAX_DIGITS characters, decimal points, and a null termination
    bool manualPlexing = false;
    size_t filterDecimals(const char* string);
    void wipeDisplay();
public:
    static AutoPlex7* displays[MAX_DISPLAYS];
    void begin(uint8_t displayType, uint8_t digits, uint8_t digitPins[], uint8_t segmentPins[], bool multiplexing = AUTOPLEX);
    void testDisplay(unsigned long ms = 0);
    void multiplex();
    void append(const char* text);
    void append(int32_t num);
    void append(double num, uint8_t decimalPlaces);
    void clear();
    void showNumber(int32_t num);
    void showNumberF(double num, uint8_t decimalPlaces);
    void print(const char* text);
    void print(int32_t num);
    void print(double num, uint8_t decimalPlaces);
};

#endif
