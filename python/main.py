# prototype for generic vfd class
from python.vfd import VFD
# change grid and segment pins to suit display circuit
grid_pins = [6,13,19,26,21,20,16,12, 5,0]
segment_pins = [1,24,15,17,14,23,18,7,8,25,2,3,4,27,22,10]
display = VFD(grid_pins,segment_pins)

display.scrolling_message('awesome')

