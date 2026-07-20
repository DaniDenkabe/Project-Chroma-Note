
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
MCP_ADDR3 = 0x23
MCP_ADDR4 = 0x24
MCP_ADDR5 = 0x27

encoderList = [Encoder(4, 0), Encoder(4, 1), Encoder(4, 29), Encoder(4, 4), Encoder(4, 2),
               Encoder(4, 5), Encoder(4, 3), Encoder(4, 28), Encoder(4, 18), Encoder(4, 19),
               Encoder(4, 11), Encoder(4, 12), Encoder(4, 7), Encoder(4, 8), Encoder(4, 16), 
               Encoder(4, 30), Encoder(0, 29), Encoder(1, 29), Encoder(2, 29), Encoder(3, 29),
               Encoder(0, 1), Encoder(1, 1), Encoder(2, 1), Encoder(3, 1), Encoder(4, 10),
               Encoder(4, 9)]
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
bus.write_byte_data(MCP_ADDR4, 0x0D, 0b11111111)

bus.write_byte_data(MCP_ADDR0, 0x00, 0xFF)  # IODIRA = inputs
bus.write_byte_data(MCP_ADDR1, 0x00, 0xFF)  # IODIRA = inputs
bus.write_byte_data(MCP_ADDR2, 0x00, 0xFF)  # IODIRA = inputs
bus.write_byte_data(MCP_ADDR3, 0x00, 0xFF)  # IODIRA = inputs
bus.write_byte_data(MCP_ADDR4, 0x00, 0xFF)  # IODIRA = inputs

bus.write_byte_data(MCP_ADDR0, 0x01, 0xFF)  # IODIRB = inputs
bus.write_byte_data(MCP_ADDR1, 0x01, 0xFF)  # IODIRB = inputs
bus.write_byte_data(MCP_ADDR2, 0x01, 0xFF)  # IODIRB = inputs
bus.write_byte_data(MCP_ADDR3, 0x01, 0xFF)  # IODIRB = inputs
bus.write_byte_data(MCP_ADDR4, 0x01, 0xFF)  # IODIRB = inputs




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


bus.write_byte_data(MCP_ADDR0, 0x05, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR0, 0x09, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR0, 0x11)  # INTCAP

bus.write_byte_data(MCP_ADDR1, 0x05, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR1, 0x09, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR1, 0x11)  # INTCAP

bus.write_byte_data(MCP_ADDR2, 0x05, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR2, 0x09, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR2, 0x11)  # INTCAP

bus.write_byte_data(MCP_ADDR3, 0x05, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR3, 0x09, 0x00)  # INTCONA (interrupt on change)
bus.read_byte_data(MCP_ADDR3, 0x11)  # INTCAP

