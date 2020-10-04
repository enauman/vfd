//Example sketch using a timer to delay while multiplexing.
#include <VFD.h>

const byte NUM_SEG_PINS = 9;
const byte NUM_GRID_PINS = 5;
const byte segments[] = {8,7,6,5,4,3,2, A1, A0};
const byte grids[] = {13, 12, 11, 10, 9};

VFD disp(NUM_SEG_PINS, segments, NUM_GRID_PINS, grids);
byte state = 0;
int delayTime = 500;
double lastChange = 0;

void setup() {}

void loop() {
if (state == 0) {
    disp.multiDigitNumber(96);
  } else {
    disp.off(0);
  }
  if (millis() > lastChange + delayTime) {
    state = !state;
    lastChange = millis();
  }
}
