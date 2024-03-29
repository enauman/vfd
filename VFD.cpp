#include "Arduino.h"
#include "VFD.h"
/*
Create instance of display, arguments:
1) number of segment pins
2) array of segment pins, first 7 or 9 (see documentation) in conventional order (A-G) or (A-I) 
 for number segments if numbers wanted:
*   A
* F   B
*   G
* E   C
*   D 
*********
*   A
* F   B
*  GHI
* E   C
*   D 
*********
* With star-type digit (15 segment) you can use letter, message, and scrollingMessage
* functions, order segment pin array in this order:
*   A
* FJKLB
*  GHI
* EMNOC
*   D 
3) number of grid pins
4) array of grid pins, rightmost digit first
5) (optional) number of segments to be used for numbers (7 or 9)
*/
VFD::VFD(const byte numSegPins, const byte * segPins,const byte numGridPins, const byte * gridPins)
{
  _numSegPins = numSegPins;
  _segPins = segPins;
  _numGridPins = numGridPins;
  _gridPins = gridPins;
  _segsForNumbers = 7;
  for(byte i = 0; i<_numSegPins; i++) {
    pinMode(_segPins[i],OUTPUT);
  }
  for(byte i = 0; i<_numGridPins; i++) {
    pinMode(_gridPins[i],OUTPUT);
  }
  off(0);
}

VFD::VFD(const byte numSegPins, const byte * segPins,const byte numGridPins, const byte * gridPins, const byte segsForNumbers)
{
  _numSegPins = numSegPins;
  _segPins = segPins;
  _numGridPins = numGridPins;
  _gridPins = gridPins;
  _segsForNumbers = segsForNumbers;
  for(byte i = 0; i<_numSegPins; i++) {
    pinMode(_segPins[i],OUTPUT);
  }
  for(byte i = 0; i<_numGridPins; i++) {
    pinMode(_gridPins[i],OUTPUT);
  }
  off(0);
}

void VFD::on()
{
  for(byte k=0; k<_numGridPins; k++) {
    for (byte i = 0; i < _numSegPins; i++) {
      segment(k, i);
    }
  }
}

void VFD::off(int duration)
{
  for (byte i = 0; i < _numSegPins; i++) {
    digitalWrite(_segPins[i], HIGH);
  }
  for (byte i = 0; i < _numGridPins; i++) {
    digitalWrite(_gridPins[i], HIGH);
  } 
  delay(duration);
}

void VFD::blink(int duration) {
  if(isOff) {
    off(1);
  } else {
    on();
  }
  if(millis() > lastChange + duration) {
    isOff = !isOff;
    lastChange = millis();
  }
}

void VFD::segment(byte g, byte s) {
    digitalWrite(_gridPins[g], LOW);
    digitalWrite(_segPins[s], LOW);
}

void VFD::segment(byte g, byte s, int duration) {
  off(0);
  digitalWrite(_gridPins[g], LOW);
  digitalWrite(_segPins[s], LOW);
  delay(duration);
  digitalWrite(_gridPins[g], HIGH);
  digitalWrite(_segPins[s], HIGH);
}