bus.write_byte_data(MCP_ADDR4, 0x05, 0xFF)  # GPINTENA (enable interrupts)
bus.write_byte_data(MCP_ADDR4, 0x09, 0x00)  # INTCONA (interrupt on change)
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
        encoderList[0].prev_CLK_state = encoderList[0].CLK_state
        encoderList[0].CLK_state = pin0_state
        encoderList[0].DT_state = pin1_state
        rotary_turned(encoderList[0])
    if pin0 == 2:
        encoderList[1].prev_CLK_state = encoderList[1].CLK_state
        encoderList[1].CLK_state = pin0_state
        encoderList[1].DT_state = pin1_state
        rotary_turned(encoderList[1])
    if pin0 == 4:
        encoderList[2].prev_CLK_state = encoderList[2].CLK_state
        encoderList[2].CLK_state = pin0_state
        encoderList[2].DT_state = pin1_state
        rotary_turned(encoderList[2])       
    if pin0 == 6:
        ctrl = (ctrl + 1) % 3
    if pin0 == 7:
        selectedVoice = 4

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
        encoderList[24].voice = selectedVoice
        encoderList[24].prev_CLK_state = encoderList[24].CLK_state
        encoderList[24].CLK_state = pin0_state
        encoderList[24].DT_state = pin1_state
        rotary_turned(encoderList[24])
    if pin0 == 2:
        encoderList[25].voice = selectedVoice
        encoderList[25].prev_CLK_state = encoderList[25].CLK_state
        encoderList[25].CLK_state = pin0_state
        encoderList[25].DT_state = pin1_state
        rotary_turned(encoderList[25])
    if pin0 == 5:
        print("Selected Voice is now 4")
        selectedVoice = 4
    if pin0 == 6:
        print("!!!")

 




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
        encoderList[3].voice = selectedVoice
        encoderList[3].prev_CLK_state = encoderList[3].CLK_state
        encoderList[3].CLK_state = pin0_state
        encoderList[3].DT_state = pin1_state
        rotary_turned(encoderList[3])
    if pin0 == 2:
        encoderList[4].voice = selectedVoice
        encoderList[4].prev_CLK_state = encoderList[4].CLK_state
        encoderList[4].CLK_state = pin0_state
        encoderList[4].DT_state = pin1_state
        rotary_turned(encoderList[4])
    if pin0 == 4:
        encoderList[5].voice = selectedVoice
        encoderList[5].prev_CLK_state = encoderList[5].CLK_state
        encoderList[5].CLK_state = pin0_state
        encoderList[5].DT_state = pin1_state
        rotary_turned(encoderList[5])       
    if pin0 == 6:
        encoderList[6].voice = selectedVoice
        encoderList[6].prev_CLK_state = encoderList[6].CLK_state
        encoderList[6].CLK_state = pin0_state
        encoderList[6].DT_state = pin1_state
        rotary_turned(encoderList[6])    




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
        encoderList[7].voice = selectedVoice
        encoderList[7].prev_CLK_state = encoderList[7].CLK_state
        encoderList[7].CLK_state = pin0_state
        encoderList[7].DT_state = pin1_state
        rotary_turned(encoderList[7])
    if pin0 == 2:
        button_pressed(selectedVoice, 6, 1)
    if pin0 == 3:
        button_pressed(selectedVoice, 6, -1)
    if pin0 >= 4:
        selectedVoice = pin0 - 4
        print("selectedVoice: " + str(selectedVoice))



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
        encoderList[8].voice = selectedVoice
        encoderList[8].prev_CLK_state = encoderList[8].CLK_state
        encoderList[8].CLK_state = pin0_state
        encoderList[8].DT_state = pin1_state
        rotary_turned(encoderList[8])

    if pin0 == 2:
        encoderList[9].voice = selectedVoice
        encoderList[9].prev_CLK_state = encoderList[9].CLK_state
        encoderList[9].CLK_state = pin0_state
        encoderList[9].DT_state = pin1_state
        rotary_turned(encoderList[9])

    if pin0 == 4:
        encoderList[10].voice = selectedVoice
        encoderList[10].prev_CLK_state = encoderList[10].CLK_state
        encoderList[10].CLK_state = pin0_state
        encoderList[10].DT_state = pin1_state
        rotary_turned(encoderList[10])

    if pin0 == 6:
        encoderList[11].voice = selectedVoice
        encoderList[11].prev_CLK_state = encoderList[11].CLK_state
        encoderList[11].CLK_state = pin0_state
        encoderList[11].DT_state = pin1_state
        rotary_turned(encoderList[11])


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
 
    if pin0 == 0:
        encoderList[12].voice = selectedVoice
        encoderList[12].prev_CLK_state = encoderList[12].CLK_state
        encoderList[12].CLK_state = pin0_state
        encoderList[12].DT_state = pin1_state
        rotary_turned(encoderList[12])
    if pin0 == 2:
        encoderList[13].voice = selectedVoice
        encoderList[13].prev_CLK_state = encoderList[13].CLK_state
        encoderList[13].CLK_state = pin0_state
        encoderList[13].DT_state = pin1_state
        rotary_turned(encoderList[13])
    if pin0 == 4:
        encoderList[14].voice = selectedVoice
        encoderList[14].prev_CLK_state = encoderList[14].CLK_state
        encoderList[14].CLK_state = pin0_state
        encoderList[14].DT_state = pin1_state
        rotary_turned(encoderList[14])
    if pin0 == 6:
        encoderList[15].voice = selectedVoice
        encoderList[15].prev_CLK_state = encoderList[15].CLK_state
        encoderList[15].CLK_state = pin0_state
        encoderList[15].DT_state = pin1_state
        rotary_turned(encoderList[15])



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
        button_pressed(selectedVoice, 21, 1)
    if pin0 == 1:
        button_pressed(selectedVoice, 21, -1)
    if pin0 == 2:
        button_pressed(selectedVoice, 22, 1)
    if pin0 == 3:
        button_pressed(selectedVoice, 22, -1)
    if pin0 == 4:
        button_pressed(selectedVoice, 23, 1)
    if pin0 == 5:
        button_pressed(selectedVoice, 23, -1)
    if pin0 == 6:
        button_pressed(selectedVoice, 24, 1)
    if pin0 == 7:
        button_pressed(selectedVoice, 24, -1)

 

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
        button_pressed(selectedVoice, 25, 1)
    if pin0 == 1:
        button_pressed(selectedVoice, 25, -1)
    if pin0 == 2:
        button_pressed(selectedVoice, 26, 1)
    if pin0 == 3:
        button_pressed(selectedVoice, 26, -1)
    if pin0 == 4:
        if pressCheckList[0]:
            button_pressed(selectedVoice, 17, 1)
            pressCheckList[0] = False
        else:
            pressCheckList[0] = True
    if pin0 == 5:
        if pressCheckList[1]:
            button_pressed(selectedVoice, 20, 1)
            pressCheckList[1] = False
        else:
            pressCheckList[1] = True
    if pin0 == 6:
        if pressCheckList[2]:
            button_pressed(selectedVoice, 27, 1)
            pressCheckList[2] = False
        else:
            pressCheckList[2] = True


