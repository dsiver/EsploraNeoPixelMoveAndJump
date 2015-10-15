/*
 * NeoPixel Move and Jump
 * Board: Arduino Esplora
 *
 * David Siver
 * CS 4985
 * Fall 2015
 */
#include <Esplora.h>
#include <Adafruit_NeoPixel.h>

#define DEBUG 1
#define DELAY 20
#define BAUD_RATE 9600
#define NEOPIXEL_NUM_PIXELS 16
#define NEOPIXEL_PIN_NUMBER 7
#define NEOPIXEL_BRIGHTNESS 20
#define NO_PIXEL -1

int pixelNumber, oldPixelNumber;
int upState, oldUpState;
int downState, oldDownState;
int leftState, oldLeftState;
int rightState, oldRightState;

Adafruit_NeoPixel neoPixel;

void setup() {
  upState = 0;
  downState = 0;
  leftState = 0;
  rightState = 0;
  oldUpState = 0;
  oldDownState = 0;
  oldLeftState = 0;
  oldRightState = 0;
  pixelNumber = -1;
  oldPixelNumber = pixelNumber;
  Serial.begin(BAUD_RATE);
  neoPixel = Adafruit_NeoPixel(NEOPIXEL_NUM_PIXELS, NEOPIXEL_PIN_NUMBER, NEO_GRB + NEO_KHZ800);
  neoPixel.begin();
  neoPixel.show();
  pinMode(NEOPIXEL_PIN_NUMBER, OUTPUT);
}

void loop() {
  controlNeoPixelWithButtons();
  delay(DELAY);
}

void controlNeoPixelWithButtons() {
  upState = Esplora.readButton(SWITCH_UP);
  downState = Esplora.readButton(SWITCH_DOWN);
  leftState = Esplora.readButton(SWITCH_LEFT);
  rightState = Esplora.readButton(SWITCH_RIGHT);
  if (upState == LOW) {
    if (oldUpState != upState) {
      pixelNumber++;
      if (pixelNumber == neoPixel.numPixels()) {
        pixelNumber = 0;
      }
    }
  }
  else if (downState == LOW) {
    if (oldDownState != downState) {
      pixelNumber--;
      if (pixelNumber < 0) {
        pixelNumber = neoPixel.numPixels() - 1;
      }
    }
  }
  else if (leftState == LOW) {
    if (oldLeftState != leftState) {
      int newPixel = pixelNumber - 8;
      if (newPixel < 0) {
        newPixel += 16;
      }
      pixelNumber = newPixel;
    }
  }
  else if (rightState == LOW) {
    if (oldRightState != rightState) {
      int newPixel = pixelNumber + 8;
      if (newPixel > neoPixel.numPixels() - 1) {
        newPixel -= 16;
      }
      pixelNumber = newPixel;
    }
  }
  neoPixel.setPixelColor(pixelNumber, neoPixel.Color(0, NEOPIXEL_BRIGHTNESS, 0));
  neoPixel.show();
  oldUpState = upState;
  oldDownState = downState;
  oldLeftState = leftState;
  oldRightState = rightState;
  neoPixel.setPixelColor(oldPixelNumber, neoPixel.Color(0, 0, 0));
  oldPixelNumber = pixelNumber;
}
