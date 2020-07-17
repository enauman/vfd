#include <VFD.h>
const int NUM_SEG_PINS = 9;
const int NUM_GRID_PINS = 5;
const int segments[] = {8,7,6,5,4,3,2, A1, A0};
const int grids[] = {13, 12, 11, 10, 9};

VFD disp(NUM_SEG_PINS, segments, NUM_GRID_PINS, grids);

void setup() {}

void loop() {
  disp.blink(1000);
}