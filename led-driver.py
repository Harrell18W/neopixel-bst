#!/usr/bin/env python3
import os
from neopixel import *

# LED strip configuration
LED_COUNT   = 31 # number of LEDS
LED_PIN     = 18 # GPIO, must be PWM
LED_FREQ_HZ = 800000 # god knows what this other stuff is, probably some stupid nerd stuff
LED_DMA     = 5
LED_INVERT  = False

# define dictionary for converting position codes to strip positions
positions = {
    "root": 0,
    "l":    22,
    "r":    1,
    "ll":   21,
    "lr":   30,
    "rl":   23,
    "rr":   2,
    "lll":  20,
    "llr":  29,
    "lrl":  28,
    "lrr":  27,
    "rll":  26,
    "rlr":  25,
    "rrl":  24,
    "rrr":  3,
    "llll": 19,
    "lllr": 18,
    "llrl": 17,
    "llrr": 16,
    "lrll": 15,
    "lrlr": 14,
    "lrrl": 13,
    "lrrr": 12,
    "rlll": 11,
    "rllr": 10,
    "rlrl": 9,
    "rlrr": 8,
    "rrll": 7,
    "rrlr": 6,
    "rrrl": 5,
    "rrrr": 4
}

def main():
    # create NeoPixel strip
    strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT)
    strip.begin()
    strip.setPixelColor(0, 1, 2 , 3)
    test(strip, "r")

def clearTree(strip, channel):
    for led in range(LED_COUNT):
        strip.setPixelColor(led, 0, 0, 0)
    strip.show()

def checkForUpdates():
    if os.path.exists("./r.txt"):
        changeTree("./r.txt")
    elif os.path.exists("./g.txt")
        changeTree("./g.txt")
    elif os.path.exists("./b.txt")
        changeTree("./b.txt")

def changeTree(path):
    if path == "./r.txt":
        pos = 0
    elif path == "./g.txt":
        pos = 1
    else:
        pos = 2
    f = open(path, "r")
    tree = f.readlines()
    for line in tree:

def test(strip, channel):
    for led in range(LED_COUNT):
        color = strip.getPixelColor(0)[0]
        print(color)