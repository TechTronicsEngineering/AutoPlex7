#include "AutoPlex7.h"

void Display::blankSegments() {
    digitalWrite(A, OFF); digitalWrite(B, OFF); digitalWrite(C, OFF);
    digitalWrite(D, OFF); digitalWrite(E, OFF); digitalWrite(F, OFF);
    digitalWrite(G, OFF); digitalWrite(DP, OFF);
}

void Display::activateDigit(int digitIndex){
    digitalWrite(D1, digitIndex==0?OFF:ON);
    digitalWrite(D2, digitIndex==1?OFF:ON);
    digitalWrite(D3, digitIndex==2?OFF:ON);
    digitalWrite(D4, digitIndex==3?OFF:ON);
}

void Display::showDigitSegments(int val){
    switch(val){
        case 0: digitalWrite(A,ON); digitalWrite(B,ON); digitalWrite(C,ON); digitalWrite(D,ON); digitalWrite(E,ON); digitalWrite(F,ON); digitalWrite(G,OFF); break;
        case 1: digitalWrite(A,OFF); digitalWrite(B,ON); digitalWrite(C,ON); digitalWrite(D,OFF); digitalWrite(E,OFF); digitalWrite(F,OFF); digitalWrite(G,OFF); break;
        case 2: digitalWrite(A,ON); digitalWrite(B,ON); digitalWrite(C,OFF); digitalWrite(D,ON); digitalWrite(E,ON); digitalWrite(F,OFF); digitalWrite(G,ON); break;
        case 3: digitalWrite(A,ON); digitalWrite(B,ON); digitalWrite(C,ON); digitalWrite(D,ON); digitalWrite(E,OFF); digitalWrite(F,OFF); digitalWrite(G,ON); break;
        case 4: digitalWrite(A,OFF); digitalWrite(B,ON); digitalWrite(C,ON); digitalWrite(D,OFF); digitalWrite(E,OFF); digitalWrite(F,ON); digitalWrite(G,ON); break;
        case 5: digitalWrite(A,ON); digitalWrite(B,OFF); digitalWrite(C,ON); digitalWrite(D,ON); digitalWrite(E,OFF); digitalWrite(F,ON); digitalWrite(G,ON); break;
        case 6: digitalWrite(A,ON); digitalWrite(B,OFF); digitalWrite(C,ON); digitalWrite(D,ON); digitalWrite(E,ON); digitalWrite(F,ON); digitalWrite(G,ON); break;
        case 7: digitalWrite(A,ON); digitalWrite(B,ON); digitalWrite(C,ON); digitalWrite(D,OFF); digitalWrite(E,OFF); digitalWrite(F,OFF); digitalWrite(G,OFF); break;
        case 8: digitalWrite(A,ON); digitalWrite(B,ON); digitalWrite(C,ON); digitalWrite(D,ON); digitalWrite(E,ON); digitalWrite(F,ON); digitalWrite(G,ON); break;
        case 9: digitalWrite(A,ON); digitalWrite(B,ON); digitalWrite(C,ON); digitalWrite(D,ON); digitalWrite(E,OFF); digitalWrite(F,ON); digitalWrite(G,ON); break;
    }
}

void Display::begin(){
    int pins[] = {D1,D2,D3,D4,A,B,C,D,E,F,G,DP};
    for(int i=0;i<12;i++) pinMode(pins[i], OUTPUT);
    clearDisplay();

    // Set up Timer2 for ~1kHz multiplexing
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2  = 0;
    OCR2A = 249;               // 16MHz/(64*1000Hz)-1
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22);     // prescaler 64
    TIMSK2 |= (1 << OCIE2A);   // enable compare match interrupt
    sei();                      // enable global interrupts
}

void Display::blankDigit(){ blankSegments(); }

void Display::clearDisplay(){
    for(int i=0;i<4;i++){ digitsToDisplay[i]=-1; decimalFlags[i]=false; }
    blankSegments();
    digitalWrite(D1,OFF); digitalWrite(D2,OFF); digitalWrite(D3,OFF); digitalWrite(D4,OFF);
}

void Display::showDecimal(){ decimalFlags[currentDigit]=true; }
void Display::clearDecimal(){ decimalFlags[currentDigit]=false; }

void Display::testDisplay(){
    for(int i=0;i<4;i++){ digitsToDisplay[i]=8; decimalFlags[i]=true; }
}

void Display::showNumber(int num){
    int tmp[4];
    tmp[0] = (num/1000)%10; tmp[1] = (num/100)%10;
    tmp[2] = (num/10)%10; tmp[3] = num%10;

    bool nonZero=false;
    for(int i=0;i<4;i++){
        if(tmp[i]!=0 || nonZero || i==3){ digitsToDisplay[i]=tmp[i]; nonZero=true; }
        else digitsToDisplay[i]=-1;
    }
}

void Display::setDigit(int number){ currentDigit = number>3?0:number; }

void Display::multiplexStep(){
    blankSegments();
    activateDigit(currentDigit);

    int val = digitsToDisplay[currentDigit];
    if(val != -1) showDigitSegments(val);
    digitalWrite(DP, decimalFlags[currentDigit]?ON:OFF);

    currentDigit++;
    if(currentDigit>3) currentDigit=0;
}

Display display;

ISR(TIMER2_COMPA_vect){
    display.multiplexStep();
}
