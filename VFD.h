#ifndef VFD_h
#define VFD_h

#include "Arduino.h"

class VFD
{

public:
	VFD(const int numSegPins, const int * segPins,const int numGridPins, const int * gridPins, const int segsForNumbers);
	VFD(const int numSegPins, const int * segPins,const int numGridPins, const int * gridPins);
	void on(int duration);
	void off(int duration);
	void blink(int duration);
	void number(int g, int num);
	void multiDigitNumber(int num);
	void segment(int g, int s);
	void segment(int g, int s, int duration);
	void crazyEights(int speed);
	void letter(int g, String whichletter);
	void message(String text, byte firstGrid, byte lastGrid, int waitTime);
	void scrollingMessage(String text, byte firstGrid, byte lastGrid, int waitTime);
private:
	void messageSegment(String mesg, byte firstGrid, byte lastGrid);
	int _numSegPins;
	const int * _segPins;
	int _numGridPins;
	const int * _gridPins;
	int _segsForNumbers;
	int messageFragment = 0;
	//for timer
	int waitTime = 1000;
	double lastTime = 0;
	const int numbers7[10][7] = {
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
	const int numbers9[10][9] = {
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
	const int alphanum[37][15] {
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