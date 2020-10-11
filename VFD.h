#ifndef VFD_h
#define VFD_h

#include "Arduino.h"

class VFD
{

public:
	VFD(const byte numSegPins, const byte * segPins,const byte numGridPins, const byte * gridPins, const byte segsForNumbers);
	VFD(const byte numSegPins, const byte * segPins,const byte numGridPins, const byte * gridPins);
	void on();
	void off(int duration);
	void blink(int duration);
	void number(byte g, byte num);
	void multiDigitNumber(int num);
	void segment(byte g, byte s);
	void segment(byte g, byte s, int duration);
	void crazyEights(int speed);
	void letter(byte g, char whichletter);
	void message(String text, byte firstGrid, byte lastGrid, int waitTime);
	void scrollingMessage(String text, byte firstGrid, byte lastGrid, int waitTime);
private:
	void messageSegment(String mesg, byte firstGrid, byte lastGrid);
	byte _numSegPins;
	const byte * _segPins;
	byte _numGridPins;
	const byte * _gridPins;
	byte _segsForNumbers;
	byte messageFragment = 0;
	//for text functions
	int waitTime = 0;
	double lastTime = 0;
	//for blink
	double lastChange = 0;
	bool isOff = false;

	const byte PROGMEM numbers7[10][7] = {
	  {0, 0, 0, 0, 0, 0, 1},//0
	  {1, 0, 0, 1, 1, 1, 1},//1
	  {0, 0, 1, 0, 0, 1, 0},//2
	  {0, 0, 0, 0, 1, 1, 0},//3
	  {1, 0, 0, 1, 1, 0, 0},//4
	  {0, 1, 0, 0, 1, 0, 0},//5
	  {0, 1, 0, 0, 0, 0, 0},//6
	  {0, 0, 0, 1, 1, 1, 1},//7
	  {0, 0, 0, 0, 0, 0, 0},//8
	  {0, 0, 0, 0, 1, 0, 0}//9
	};
	const byte PROGMEM numbers9[10][9] = {
	  {0, 0, 0, 0, 0, 0, 1, 1, 1},//0
	  {1, 0, 0, 1, 1, 1, 1, 1, 1},//1
	  {0, 0, 1, 0, 0, 1, 0, 0, 0},//2
	  {0, 0, 0, 0, 1, 1, 1, 0, 0},//3
	  {1, 0, 0, 1, 1, 0, 0, 0, 0},//4
	  {0, 1, 0, 0, 1, 0, 0, 0, 0},//5
	  {0, 1, 0, 0, 0, 0, 0, 0, 0},//6
	  {0, 0, 0, 1, 1, 1, 1, 1, 1},//7
	  {0, 0, 0, 0, 0, 0, 0, 0, 0},//8
	  {0, 0, 0, 0, 1, 0, 0, 0, 0}//9
	};
	const byte PROGMEM alphanum[37][15] {
	  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //space
	  {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}, //a
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},  //b
	  {0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //c
	  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //d
	  {0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},  //e
	  {0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},  //f
	  {0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},  //g
	  {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},  //h
	  {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},  //i
	  {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //j
	  {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0},  //k
	  {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //l
	  {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},  //m
	  {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0},  //n
	  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //o
	  {0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},  //p
	  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1},  //q
	  {0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},  //r
	  {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},  //s
	  {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},  //t
	  {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //u
	  {1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1},  //v
	  {1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0},  //w
	  {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0},  //x
	  {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},  //y
	  {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1},  //z
	  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //0
	  {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1
	  {0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},//2
	  {0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},//3
	  {1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},//4
	  {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},//5
	  {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},//6
	  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//7
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},//8
	  {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}//9
	};

};

#endif
