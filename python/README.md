# Python version
Requirement: gpiozero library<br />
See use of gpiozero in virtual environment re pin factory error, solutions <a href="https://raspberrypi.stackexchange.com/questions/148817/raspi-4-bookworm-gpio-issues-using-gpiozero">here</a> 
## Functions
<ul>
  <li>
    <b>display.segment(g, s)</b> Display a given segment(s) in a given grid(g), with default duration of 0.
  </li>
  <li>
    <b>display.segment(g, s, duration)</b> Display a given segment(s) in a given grid(g), with a given duration.
  </li>
  <li>
    <b>display.set_on()</b> Turn on whole display.
  </li>
  <li>
    <b>display.set_on(duration)</b> Turn on whole display for a given duration.
  </li>
  <li>
    <b>display.set_off()</b> Turn off whole display.
  </li>
  <li>
    <b>display.set_off(duration)</b> Turn off whole display for a given duration.
  </li>
  <li>
    <b>display.blink(speed, duration)</b>Blink entire display at a given speed for a given duration.
  </li>
  <li>
    <b>display.number(g, digit)</b>Display a single digit number on the grid(g) specified. Stays on for a duration of 0.005 sec.
  </li>
  <li>
    <b>display.multi_digit_number(number)</b>Display a number from 0 to 9999 on the rightmost grids. Digits are multiplexed using the number function.
  </li>
  <li>
    <b>display.message(text)</b>Display a string of text.
  </li>
  <li>
    <b>display.scrolling_message(text)</b>Display a string of text that scrolls across alphanumeric digits. Max length of text grids should be set in library variables.
  </li>
  <li>
    <b>display.letter(g, letter)</b>Display a letter as a string on a given grid(g).
  </li>
</ul>
