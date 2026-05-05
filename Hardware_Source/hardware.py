
import RPi.GPIO as GPIO
import time
import smbus2 as smbus

DIRECTION_CW = 0
DIRECTION_CCW = 1

bus = smbus.SMBus(1)

class Encoder:
    prev_direction = DIRECTION_CW
    CLK_state = 1
    DT_state = 1
    prev_CLK_state = 1
    voice = 4
    param = 0
    
    def __init__(self, voice, param):
        self.voice = voice
        self.param = param
    
    
    
INTA_PIN = 17
INTB_PIN = 27

MCP_ADDR0 = 0x20

encoderList = [Encoder(4, 0), Encoder(4, 1)]
dataList = [0] * 154
start = time.time()


GPIO.setmode(GPIO.BCM)
GPIO.setup(INTA_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTB_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

bus.write_byte_data(MCP_ADDR0, 0x0C, 0b11111111)

bus.write_byte_data(MCP_ADDR0, 0x00, 0xFF)  # IODIRA = inputs


bus.write_byte_data(MCP_ADDR0, 0x04, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR0, 0x08, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR0, 0x10)  # INTCAP



    

def interrupt0A(channel):
 #   print("!!!")
    intf = bus.read_byte_data(MCP_ADDR0,0x0E)
    values = bus.read_byte_data(MCP_ADDR0, 0x10)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin
            if pin0 % 2 != 0:
                return
    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1
    
    if pin0 == 0:
        encoderList[0].prev_CLK_state = encoderList[0].CLK_state
        encoderList[0].CLK_state = pin0_state
        encoderList[0].DT_state = pin1_state
        rotary_turned(encoderList[0])
    if pin0 == 2:
        encoderList[1].prev_CLK_state = encoderList[1].CLK_state
        encoderList[1].CLK_state = pin0_state
        encoderList[1].DT_state = pin1_state
        rotary_turned(encoderList[1])
        
def rotary_turned(e):
        # Read the current state of the rotary encoder's CLK pin
        CLK_state = e.CLK_state
        prev_CLK_state = e.prev_CLK_state
        DT_state = e.DT_state
        prev_direction = e.prev_direction
        voice = e.voice
        param = e.param
        global start
        index = voice * 31 + param


        direction = 0
        # If the state of CLK is changed, then pulse occurred
        # React to only the rising edge (from LOW to HIGH) to avoid double count
        if CLK_state != prev_CLK_state and CLK_state == GPIO.LOW:
            # If the DT state is HIGH, the encoder is rotating in counter-clockwise direction
            # Decrease the counter
            if DT_state == GPIO.LOW:
                end = time.time()
                if prev_direction == DIRECTION_CCW or end - start > 0.5:
                    dataList[index] -= 1
                    direction = DIRECTION_CCW
                    start = time.time()
            else:
                # The encoder is rotating in clockwise direction => increase the counter
                end = time.time()
                if prev_direction == DIRECTION_CW or end - start > 0.5:
                    dataList[index] += 1
                    direction = DIRECTION_CW
                    start = time.time()
                    
            e.prev_direction = direction
            check = time.time()
            print("Rotary Encoder:: direction:", "CLOCKWISE" if direction == DIRECTION_CW else "ANTICLOCKWISE",
                  "- count:", dataList[index], "Time since last: ", check - start)
            file_path = "data.txt"
            with open(file_path, 'r') as file:
                lines = file.readlines()
            lines[0:3] = [str(voice) + "\n", str(param) + "\n", str(dataList[index])]
            
            with open(file_path, 'w') as file:
                file.writelines(lines)
            time.sleep(0.05)
    
    
    

GPIO.add_event_detect(INTA_PIN, GPIO.FALLING, callback=interrupt0A, bouncetime=1)

#GPIO.add_event_detect(INTB_PIN, GPIO.FALLING, callback=interrupt0B, bouncetime=5)

#while True:
#    print(GPIO.input(INTA_PIN))
#    time.sleep(0.1)



try:
    while True:
        time.sleep(0.01)
except KeyboardInterrupt:
    GPIO.cleanup()




