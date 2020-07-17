#include "Arduino.h"
#include "VFD.h"
/*
Create instance of display, arguments:
2) number of segment pins
3) array of segment pins, first 7 in conventional order (A-F) for number segments if numbers wanted
*   A
* F   B
*   G
* E   C
*   D 
4) number of grid pins
5) array of grid pins, rightmost digit first
*/
VFD::VFD(const int numSegPins, const int * segPins,const int numGridPins, const int * gridPins)
{
  _numSegPins = numSegPins;
  _segPins = segPins;
  _numGridPins = numGridPins;
  _gridPins = gridPins;
  for(int i = 0; i<_numSegPins; i++) {
    pinMode(_segPins[i],OUTPUT);
  }
  for(int i = 0; i<_numGridPins; i++) {
    pinMode(_gridPins[i],OUTPUT);
  }
  off(0);
}

void VFD::segment(int g, int s) {
    digitalWrite(_gridPins[g], LOW);
    digitalWrite(_segPins[s], LOW);
}

void VFD::segment(int g, int s, int duration) {
  off(0);
  digitalWrite(_gridPins[g], LOW);
  digitalWrite(_segPins[s], LOW);
  delay(duration);
  digitalWrite(_gridPins[g], HIGH);
  digitalWrite(_segPins[s], HIGH);
}

void VFD::blink(int duration) {
  on(duration);
  off(duration);
}

void VFD::on(int duration)
{
  int multiplexDuration = 3;
  for(int j = 0; j<duration / (multiplexDuration * _numGridPins); j++) {
    for (int i = 0; i < _numGridPins; i++) {
      for (int k = 0; k < _numSegPins; k++) {
        segment(i, k);
      }
      delay(multiplexDuration);
      off(0);
    } 
  } 
}

void VFD::off(int duration)
{
  for (int i = 0; i < _numSegPins; i++) {
    digitalWrite(_segPins[i], HIGH);
  }
  for (int i = 0; i < _numGridPins; i++) {
    digitalWrite(_gridPins[i], HIGH);
  } 
  delay(duration);
}

void VFD::number(int g, int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(_segPins[i], numbers[num][i]);
  }
  for (int j = 0; j < _numGridPins; j++) {
    if (j == d) {
      digitalWrite(_gridPins[j], LOW);
    } else {
      digitalWrite(_gridPins[j], HIGH);
    }
  }
  delay(5);
}

void VFD::multiDigitNumber(int num) {
  char onesChar, tensChar, hundredsChar, thousandsChar, tenThousandsChar;
  int ones, tens, hundreds, thousands, tenThousands;
  String numStr = String(num);

  if (num < 10) {
    onesChar = numStr[0];
    ones = int(onesChar - '0');
    number(0, ones);
  } else if(num >=10 && num < 100) {
    onesChar = numStr[1];
    tensChar = numStr[0];
    ones = int(onesChar - '0');
    tens = int(tensChar - '0');
    number(0, ones);
    number(1, tens);
  } else if(num >=100 && num < 1000) {
    onesChar = numStr[2];
    tensChar = numStr[1];
    hundredsChar = numStr[0];
    ones = int(onesChar - '0');
    tens = int(tensChar - '0');
    hundreds = int(hundredsChar - '0');
    number(0, ones);
    number(1, tens);
    number(2, hundreds);
  } else if(num >= 1000 && num < 10000) {
    onesChar = numStr[3];
    tensChar = numStr[2];
    hundredsChar = numStr[1];
    thousandsChar = numStr[0];
    ones = int(onesChar - '0');
    tens = int(tensChar - '0');
    hundreds = int(hundredsChar - '0');
    thousands = int(thousandsChar - '0');
    number(0, ones);
    number(1, tens);
    number(2, hundreds);
    number(3, thousands);
  } else {
    onesChar = numStr[4];
    tensChar = numStr[3];
    hundredsChar = numStr[2];
    thousandsChar = numStr[1];
    tenThousandsChar = numStr[0];
    ones = int(onesChar - '0');
    tens = int(tensChar - '0');
    hundreds = int(hundredsChar - '0');
    thousands = int(thousandsChar - '0');
    tenThousands = int(tenThousandsChar - '0');
    number(0, ones);
    number(1, tens);
    number(2, hundreds);
    number(3, thousands);
    number(4, tenThousands);  
  }
}

void VFD::crazyEights(int speed) {
  int segs[] = {0, 1, 6, 4, 3, 2, 6, 5};
  for (int i = 0; i < sizeof(segs)/sizeof(segs[0]); i++) {
    for(int j = 0; j < _numGridPins; j++) {
      segment(j, segs[i]);
    }
    delay(speed);
    off(1);   
  }
}
