from gpiozero import LED
import time
class VFD:
    def __init__(self, grid_pins, seg_pins):
        self.grids = []
        self.segments = []
        self.is_off = False
        self.last_change = 0
        self.message_segment = 0
        self.max_message_length = 8 # set max length of display digits
        self.message_speed = 0.2
        self.scrolling = False
        '''
        Create instance of display, arguments:
        1) number of segment pins
        2) number of segment pins, first 7 in conventional order (A-G) 
        for number segments if numbers wanted:
        *   A
        * F   B
        *   G
        * E   C
        *   D 
        * With star-type digit (15 segment) you can use letter, message, and scrollingMessage
        * functions, order segment pin array in this order:
        *   A
        * FJKLB
        *  GHI
        * EMNOC
        *   D 
        '''
        self.numbers = [
            [0, 0, 0, 0, 0, 0, 1],#0    
            [1, 0, 0, 1, 1, 1, 1],#1
            [0, 0, 1, 0, 0, 1, 0],#2
            [0, 0, 0, 0, 1, 1, 0],#3
            [1, 0, 0, 1, 1, 0, 0],#4
            [0, 1, 0, 0, 1, 0, 0],#5
            [0, 1, 0, 0, 0, 0, 0],#6
            [0, 0, 0, 1, 1, 1, 1],#7
            [0, 0, 0, 0, 0, 0, 0],#8
            [0, 0, 0, 0, 1, 0, 0]#9
        ]
        self.alphanumeric = [
            [0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1], #a
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],  #b
            [0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1],  #c
            [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1],  #d
            [0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1],  #e
            [0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1],  #f
            [0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1],  #g
            [1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],  #h
            [0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1],  #i
            [1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],  #j
            [1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0],  #k
            [1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1],  #l
            [1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1],  #m
            [1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0],  #n
            [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1],  #o
            [0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],  #p
            [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1],  #q
            [0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0],  #r
            [0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],  #s
            [0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1],  #t
            [1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1],  #u
            [1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1],  #v
            [1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0],  #w
            [1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0],  #x
            [1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1],  #y
            [0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1],  #z
            [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1], #0
            [1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],#1
            [0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1],#2
            [0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1],#3
            [1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],#4
            [0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],#5
            [0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],#6
            [0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],#7
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],#8
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],#9
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] #space
        ]
        # assign LED object pins
        for grid in grid_pins:
            self.grids.append(LED(grid))
        for segment in seg_pins:
            self.segments.append(LED(segment))
        
        self.set_off()

    def get_scrolling(self):
        return self.scrolling

    def segment(self, grid, seg, duration=None):
        if duration == None:
            self.grids[grid].off()
            self.segments[seg].off()
        else:
            self.set_off()
            self.grids[grid].off()
            self.segments[seg].off()
            time.sleep(duration)
            self.grids[grid].on()
            self.segments[seg].on()

    def set_on(self, duration=None):
        if duration is None:
            for grid in self.grids:
                grid.off()
            for seg in self.segments:
                seg.off()
        else:
            for grid in self.grids:
                grid.off()
            for seg in self.segments:
                seg.off()
            time.sleep(duration)
            for grid in self.grids:
                grid.on()
            for seg in self.segments:
                seg.on()

    def set_off(self, duration=None):
        if duration is None:
            for grid in self.grids:
                grid.on()
            for seg in self.segments:
                seg.on()
        else:
            for grid in self.grids:
                grid.on()
            for seg in self.segments:
                seg.on()
            time.sleep(duration)
            for grid in self.grids:
                grid.off()
            for seg in self.segments:
                seg.off()

    def blink(self, speed, duration):
        start_time = time.time()
        self.last_change = time.time()
        self.scrolling = True
        while self.scrolling:
            if self.is_off:
                self.set_off()
            else:
                self.set_on()
            if time.time() > self.last_change:
                self.is_off = not self.is_off
                self.last_change = time.time() + speed
            if time.time() > start_time + duration:
                self.scrolling = False

    def number(self, grid, number):
        self.set_off()
        self.grids[grid].off()
        for (val,seg) in enumerate(self.numbers[number]):
            if seg == 0:
                self.segments[val].off()
            else:
                self.segments[val].on()
        time.sleep(0.005)

    def multi_digit_number(self, number):
        if number > 10000: number = 9999
        if number < 0: number = 0
        split_num = str(number) #split digits into str to get separate elemts
        self.set_off()
        if len(split_num) == 1:
            self.number(0, number)
        elif len(split_num) == 2:
            self.number(0, int(split_num[1]))
            self.number(1, int(split_num[0]))
        elif len(split_num) == 3:
            self.number(0, int(split_num[2]))
            self.number(1, int(split_num[1]))
            self.number(2, int(split_num[0]))
        elif len(split_num) == 4:
            self.number(0, int(split_num[3]))
            self.number(1, int(split_num[2]))
            self.number(2, int(split_num[1]))
            self.number(3, int(split_num[0]))

    def message(self, text):
        text = text.lower()
        for i in range(len(text)):
            self.letter(i, text[len(text)-i-1])

    def scrolling_message(self, text):
        max_length = self.max_message_length
        buffer = ""
        for i in range(max_length):
            buffer += " "
        self.scrolling = True
        while self.scrolling:
            new_text = buffer + text + buffer
            msg_length = len(new_text)
            if time.time() > self.last_change:
                self.message_segment += 1
                self.last_change = time.time() + self.message_speed
            if self.message_segment + max_length >= msg_length:
                self.scrolling = False
                self.message_segment = 0
            self.send_message_segment(new_text[self.message_segment:self.message_segment + max_length], max_length)

    def send_message_segment(self, message, max_length):
        message = message.lower()
        for i in range(max_length):
            self.letter(i,message[max_length - 1 - i])

    def letter(self, grid, which_letter):
        self.set_off()
        for i in range(len(self.grids)):
            if i == grid:
                self.grids[i].off()
            else:
                self.grids[i].on()
        alpha_to_num = {
            'a': 0,
            'b': 1,
            'c': 2,
            'd': 3,
            'e': 4,
            'f': 5,
            'g': 6,
            'h': 7,
            'i': 8,
            'j': 9,
            'k': 10,
            'l': 11,
            'm': 12,
            'n': 13,
            'o': 14,
            'p': 15,
            'q': 16,
            'r': 17,
            's': 18,
            't': 19,
            'u': 20,
            'v': 21,
            'w': 22,
            'x': 23,
            'y': 24,
            'z': 25,
            '0': 26,
            '1': 27,
            '2': 28,
            '3': 29,
            '4': 30,
            '5': 31,
            '6': 32,
            '7': 33,
            '8': 34,
            '9': 35,
            ' ': 36
        }
        for key, value in alpha_to_num.items():
            if which_letter == key:
                for (val,seg) in enumerate(self.alphanumeric[value]):
                    if seg == 0:
                        self.segments[val].off()
                    else:
                        self.segments[val].on()
        time.sleep(0.005)
