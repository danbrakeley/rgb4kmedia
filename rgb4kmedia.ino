#include <Arduino.h>

/*
 * Media key for rgb4k (from thnikk)
 * 
 * Dan Brakeley
 */

#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>
#include <Keyboard.h>
#include "MediaKeys.h"

// Map from button index to i/o pin number
const byte buttonToPin[] = { 2, 3, 4, 5, 7 };

// Constants
const byte kNumButtons = 5;
const byte kNumTopButtons = 4;
const byte kNumLeds = 4;
const byte kBounceIntervalMs = 8;

// Button state (as of most recent update)
bool pressed[kNumButtons];
bool released[kNumButtons];

// Light strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(kNumLeds, 6, NEO_GRB + NEO_KHZ800);

// Map from button index to debouncer instance
Bounce bounce[kNumButtons];

// colors
uint32_t cOff = strip.Color(0, 0, 0);
uint32_t cDimWhite = strip.Color(64, 64, 64);
uint32_t cWhite = strip.Color(255, 255, 255);

uint32_t cDimRed = strip.Color(128, 0, 0);
uint32_t cDimGreen = strip.Color(0, 128, 0);
uint32_t cDimBlue = strip.Color(0, 0, 128);

uint32_t cRed = strip.Color(255, 0, 0);
uint32_t cGreen = strip.Color(0, 255, 0);
uint32_t cBlue = strip.Color(0, 0, 255);
uint32_t cYellow = strip.Color(255, 255, 64);
uint32_t cCyan = strip.Color(255, 0, 255);
uint32_t cMagenta = strip.Color(0, 255, 255);

////////////////////////////////////////////////////////////
// Main Setup

void setup() {
  // seed from unconnected pin
  randomSeed(analogRead(0));

  // init LEDs
  strip.begin();

  // set input pullup resistors
  for (byte i = 0; i < kNumButtons; i++) {
    pinMode(buttonToPin[i], INPUT_PULLUP);
  }

  // bounce initializtion
  for (byte i = 0; i < kNumButtons; i++) {
    bounce[i].attach(buttonToPin[i]);
    bounce[i].interval(kBounceIntervalMs);
  }

  // init debug output
#ifdef DEBUG
  Serial.begin(9600);
#endif

  introAnimation();
}

////////////////////////////////////////////////////////////
// Main Loop

void loop() {
  updateButtonState();
  handleButtons();
}

////////////////////////////////////////////////////////////
// Button Helpers

void updateButtonState() {
  for (byte i = 0; i < kNumButtons; i++) {
    pressed[i] = false;
    released[i] = false;
    if (bounce[i].update()) {
      if (bounce[i].read()) {
        released[i] = true;
      } else {
        pressed[i] = true;
      }
    }
  }
}

void handleButtons(){
  if (pressed[0]) {
    MediaKeys.press(MK_PLAYPAUSE);
    setButton(0, cYellow);
  } else if (released[0]) {
    MediaKeys.release(MK_PLAYPAUSE);
    setButton(0, cOff);
  }

  if (pressed[1]) {
    MediaKeys.press(MK_VOL_UP);
    setButton(1, cRed);
  } else if (released[1]) {
    MediaKeys.release(MK_VOL_UP);
    setButton(1, cOff);
  }

  if (pressed[2]) {
    MediaKeys.press(MK_VOL_DOWN);
    setButton(2, cMagenta);
  } else if (released[2]) {
    MediaKeys.release(MK_VOL_DOWN);
    setButton(2, cOff);
  }

  if (pressed[3]) {
    MediaKeys.press(MK_NEXT);
    setButton(3, cBlue);
  } else if (released[3]) {
    MediaKeys.release(MK_NEXT);
    setButton(3, cOff);
  }

  if (pressed[4]) {
    MediaKeys.press(MK_PREV);
    setButton(3, cGreen);
  } else if (released[4]) {
    MediaKeys.release(MK_PREV);
    setButton(3, cOff);
  }
}

////////////////////////////////////////////////////////////
// LED Helpers

void setButton(u8 b, uint32_t c) {
  strip.setPixelColor(b, c);
  strip.show();
}

void setStrip(uint32_t c0, uint32_t c1, uint32_t c2, uint32_t c3) {
  strip.setPixelColor(0, c0);
  strip.setPixelColor(1, c1);
  strip.setPixelColor(2, c2);
  strip.setPixelColor(3, c3);
  strip.show();
}

void introAnimation() {
  animateDown(cWhite, cDimWhite);
  animateUp(cWhite, cDimWhite);
}

void animateDown(uint32_t cBright, uint32_t cDim) {
  setStrip(cBright, cOff, cOff, cOff);
  delay(50);
  setStrip(cDim, cBright, cOff, cOff);
  delay(50);
  setStrip(cOff, cBright, cOff, cOff);
  delay(10);
  setStrip(cOff, cDim, cBright, cOff);
  delay(50);
  setStrip(cOff, cOff, cBright, cOff);
  delay(30);
  setStrip(cOff, cOff, cDim, cBright);
  delay(50);
  setStrip(cOff, cOff, cOff, cBright);
  delay(70);
  setStrip(cOff, cOff, cOff, cDim);
  delay(50);
  setStrip(cOff, cOff, cOff, cOff);
}

void animateUp(uint32_t cBright, uint32_t cDim) {
  setStrip(cOff, cOff, cOff, cBright);
  delay(50);
  setStrip(cOff, cOff, cBright, cDim);
  delay(50);
  setStrip(cOff, cOff, cBright, cOff);
  delay(10);
  setStrip(cOff, cBright, cDim, cOff);
  delay(50);
  setStrip(cOff, cBright, cOff, cOff);
  delay(30);
  setStrip(cBright, cDim, cOff, cOff);
  delay(50);
  setStrip(cBright, cOff, cOff, cOff);
  delay(70);
  setStrip(cDim, cOff, cOff, cOff);
  delay(50);
  setStrip(cOff, cOff, cOff, cOff);
}
