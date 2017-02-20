#include <FastLED.h>

#define LED_PIN     1
#define NUM_LEDS    14
#define BRIGHTNESS  100
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 10

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

// Gradient palette "otis_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/otis.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( otis_gp ) {  // main animation
    0,  26,  1, 89,
  127,  17,193,  0,
  216,   0, 34, 98,
  255,   0, 34, 98};

// Gradient palette "rainbow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/rainbow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 48 bytes of program space.

DEFINE_GRADIENT_PALETTE( rainbow_gp ) { // startup demo?
    0, 126,  1,142,
   25, 171,  1, 26,
   48, 224,  9,  1,
   71, 237,138,  1,
   94,  52,173,  1,
  117,   1,201,  1,
  140,   1,211, 54,
  163,   1,124,168,
  186,   1,  8,149,
  209,  12,  1,151,
  232,  12,  1,151,
  255, 171,  1,190};

// Gradient palette "blackhorse_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/blackhorse.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( blackhorse_gp ) {   // startup demo?
    0,   8, 30,  1,
   53,  29, 99,237,
  112,   1,  1, 14,
  168,  21,  5, 21,
  219,   1,  5,  2,
  255,   8, 30,  1};

DEFINE_GRADIENT_PALETTE( halloween_gp ) { // Unused but cool
    0, 173, 53,  1,
  127,   0,  0,  0,
  191, 173, 53,  1,
  255, 173, 53,  1};

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    currentBlending = LINEARBLEND;
    
    currentPalette = blackhorse_gp;

    // initial demo
    for (int i=0;i<1000;i++) {
      FillLEDsFromPaletteColors(i);
      FastLED.show();
      FastLED.delay(10);
    }
    
    currentPalette = otis_gp;
    
}


void loop() {
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors(startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

