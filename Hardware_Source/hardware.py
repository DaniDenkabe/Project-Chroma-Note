
import RPi.GPIO as GPIO
import time
import smbus2 as smbus
from pathlib import Path

home = Path.home()
hallCounter = 0

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
    
    
    
INTA_PIN0 = 17
INTB_PIN0 = 27
INTA_PIN1 = 9
INTB_PIN1 = 10
INTA_PIN2 = 5
INTB_PIN2 = 6
INTA_PIN3 = 19
INTB_PIN3 = 26
INTA_PIN4 = 23
INTB_PIN4 = 24
INTA_PIN5 = 25
INTB_PIN5 = 8 


MCP_ADDR0 = 0x20
MCP_ADDR1 = 0x21
MCP_ADDR2 = 0x22
MCP_ADDR3 = 0x24
MCP_ADDR4 = 0x27
MCP_ADDR5 = 0x23

GAIN = 0
PITCH = 1
FREQ = 2
WOW = 3 
AMP = 4
LFO = 5
SAT = 6
HIGHFREQ = 7
LOWFREQ = 8
SAMPLERATE = 9
BIT = 10 
THRESH = 11 
RATIO = 12
ATTACK = 13
REALEASE = 14 
DELAY_AMOUNT = 15 
LOOP_LENGTH = 16 
LOOP_IS_ON = 17
DELAY_SPACE = 18
DELAY_FEEDBACK = 19
DELAY_IS_ON = 20
ON_SPACE = 21 
OFF_SPACE = 22
ON_OFFSET = 23 
OFF_OFFSET = 24 
STUTTER_ATTACK = 25 
STUTTER_RELEASE = 26
STUTTER_IS_ON = 27 
NOISE_MAG = 28
BEND = 29
PAN = 30
MUTE = 31

encoderList = {"P/G0" : Encoder(0, GAIN), "BEND0" : Encoder(0, BEND), "P/G1" : Encoder(1, GAIN),
               "BEND1" : Encoder(1, BEND), "P/G2" : Encoder(2, GAIN), "BEND2" : Encoder(2, BEND), 
               "P/G3" : Encoder(3, GAIN), "BEND3" : Encoder(3, BEND), "P/G4" : Encoder(4, GAIN), 
               "BEND4" : Encoder(4, BEND), "AMP" : Encoder(4, AMP), "FREQ" : Encoder(4, FREQ), 
               "LFO" : Encoder(4, LFO), "WOW" : Encoder(4, WOW), "BIT" : Encoder(4, BIT), 
               "SR" : Encoder(4, SAMPLERATE), "NOISE" : Encoder(4, NOISE_MAG), "SAT" : Encoder(4, SAT),
               "DELAY SPACE" : Encoder(4, DELAY_SPACE), "DELAY FEEDBACK" : Encoder(4, DELAY_FEEDBACK),
               "COMP THRESH" : Encoder(4, THRESH), "COMP RATIO" : Encoder(4, RATIO),
               "LOWFREQ" : Encoder(4, LOWFREQ), "HIGHFREQ" : Encoder(4, HIGHFREQ),
               "PAN" : Encoder(4, PAN), "LOOP LENGTH" : Encoder(4, LOOP_LENGTH),
               "ON SPACE" : Encoder(4, ON_SPACE), "OFF SPACE" : Encoder(4, OFF_SPACE),
               "ON OFFSET" : Encoder(4, ON_OFFSET), "OFF OFFSET" : Encoder(4, OFF_OFFSET),
               "STUTTER RELEASE" : Encoder(4, STUTTER_RELEASE), "STUTTER ATTACK" : Encoder(4, STUTTER_ATTACK)}
dataList = [0] * 155
pressCheckList = [True, True, True]
start = time.time()
ctrl = 0
selectedVoice = 4

