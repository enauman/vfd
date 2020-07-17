#ifndef VFD_h
#define VFD_h

#include "Arduino.h"

class VFD
{

public:
	VFD(const int numSegPins, const int * segPins,const int numGridPins, const int * gridPins);
	void on(int duration);
	void off(int duration);
	void blink(int duration);
	void number(int d, int num);
	void multiDigitNumber(int num);
	void segment(int d, int s);
	void segment(int d, int s, int duration);
	void crazyEights(int speed);
private:
	int _numSegPins;
	const int * _segPins;
	int _numGridPins;
	const int * _gridPins;
	const int numbers[10][7] = {
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
};

#endif