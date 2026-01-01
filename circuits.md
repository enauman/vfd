# Circuit details
The following is an example circuit, illustrating how a very simple 4-digit, 7 segment + decimal point (dp) would be driven with a MCU, in this case the Adafruit Metro Mini. For most VFDs the Metro Mini doesn't provide enough GPIO pins so I've used different versions of the Teensy board. Even the <a href="https://www.pjrc.com/teensy/teensyLC.html">Teensy LC</a> has 27 GPIO pins.<br />
## Driving the Filament
In this circuit the filament is driven with an LM4871 chip which provides a square wave across the filament. For testing purposes you can just use a 3V battery source but for permanent driving just putting 3V DC, say from the 3.3V pin on the MCU, will result in a voltage drop on one side of the VFD and ghost segment artifacts will appear. With 5V in to the LM4871, the 10Ω value of R4 and R5 seems to provide a good level of brightness. But they can be changed to a lower value to increase the brighness of the display if needed. Sometimes the sweet spot for the filament current requires a bit of experimentation.<br />
On an ocsilloscope the filament signal looks like this, with an oscillating 3V current that alternates from one side to the other to eliminate the voltage drop across the filament. <br />

## High voltage for grids and segments
A buck booster <a href="https://www.amazon.com/dp/B0CWKWX7QC?ref=ppx_yo2ov_dt_b_fed_asin_title">such as this</a> is used to boost voltage from the 3.3V pin on the MCU to 21V for the grid and segment pins.<br /><br />
<img src="images/Schematic_LM4871-adapter_2025-12-31.png" /><br />
