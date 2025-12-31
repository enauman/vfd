# Python version
Requirement: gpiozero library<br />
See use of gpiozero in virtual environment re pin factory error, solutions <a href="https://raspberrypi.stackexchange.com/questions/148817/raspi-4-bookworm-gpio-issues-using-gpiozero">here</a> 
## Microcontrollers
I've only done used this with a Raspberry Pi 5 with Debian release 13 (trixie). Could it be done with a Raspberry Pi Pico? 
## Functions
<ul>
  <li>
    display.segment(g, s): Display a given segment(s) in a given grid(g), with default duration of 0.
  </li>
  <li>
    display.segment(g, s, duration): Display a given segment(s) in a given grid(g), with a given duration.
  </li>
  <li>
    display.set_on(): Turn on whole display.
  </li>
  <li>
    display.set_on(duration): Turn on whole display for a given duration.
  </li>
  <li>
    display.set_off(): Turn off whole display.
  </li>
  <li>
    display.set_off(duration): Turn off whole display for a given duration.
  </li>
  <li>
    display.blink(speed, duration): Blink entire display at a given speed for a given duration.
  </li>
  <li>
    display.number(g, digit): Display a single digit number on the grid(g) specified. Stays on for a duration of 0.005 sec.
  </li>
  <li>
    display.multi_digit_number(number): Display a number from 0 to 9999 on the rightmost grids. Digits are multiplexed using the number function.
  </li>
  <li>
    display.message(text): Display a string of text.
  </li>
  <li>
    display.scrolling_message(text): Display a string of text that scrolls across alphanumeric digits. Max length of text grids should be set in library variables.
  </li>
  <li>
    display.letter(g, letter): Display a letter as a string on a given grid(g).
  </li>
</ul>
<p>
  <img src="../images/IMG_6351.JPG" width="500">
</p>
