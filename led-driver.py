#!/usr/bin/env python3
import os
import time
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
    while(True):
        checkForUpdates(strip)
        time.sleep(0.1)

def clearTree(strip, channel):
    for led in range(LED_COUNT):
        changeChannel(strip, led, channel, 0)
    strip.show()

def hexToRGB(hexa):
    rgb = []
    rgb.append(int(hexa[0:2], 16))
    rgb.append(int(hexa[2:4], 16))
    rgb.append(int(hexa[4:6], 16))
    return rgb

def changeChannel(strip, position, channel, brightness):
    #print("position: %d channel: %d brightness: %d" %(position, channel, brightness))
    color = strip.getPixelColor(position)
    color = hexToRGB(format(color, "06x"))
    color[channel] = brightness
    strip.setPixelColorRGB(position, color[0], color[1], color[2])

def checkForUpdates(strip):
    if os.path.exists("./r.txt"):
        changeTree(strip, "./r.txt")
    elif os.path.exists("./g.txt"):
        changeTree(strip, "./g.txt")
    elif os.path.exists("./b.txt"):
        changeTree(strip, "./b.txt")

def changeTree(strip, path):
    if path == "./r.txt":
        pos = 1
    elif path == "./g.txt":
        pos = 0
    else:
        pos = 2
    f = open(path, "r")
    tree = f.readlines()
    f.close()
    os.remove(path)
    clearTree(strip, pos)
    if tree[0].split()[0] == "clear":
        return
    for line in tree:
        #print(line.split()[0])
        #print(line.split()[1])
        changeChannel(strip, positions[line.split()[0]], pos, int(line.split()[1]))
    strip.show()

if __name__ == "__main__":
    main()
