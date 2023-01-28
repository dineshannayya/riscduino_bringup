from nucleo_api import *
import os
import gpio_config_builder
from flash import flash_mem
from flash import verify_mem
import sys
import pyb
from machine import Pin


config_filename = "gpio_config_def.py"


class Led:

    def __init__(self, pin_name):
        self.led = Pin(pin_name, Pin.OUT)

    def blink(self, short=1, long=0):
        delay_short = 300
        delay_long = 600

        self.led.off()
        for i in range(short):
            self.led.on()
            pyb.delay(delay_short)
            self.led.off()
            pyb.delay(delay_short)

        if long > 0:
            pyb.delay(delay_long)

        for i in range(long):
            self.led.on()
            pyb.delay(delay_long)
            self.led.off()
            pyb.delay(delay_long)

    def on(self):
        self.led.on()

    def off(self):
        self.led.off()

    def toggle(self):
        if self.led.value():
            self.led.off()
        else:
            self.led.on()

# used as an activity indicator
#        - active = flash firmware, checking for IO pulses

led_blue = Led("B7")

# used for program start and completion

led_green = Led("B0")

# red and green are used at program termination
#       - flashing red = chain configuration failure

led_red = Led("B14")


def run_builder(gpio_l, gpio_h):
    return gpio_config_builder.build_config(gpio_h, gpio_l)


def data_flash(test_name, hex_data, first_line=1):
    
    new_hex_file = open(f"{test_name}-tmp.hex", "w")
    new_hex_data = ""
    hex_out = []
    n_bits = hex_data[0]
    
    with open(f"{test_name}.hex", mode='r') as f:
        line = f.readline()
        line = line.strip()
        while line != "":
           if line.startswith("@"):
               if first_line > 0:
                   first_line = first_line - 1
               else:
                   hex_out = [ line.strip() ]
                   break
           line = f.readline()
                    
    count = 0
    for d in hex_data:
        new_hex_data = new_hex_data + " {:02x}".format(d)
        count = count + 1
        if count >= 16:
            hex_out.append(f"{new_hex_data[1:]}")
            count = 0
            new_hex_data = ""

    hex_out.append(f"{new_hex_data[1:]}")
    for i in hex_out:
        new_hex_file.write(f"{i}\n")
    new_hex_file.close()

    flash(f"{test_name}-tmp.hex")


def exec_flash(test, test_name):
    print("*** Flashing Caravel (1)")
    test.apply_reset()
    test.powerup_sequence()
    erase()
    test.flash(f"{test_name}.hex")
    test.powerup_sequence()
    test.release_reset()


def exec_data_flash(test, test_name, config_stream):
    print("\n*** flashing Caravel")
    test.apply_reset()
    test.powerup_sequence()
    erase()
    # test.flash(f"{test_name}.hex")
    flash(f"{test_name}.hex")
    data_flash(test_name, config_stream )
    test.powerup_sequence()
    test.release_reset()



def choose_test(
    test,
    test_name,
    gpio_l,
    gpio_h,
    chain="low",
    high=False
):
    test_result = False
    channel_failed = True
    exec_flash(test, test_name)
    #test.test_name = test_name
    #config_stream = run_builder(gpio_l, gpio_h)
    #exec_data_flash(test, test_name, config_stream)
    #print("**** Running Test for {} !!".format(test.test_name))

    return test_result, channel_failed


def run():
    test = Test(voltage=1.8)
    gpio_l = Gpio()
    gpio_h = Gpio()

    print(" ")
    print("===================================================================")
    print("== Beginning IO configuration test.  Testing LOW IO chain...     ==")
    print("===================================================================")
    print(" ")
    led_green.blink(short=3, long=2)
    exec_flash(test, "config_io_o")

