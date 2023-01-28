from nucleo_api import *
import os
import gpio_config_builder
from flash import flash_mem
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


def exec_flash(test, test_name):
    print("*** Flashing Caravel (1)")
    test.apply_reset()
    test.powerup_sequence()
    erase()
    flash(f"{test_name}.hex")
    test.powerup_sequence()
    test.release_reset()


def run():
    test = Test()

    print(" ")
    print("===================================================================")
    print("== Beginning YIFIVE Boot test...                                 ==")
    print("===================================================================")
    print(" ")
    led_green.blink(short=3, long=2)
    exec_flash(test,  "config_io_o")
    led_green.blink(short=3, long=4)

