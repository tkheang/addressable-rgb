#include <FastLED.h>

// number of LEDs per strip
#define NUM_LEDS    34
// number of LED strips
#define NUM_STRIPS  4
// brightness level 0-255
#define BRIGHTNESS  128
// LED type
#define LED_TYPE    WS2811
// color order
#define COLOR_ORDER GRB

CRGB leds[NUM_STRIPS][NUM_LEDS];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
    // power-up safety delay
    delay(2000);
    // set up LED strips
    // digital pins 2, 3, 4, 5 are used to control the LED strips
    FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    currentBlending = LINEARBLEND;
    // reset all LED strips
    for(int x = 0; x < NUM_STRIPS - 1; x++) {
      for(int y = 0; y < NUM_LEDS - 1; y++) {
        leds[x][y] = CRGB::Black;
        FastLED.show();
      }
    }
    Serial.begin(115200);
    delay(1000);
}

void loop() {
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    // play an animation
    RainbowFade(startIndex);
}

void RainbowWheel(uint8_t colorIndex) {
    for( int x = 0; x < NUM_LEDS - 1; x++) {
      leds[0][x] = ColorFromPalette(RainbowColors_p, colorIndex, BRIGHTNESS, currentBlending);
      colorIndex += 3;
    }
    for( int y = NUM_LEDS - 1; y >= 0; y--) {
      leds[1][y] = ColorFromPalette(RainbowColors_p, colorIndex, BRIGHTNESS, currentBlending);
      colorIndex += 3;
    }
    FastLED.show();
    delay(5);
}

void RainbowWave(uint8_t colorIndex) {
    for( int x = 0; x < NUM_LEDS; x++) {
      leds[0][x] = ColorFromPalette(RainbowColors_p, colorIndex, BRIGHTNESS, currentBlending);
      leds[1][x] = ColorFromPalette(RainbowColors_p, colorIndex, BRIGHTNESS, currentBlending);
      colorIndex += 5;
    }
    FastLED.show();
    delay(5);
}

void RainbowFade(uint8_t colorIndex) {
    fill_solid(leds[0], NUM_LEDS, ColorFromPalette(RainbowColors_p, colorIndex, BRIGHTNESS, currentBlending));
    fill_solid(leds[1], NUM_LEDS, ColorFromPalette(RainbowColors_p, colorIndex, BRIGHTNESS, currentBlending));
    colorIndex += 1;
    FastLED.show();
    delay(50);
}

void SingleBreathing() {
    fill_solid(leds[0], NUM_LEDS, CRGB::Green);
    fill_solid(leds[1], NUM_LEDS, CRGB::Green);
    for (int i = 31; i < 127; i++) {
      FastLED.setBrightness(i);
      FastLED.show();
      delay(20);
    }
    for (int i = 127; i >= 31; i--) {
      FastLED.setBrightness(i);
      FastLED.show();
      delay(20);
    }
}

