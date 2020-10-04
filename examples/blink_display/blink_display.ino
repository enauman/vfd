#include <VFD.h>
const byte NUM_SEG_PINS = 9;
const byte NUM_GRID_PINS = 5;
const byte segments[] = {8,7,6,5,4,3,2, A1, A0};
const byte grids[] = {13, 12, 11, 10, 9};

VFD disp(NUM_SEG_PINS, segments, NUM_GRID_PINS, grids);

void setup() {}

void loop() {
  disp.blink(1000);
}