void VFD::number(byte d, byte num) {
  for (byte i = 0; i < _segsForNumbers; i++) {
    if(_segsForNumbers == 9) {
      digitalWrite(_segPins[i], numbers9[num][i]);
    } else {
      digitalWrite(_segPins[i], numbers7[num][i]);
    }
  }
  for (byte j = 0; j < _numGridPins; j++) {
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
    ones = byte(onesChar - '0');
    number(0, ones);
  } else if(num >=10 && num < 100) {
    onesChar = numStr[1];
    tensChar = numStr[0];
    ones = byte(onesChar - '0');
    tens = byte(tensChar - '0');
    number(0, ones);
    number(1, tens);
  } else if(num >=100 && num < 1000) {
    onesChar = numStr[2];
    tensChar = numStr[1];
    hundredsChar = numStr[0];
    ones = byte(onesChar - '0');
    tens = byte(tensChar - '0');
    hundreds = int(hundredsChar - '0');
    number(0, ones);
    number(1, tens);
    number(2, hundreds);
  } else if(num >= 1000 && num < 10000) {
    onesChar = numStr[3];
    tensChar = numStr[2];
    hundredsChar = numStr[1];
    thousandsChar = numStr[0];
    ones = byte(onesChar - '0');
    tens = byte(tensChar - '0');
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
    ones = byte(onesChar - '0');
    tens = byte(tensChar - '0');
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

void VFD::multiDigitNumber(byte g, int num) {
  char onesChar, tensChar, hundredsChar, thousandsChar, tenThousandsChar;
  int ones, tens, hundreds, thousands, tenThousands;
  String numStr = String(num);

  if (num < 10) {
    onesChar = numStr[0];
    ones = byte(onesChar - '0');
    number(g, ones);
  } else if(num >=10 && num < 100) {
    onesChar = numStr[1];
    tensChar = numStr[0];
    ones = byte(onesChar - '0');
    tens = byte(tensChar - '0');
    number(g, ones);
    number(g+1, tens);
  } else if(num >=100 && num < 1000) {
    onesChar = numStr[2];
    tensChar = numStr[1];
    hundredsChar = numStr[0];
    ones = byte(onesChar - '0');
    tens = byte(tensChar - '0');
    hundreds = int(hundredsChar - '0');
    number(g, ones);
    number(g+1, tens);
    number(g+2, hundreds);
  } else if(num >= 1000 && num < 10000) {
    onesChar = numStr[3];
    tensChar = numStr[2];
    hundredsChar = numStr[1];
    thousandsChar = numStr[0];
    ones = byte(onesChar - '0');
    tens = byte(tensChar - '0');
    hundreds = int(hundredsChar - '0');
    thousands = int(thousandsChar - '0');
    number(g, ones);
    number(g+1, tens);
    number(g+2, hundreds);
    number(g+3, thousands);
  } else {
    onesChar = numStr[4];
    tensChar = numStr[3];
    hundredsChar = numStr[2];
    thousandsChar = numStr[1];
    tenThousandsChar = numStr[0];
    ones = byte(onesChar - '0');
    tens = byte(tensChar - '0');
    hundreds = int(hundredsChar - '0');
    thousands = int(thousandsChar - '0');
    tenThousands = int(tenThousandsChar - '0');
    number(g, ones);
    number(g+1, tens);
    number(g+2, hundreds);
    number(g+3, thousands);
    number(g+4, tenThousands);  
  }
}

void VFD::crazyEights(int speed) {
  if(_segsForNumbers == 9) {
    byte segs[] = {0, 1, 8, 7, 6, 4, 3, 2, 8, 7, 6, 5};
    for (byte i = 0; i < sizeof(segs)/sizeof(segs[0]); i++) {
      for(byte j = 0; j < _numGridPins; j++) {
        segment(j, segs[i]);
      }
      delay(speed);
      off(1);   
    }   
  } else {
    byte segs[] = {0, 1, 6, 4, 3, 2, 6, 5};
    for (byte i = 0; i < sizeof(segs)/sizeof(segs[0]); i++) {
      for(byte j = 0; j < _numGridPins; j++) {
        segment(j, segs[i]);
      }
      delay(speed);
      off(1);   
    }
  }
}

void VFD::message(String text, byte firstGrid, byte lastGrid, int waitTime) {
  byte len = text.length();
  byte multiplier = lastGrid - firstGrid;
  if (millis() > lastTime + waitTime) {
    messageFragment++;
    lastTime = millis();
  }
  if (messageFragment * multiplier >= len) messageFragment = 0;
  messageSegment(text.substring(messageFragment * multiplier, messageFragment * multiplier + multiplier), firstGrid, lastGrid);
}

void VFD::scrollingMessage(String text, byte firstGrid, byte lastGrid, int waitTime) {
  String newText = "       " + text;
  byte len = newText.length();
  if (millis() > lastTime + waitTime / (lastGrid - firstGrid)) {
    messageFragment++;
    lastTime = millis();
  }
  if (messageFragment > len) messageFragment = 0;
  messageSegment(newText.substring(messageFragment, messageFragment + (lastGrid - firstGrid)), firstGrid, lastGrid);
}

void VFD::messageSegment(String mesg, byte firstGrid, byte lastGrid) {
	mesg.toLowerCase();
  for(byte i = firstGrid; i < lastGrid; i++) {
  	char let = mesg[i];
    letter(lastGrid - 1 - i, let);
  }
}

void VFD::letter(byte g, char whichLetter) {
  for (byte i = 0; i < _numGridPins; i++) {
    if (i == g) {
      digitalWrite(_gridPins[i], LOW);
    } else {
      digitalWrite(_gridPins[i], HIGH);
    }
  }
  byte tempLetter = ' ';
  switch (whichLetter) {
    case ' ':
      tempLetter = 0;
      break;
    case 'a':
      tempLetter = 1;
      break;
    case 'b':
      tempLetter = 2;
      break;
    case 'c':
      tempLetter = 3;
      break;
    case 'd':
      tempLetter = 4;
      break;
    case 'e':
      tempLetter = 5;
      break;
    case 'f':
      tempLetter = 6;
      break;
    case 'g':
      tempLetter = 7;
      break;
    case 'h':
      tempLetter = 8;
      break;
    case 'i':
      tempLetter = 9;
      break;
    case 'j':
      tempLetter = 10;
      break;
    case 'k':
      tempLetter = 11;
      break;
    case 'l':
      tempLetter = 12;
      break;
    case 'm':
      tempLetter = 13;
      break;
    case 'n':
      tempLetter = 14;
      break;
    case 'o':
      tempLetter = 15;
      break;
    case 'p':
      tempLetter = 16;
      break;
    case 'q':
      tempLetter = 17;
      break;
    case 'r':
      tempLetter = 18;
      break;
    case 's':
      tempLetter = 19;
      break;
    case 't':
      tempLetter = 20;
      break;
    case 'u':
      tempLetter = 21;
      break;
    case 'v':
      tempLetter = 22;
      break;
    case 'w':
      tempLetter = 23;
      break;
    case 'x':
      tempLetter = 24;
      break;
    case 'y':
      tempLetter = 25;
      break;
    case 'z':
      tempLetter = 26;
      break;
    case '0':
      tempLetter = 27;
      break;
    case '1':
      tempLetter = 28;
      break;
    case '2':
      tempLetter = 29;
      break;
    case '3':
      tempLetter = 30;
      break;
    case '4':
      tempLetter = 31;
      break;
    case '5':
      tempLetter = 32;
      break;
    case '6':
      tempLetter = 33;
      break;
    case '7':
      tempLetter = 34;
      break;
    case '8':
      tempLetter = 35;
      break;
    case '9':
      tempLetter = 36;
      break;
    default:
      tempLetter = 0;
      break;
  }
  for (byte i = 0; i < sizeof(alphanum[0]) / sizeof(alphanum[0][0]); i++) {
    digitalWrite(_segPins[i], alphanum[tempLetter][i]);
  }
  delay(3);
}