GPIO.setmode(GPIO.BCM)
GPIO.setup(INTA_PIN0, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTB_PIN0, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTA_PIN1, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTB_PIN1, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTA_PIN2, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTB_PIN2, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTA_PIN3, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTB_PIN3, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTA_PIN4, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(INTB_PIN4, GPIO.IN, pull_up_down=GPIO.PUD_UP)





bus.write_byte_data(MCP_ADDR0, 0x0C, 0b11111111)
bus.write_byte_data(MCP_ADDR1, 0x0C, 0b11111111)
bus.write_byte_data(MCP_ADDR2, 0x0C, 0b11111111)
bus.write_byte_data(MCP_ADDR3, 0x0C, 0b11111111)
bus.write_byte_data(MCP_ADDR4, 0x0C, 0b11111111)

bus.write_byte_data(MCP_ADDR0, 0x0D, 0b11111111)
bus.write_byte_data(MCP_ADDR1, 0x0D, 0b11111111)
bus.write_byte_data(MCP_ADDR2, 0x0D, 0b11111111)
bus.write_byte_data(MCP_ADDR3, 0x0D, 0b11111111)
bus.write_byte_data(MCP_ADDR4, 0x0D, 0b00011111)

bus.write_byte_data(MCP_ADDR0, 0x00, 0xFF)  # IODIRA = inputs
bus.write_byte_data(MCP_ADDR1, 0x00, 0xFF)  # IODIRA = inputs
bus.write_byte_data(MCP_ADDR2, 0x00, 0xFF)  # IODIRA = inputs
bus.write_byte_data(MCP_ADDR3, 0x00, 0xFF)  # IODIRA = inputs
bus.write_byte_data(MCP_ADDR4, 0x00, 0xFF)  # IODIRA = inputs

bus.write_byte_data(MCP_ADDR0, 0x01, 0xFF)  # IODIRB = inputs
bus.write_byte_data(MCP_ADDR1, 0x01, 0xFF)  # IODIRB = inputs
bus.write_byte_data(MCP_ADDR2, 0x01, 0xFF)  # IODIRB = inputs
bus.write_byte_data(MCP_ADDR3, 0x01, 0xFF)  # IODIRB = inputs
bus.write_byte_data(MCP_ADDR4, 0x01, 0b00011111)  # IODIRB = inputs




bus.write_byte_data(MCP_ADDR0, 0x04, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR0, 0x08, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR0, 0x10)  # INTCAP

bus.write_byte_data(MCP_ADDR1, 0x04, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR1, 0x08, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR1, 0x10)  # INTCAP

bus.write_byte_data(MCP_ADDR2, 0x04, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR2, 0x08, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR2, 0x10)  # INTCAP

bus.write_byte_data(MCP_ADDR3, 0x04, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR3, 0x08, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR3, 0x10)  # INTCAP

bus.write_byte_data(MCP_ADDR4, 0x04, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR4, 0x08, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR4, 0x10)  # INTCAP 


bus.write_byte_data(MCP_ADDR0, 0x05, 0xFF)  # GPINTENB (enable interrupts)
bus.write_byte_data(MCP_ADDR0, 0x09, 0x00)  # INTCONB (interrupt on change)
bus.read_byte_data(MCP_ADDR0, 0x11)  # INTCAP

bus.write_byte_data(MCP_ADDR1, 0x05, 0xFF)  # GPINTENB (enable interrupts)
bus.write_byte_data(MCP_ADDR1, 0x09, 0x00)  # INTCONB (interrupt on change)
bus.read_byte_data(MCP_ADDR1, 0x11)  # INTCAP

bus.write_byte_data(MCP_ADDR2, 0x05, 0xFF)  # GPINTENB (enable interrupts)
bus.write_byte_data(MCP_ADDR2, 0x09, 0x00)  # INTCONB (interrupt on change)
bus.read_byte_data(MCP_ADDR2, 0x11)  # INTCAP

bus.write_byte_data(MCP_ADDR3, 0x05, 0xFF)  # GPINTENB (enable interrupts)
bus.write_byte_data(MCP_ADDR3, 0x09, 0x00)  # INTCONB (interrupt on change)
bus.read_byte_data(MCP_ADDR3, 0x11)  # INTCAP

bus.write_byte_data(MCP_ADDR4, 0x05, 0b00011111)  # GPINTENB (enable interrupts)
bus.write_byte_data(MCP_ADDR4, 0x09, 0b11100000)  # INTCONB (interrupt on change)
bus.read_byte_data(MCP_ADDR4, 0x11)  # INTCAP



def interrupt0A(channel):
 #   print("!!!")

    global selectedVoice

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
        encoderList["AMP"].voice = selectedVoice
        rotary_turned(encoderList["AMP"], pin0_state, pin1_state)
    if pin0 == 2:
        encoderList["FREQ"].voice = selectedVoice
        rotary_turned(encoderList["FREQ"], pin0_state, pin1_state)
    if pin0 == 4:
        encoderList["LFO"].voice = selectedVoice
        rotary_turned(encoderList["LFO"], pin0_state, pin1_state)       
    if pin0 == 6:
        encoderList["WOW"].voice = selectedVoice
        rotary_turned(encoderList["WOW"], pin0_state, pin1_state)

def interrupt0B(channel):
 #   print("!!!")
    intf = bus.read_byte_data(MCP_ADDR0,0x0F)
    values = bus.read_byte_data(MCP_ADDR0, 0x11)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0

    global selectedVoice
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin

    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1
    

    
    if pin0 == 0:
        encoderList["BIT"].voice = selectedVoice
        rotary_turned(encoderList["BIT"], pin0_state, pin1_state)
    if pin0 == 2:
        encoderList["SR"].voice = selectedVoice
        rotary_turned(encoderList["SR"], pin0_state, pin1_state)
    if pin0 == 4:
        encoderList["NOISE"].voice = selectedVoice
        rotary_turned(encoderList["NOISE"], pin0_state, pin1_state)
    if pin0 == 6:
        encoderList["SAT"].voice = selectedVoice
        rotary_turned(encoderList["SAT"], pin0_state, pin1_state)

 




def interrupt1A(channel):
 #   print("!!!")

    global selectedVoice

    intf = bus.read_byte_data(MCP_ADDR1,0x0E)
    values = bus.read_byte_data(MCP_ADDR1, 0x10)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin
    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1
    
    if pin0 == 0:
        encoderList["DELAY SPACE"].voice = selectedVoice
        rotary_turned(encoderList["DELAY SPACE"], pin0_state, pin1_state)
    if pin0 == 2:
        encoderList["DELAY FEEDBACK"].voice = selectedVoice
        rotary_turned(encoderList["DELAY FEEDBACK"], pin0_state, pin1_state)
    if pin0 == 4:
        encoderList["COMP THRESH"].voice = selectedVoice
        rotary_turned(encoderList["COMP THRESH"], pin0_state, pin1_state)
    if pin0 == 6:
        encoderList["COMP RATIO"].voice = selectedVoice
        rotary_turned(encoderList["COMP RATIO"], pin0_state, pin1_state)






def interrupt1B(channel):
#    print("!!!")
 
    global selectedVoice

    intf = bus.read_byte_data(MCP_ADDR1,0x0F)
    values = bus.read_byte_data(MCP_ADDR1, 0x11)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin
    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1

    
    if pin0 == 0:
        encoderList["LOWFREQ"].voice = selectedVoice
        rotary_turned(encoderList["LOWFREQ"], pin0_state, pin1_state)
    if pin0 == 2:
        encoderList["HIGHFREQ"].voice = selectedVoice
        rotary_turned(encoderList["HIGHFREQ"], pin0_state, pin1_state)
    if pin0 == 4:
        encoderList["PAN"].voice = selectedVoice
        rotary_turned(encoderList["PAN"], pin0_state, pin1_state)
    if pin0 >= 6:
        encoderList["LOOP LENGTH"].voice = selectedVoice
        rotary_turned(encoderList["LOOP LENGTH"], pin0_state, pin1_state)




def interrupt2A(channel):
 #   print("!!!")

    global selectedVoice

    intf = bus.read_byte_data(MCP_ADDR2,0x0E)
    values = bus.read_byte_data(MCP_ADDR2, 0x10)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin
    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1
    
    if pin0 == 0:
        encoderList["ON SPACE"].voice = selectedVoice
        rotary_turned(encoderList["ON SPACE"], pin0_state, pin1_state)
    if pin0 == 2:
        encoderList["OFF SPACE"].voice = selectedVoice
        rotary_turned(encoderList["OFF SPACE"], pin0_state, pin1_state)
    if pin0 == 4:
        encoderList["ON OFFSET"].voice = selectedVoice
        rotary_turned(encoderList["ON OFFSET"], pin0_state, pin1_state)
    if pin0 == 6:
        encoderList["OFF OFFSET"].voice = selectedVoice
        rotary_turned(encoderList["OFF OFFSET"], pin0_state, pin1_state)


def interrupt2B(channel):
 #   print("!!!")

    global selectedVoice



    intf = bus.read_byte_data(MCP_ADDR2,0x0F)
    values = bus.read_byte_data(MCP_ADDR2, 0x11)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin
    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1
 
    if pin0 == 0
        if pressCheckList[0]:
            button_pressed(selectedVoice, STUTTER_IS_ON, 1)

            value = bus.read_byte_data(address, 0x12)
            value ^= 0b01000000
            bus.write_byte_data(address, 0x12, value)

            pressCheckList[0] = False
        else:
            pressCheckList[0] = True
    if pin0 == 1:
        if pressCheckList[1]:
            button_pressed(selectedVoice, LOOP_IS_ON, 1)

            value = bus.read_byte_data(address, 0x12)
            value ^= 0b10000000
            bus.write_byte_data(address, 0x12, value)

            pressCheckList[1] = False
        else:
            pressCheckList[1] = True
    if pin0 == 2:
        if pressCheckList[2]:
            button_pressed(selectedVoice, DELAY_IS_ON, 1)

            value = bus.read_byte_data(address, 0x12)
            value ^= 0b00100000
            bus.write_byte_data(address, 0x12, value)

            pressCheckList[2] = False
        else:
            pressCheckList[2] = True
    if pin0 == 3
        encoderList["STUTTER RELEASE"].voice = selectedVoice
        rotary_turned(encoderList["STUTTER RELEASE"], pin0_state, pin1_state)
    if pin0 == 5:
        encoderList["STUTTER ATTACK"].voice = selectedVoice
        rotary_turned(encoderList["STUTTER ATTACK"], pin0_state, pin1_state)
    if pin0 == 7:
        selectedVoice = 4



def interrupt3A(channel):
#    print("!!!")

    global selectedVoice

    intf = bus.read_byte_data(MCP_ADDR3,0x0E)
    values = bus.read_byte_data(MCP_ADDR3, 0x10)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin
    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1

    if pin0 == 0:
        if ctrl == 0:
            encoderList["P/G0"].param = PITCH
        else:
            encoderList["P/G0"].param = GAIN
        rotary_turned(encoderList["P/G0"], pin0_state, pin1_state)
    if pin0 == 2:
        if ctrl == 0:
            encoderList["P/G1"].param = PITCH
        else:
            encoderList["P/G1"].param = GAIN
        rotary_turned(encoderList["P/G1"], pin0_state, pin1_state)
    if pin0 == 4:
        if ctrl == 0:
            encoderList["P/G2"].param = PITCH
        else:
            encoderList["P/G2"].param = GAIN
        rotary_turned(encoderList["P/G2"], pin0_state, pin1_state)
    if pin0 == 6:
        if ctrl == 0:
            encoderList["P/G3"].param = PITCH
        else:
            encoderList["P/G3"].param = GAIN
        rotary_turned(encoderList["P/G3"], pin0_state, pin1_state)

 

def interrupt3B(channel):
#    print("!!!")

    global selectedVoice

    intf = bus.read_byte_data(MCP_ADDR3,0x0F)
    values = bus.read_byte_data(MCP_ADDR3, 0x11)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin
    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1


    if pin0 == 0:
        if ctrl == 0:
            encoderList["BEND0"].param = BEND
        else:
            encoderList["BEND0"].param = DELAY_AMOUNT
        rotary_turned(encoderList["BEND0"], pin0_state, pin1_state)
    if pin0 == 2:
        if ctrl == 0:
            encoderList["BEND1"].param = BEND
        else:
            encoderList["BEND1"].param = DELAY_AMOUNT
        rotary_turned(encoderList["BEND1"], pin0_state, pin1_state)
    if pin0 == 4:
        if ctrl == 0:
            encoderList["BEND2"].param = BEND
        else:
            encoderList["BEND2"].param = DELAY_AMOUNT
        rotary_turned(encoderList["BEND2"], pin0_state, pin1_state)
    if pin0 == 6:
        if ctrl == 0:
            encoderList["BEND3"].param = BEND
        else:
            encoderList["BEND3"].param = DELAY_AMOUNT
        rotary_turned(encoderList["BEND3"], pin0_state, pin1_state)


def interrupt4A(channel):
 #   print("!!!")

    global selectedVoice

    intf = bus.read_byte_data(MCP_ADDR4,0x0E)
    values = bus.read_byte_data(MCP_ADDR4, 0x10)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin
    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1

    if pin0 == 0:
        button_pressed(3, MUTE, 1) 
    if pin0 == 1:
        button_pressed(2, MUTE, 1) 
    if pin0 == 2:
        button_pressed(1, MUTE, 1) 
    if pin0 == 3:
        button_pressed(0, MUTE, 1) 
    if pin0 == 4:
        selectedVoice = 0
    if pin0 == 5:
        selectedVoice = 1
    if pin0 == 6:
        selectedVoice = 2
    if pin0 == 7:
        selectedVoice = 3


def interrupt4B(channel):
 #   print("!!!")

    global selectedVoice

    intf = bus.read_byte_data(MCP_ADDR4,0x0F)
    values = bus.read_byte_data(MCP_ADDR4, 0x11)
    pin0 = 0
    pin1 = 0
    pin0_state = 0
    pin1_state = 0
    
    for pin in range(8):
        if intf & (1 << pin):
            pin0 = pin

    pin1 = pin0 + 1
    pin0_state = (values >> pin0) & 1
    pin1_state = (values >> pin1) & 1

    if pin0 == 0:
        rotary_turned(encoderList["BEND4"], pin0_state, pin1_state)
    if pin0 == 2:
        if ctrl:
            encoderList["P/G4"].param = GAIN
        else:
            encoderList["P/G4"].param = PITCH           
        rotary_turned(encoderList["P/G4"], pin0_state, pin1_state)
    if pin0 == 4:
        if ctrl:
            ctrl = 0 
        else:
            ctrl = 1








def rotary_turned(e, pin0_state, pin1_state):
        # Read the current state of the rotary encoder's CLK pin
        e.prev_CLK_state = e.CLK_state
        e.CLK_state = pin0_state
        e.DT_state = pin1_state       
        CLK_state = e.CLK_state
        prev_CLK_state = e.prev_CLK_state
        DT_state = e.DT_state
        prev_direction = e.prev_direction
        voice = e.voice
        param = e.param
        global start
        global home
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
            file_path = home / "data.txt"
            with open(file_path, 'r') as file:
                lines = file.readlines()
            lines[0:3] = [str(voice) + "\n", str(param) + "\n", str(dataList[index])]
            
            with open(file_path, 'w') as file:
                file.writelines(lines)
            time.sleep(0.05)
    
def button_pressed(voice, param, positive):
    print("button pressed")
    global dataList
    global ctrl

    index = 31 * voice + param
    if param == 17 or param == 20 or param == 27:
        dataList[index] = (dataList[index] + 1) % 2
    else:
        dataList[index] += 1 * positive
    file_path = home / "data.txt"
    with open(file_path, 'r') as file:
        lines = file.readlines()
    lines[0:3] = [str(voice) + "\n", str(param) + "\n", str(dataList[index])]
    
    with open(file_path, 'w') as file:
        file.writelines(lines)

    print(str(voice) + " " + str(param) + " " + str(dataList[index]))
    

GPIO.add_event_detect(INTA_PIN0, GPIO.FALLING, callback=interrupt0A, bouncetime=1)
GPIO.add_event_detect(INTB_PIN0, GPIO.FALLING, callback=interrupt0B, bouncetime=1)
GPIO.add_event_detect(INTA_PIN1, GPIO.FALLING, callback=interrupt1A, bouncetime=1)
GPIO.add_event_detect(INTB_PIN1, GPIO.FALLING, callback=interrupt1B, bouncetime=1)
GPIO.add_event_detect(INTA_PIN2, GPIO.FALLING, callback=interrupt2A, bouncetime=1)
GPIO.add_event_detect(INTB_PIN2, GPIO.FALLING, callback=interrupt2B, bouncetime=1)
GPIO.add_event_detect(INTA_PIN3, GPIO.FALLING, callback=interrupt3A, bouncetime=1)
GPIO.add_event_detect(INTB_PIN3, GPIO.FALLING, callback=interrupt3B, bouncetime=1)
GPIO.add_event_detect(INTA_PIN4, GPIO.FALLING, callback=interrupt4A, bouncetime=1)
GPIO.add_event_detect(INTB_PIN4, GPIO.FALLING, callback=interrupt4B, bouncetime=1)

#while True:
#    print(GPIO.input(INTA_PIN))
#    time.sleep(0.1)



try:
    while True:
        time.sleep(0.01)

except KeyboardInterrupt:
    GPIO.cleanup()

