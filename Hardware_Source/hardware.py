
"""
This Raspberry Pi code was developed by newbiely.com
This Raspberry Pi code is made available for public use without any restriction
For comprehensive instructions and wiring diagrams, please visit:
https://newbiely.com/tutorials/raspberry-pi/raspberry-pi-rotary-encoder
"""


import RPi.GPIO as GPIO
import time
import sys
import signal

# Pin numbers on Raspberry Pi
CLK_PIN = 22   # GPIO7 connected to the rotary encoder's CLK pin
DT_PIN = 27    # GPIO8 connected to the rotary encoder's DT pin


DIRECTION_CW = 0
DIRECTION_CCW = 1

counter = 0
direction = DIRECTION_CW
CLK_state = 0
prev_CLK_state = GPIO.HIGH
prev_direction = direction
start = time.time()

button_pressed = False
prev_button_state = GPIO.HIGH

def signal_handler(sig, frame):
    GPIO.cleanup()
    sys.exit(0)

def rotary_turned_callback(channel):
        # Read the current state of the rotary encoder's CLK pin
        global prev_CLK_state
        global CLK_state
        global start
        global direction
        global prev_direction
        global counter
        global DIRECTION_CCW
        global DIRECTION_CW
        global CLK_PIN
        global DT_PIN
        CLK_state = GPIO.input(CLK_PIN)

        # If the state of CLK is changed, then pulse occurred
        # React to only the rising edge (from LOW to HIGH) to avoid double count
        if CLK_state != prev_CLK_state and CLK_state == GPIO.LOW:
            # If the DT state is HIGH, the encoder is rotating in counter-clockwise direction
            # Decrease the counter
            if GPIO.input(DT_PIN) == GPIO.LOW:
                end = time.time()
                if prev_direction == DIRECTION_CCW or end - start > 0.5:
                    counter -= 1
                    direction = DIRECTION_CCW
                    start = time.time()
            else:
                # The encoder is rotating in clockwise direction => increase the counter
                end = time.time()
                if prev_direction == DIRECTION_CW or end - start > 0.5:
                    counter += 1
                    direction = DIRECTION_CW
                    start = time.time()
                    
            prev_direction = direction
            check = time.time()
            print("Rotary Encoder:: direction:", "CLOCKWISE" if direction == DIRECTION_CW else "ANTICLOCKWISE",
                  "- count:", counter, "Time since last: ", check - start)
            file_path = "data.txt"
            with open(file_path, 'r') as file:
                lines = file.readlines()
            lines[0:3] = ["4\n", "2\n", str(counter)]
            
            with open(file_path, 'w') as file:
                file.writelines(lines)
            #time.sleep(0.05)

        # Save last CLK state
        prev_CLK_state = CLK_state
        
# Configure GPIO pins
#


# Read the initial state of the rotary encoder's CLK pin
prev_CLK_state = GPIO.HIGH

if __name__ == '__main__':
    prev_CLK_state = GPIO.HIGH
    # Configure GPIO pins
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(CLK_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(DT_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.add_event_detect(CLK_PIN, GPIO.FALLING, 
            callback=rotary_turned_callback, bouncetime=50)
    
    signal.signal(signal.SIGINT, signal_handler)
    signal.pause()


        