def interrupt4A(channel):
 #   print("!!!")

    global selectedVoice
    global hallCounter

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

        print("Hall Effect Sensor Activated" + str(hallCounter))
        print("--------------------------")
        print("")
        hallCounter += 1
    if pin0 == 2:

        print("Hall Effect 1")
    if pin0 == 4:

        print("Hall Effect 2 Sensor Activated")
    if pin0 == 6:
        print("Hall Effect 3 Sensor Activated")



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
        if ctrl == 0:
            encoderList[20].param = 0
        elif ctrl == 1:
            encoderList[20].param = 1
        elif ctrl == 2:
            encoderList[20].param = 28
        encoderList[20].prev_CLK_state = encoderList[20].CLK_state
        encoderList[20].CLK_state = pin0_state
        encoderList[20].DT_state = pin1_state
        rotary_turned(encoderList[20])
    if pin0 == 2:
        if ctrl == 0:
            encoderList[21].param = 0
        elif ctrl == 1:
            encoderList[21].param = 1
        elif ctrl == 2:
            encoderList[21].param = 28
        encoderList[21].prev_CLK_state = encoderList[21].CLK_state
        encoderList[21].CLK_state = pin0_state
        encoderList[21].DT_state = pin1_state
        rotary_turned(encoderList[21])
    if pin0 == 4:
        if ctrl == 0:
            encoderList[22].param = 0
        elif ctrl == 1:
            encoderList[22].param = 1
        elif ctrl == 2:
            encoderList[22].param = 28
        encoderList[22].prev_CLK_state = encoderList[22].CLK_state
        encoderList[22].CLK_state = pin0_state
        encoderList[22].DT_state = pin1_state
        rotary_turned(encoderList[22])
    if pin0 == 6:
        if ctrl == 0:
            encoderList[23].param = 0
        elif ctrl == 1:
            encoderList[23].param = 1
        elif ctrl == 2:
            encoderList[23].param = 28
        encoderList[23].prev_CLK_state = encoderList[23].CLK_state
        encoderList[23].CLK_state = pin0_state
        encoderList[23].DT_state = pin1_state
        rotary_turned(encoderList[23])







def rotary_turned(e):
        # Read the current state of the rotary encoder's CLK pin
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

