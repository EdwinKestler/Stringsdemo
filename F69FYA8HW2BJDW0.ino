
/* 
 |------------------------------------------------------------------|
 |                    Arduino project                               |
 |                                                                  |
 |         Scrolling Text on ADAFRUIT TFT Arduino Shield            |
 |                                                                  |
 |                                                                  |
 |                                                                  |
 |     sketch uses Adafruit libraries - for more information-       |
 | http://learn.adafruit.com/adafruit-gfx-graphics-library?view=all |
 |                                                                  |
 |                                                                  |
 |                                                                  |
 |           a Renfrew Arduino 2014 project - public domain         |
 |            (scroll routine thanks to Andrew Wendt)               |
 |__________________________________________________________________|
 
 */
// libraries 
#include <Adafruit_GFX.h>    // Core graphics library
#include <ST7735_t3.h> // Hardware-specific library
#include <SPI.h>

// pin definitions
// This Teensy3 native optimized version requires specific pins
//
#define TFT_SCLK 13  // SCLK can also use pin 14
#define TFT_MOSI 11  // MOSI can also use pin 7
#define TFT_CS   10  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    9  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   8  // RST can use any pin
#define SD_CS     4  // CS for SD card, can use any pin

ST7735_t3 tft = ST7735_t3(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

const int NUMBER_OF_ELEMENTS = 10;
const int MAX_SIZE = 20;

char descriptions [NUMBER_OF_ELEMENTS] [MAX_SIZE] = { 
 { " Furnace on " }, 
 { " Furnace off " }, 
 { " Set clock " }, 
 { " Pump on " }, 
 { " Pump off " }, 
 { " Password: " }, 
 { " Accepted " }, 
 { " Rejected " }, 
 { " Fault " }, 
 { " Service rqd " }, 
 };

void setup()
{
  Serial.begin (115200);
  Serial.println ();
  
  pinMode(SD_CS, INPUT_PULLUP);  // don't touch the SD card
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_CYAN);
  tft.fillScreen(ST7735_BLUE);
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  // White on black
  tft.setTextWrap(false);  // Don't wrap text to next line
  tft.setTextSize(5);  // large letters
  tft.setRotation(1); // horizontal display
}
String text ="";
void loop()
{
  for (int i = 0; i < NUMBER_OF_ELEMENTS; i++){
     text = descriptions [i];
   
    //Serial.println (descriptions [i]);
   
  //String text = " . .  Text scrolling on Adafruit TFT shield . ."; // sample text
  const int width = 18;  // width of the marquee display (in characters)

  // Loop once through the string
  for (unsigned int offset = 0; offset < text.length(); offset++)
  {

    // Construct the string to display for this iteration
    String t = "";
    for (int i = 0; i < width; i++)
      t += text.charAt((offset + i) % text.length());
      
    // Print  the string for this iteration
    tft.setCursor(0, tft.height()/2-10);  // display will be halfway down screen
    tft.print(t);

    // Short delay so the text doesn't move too fast
    delay(200);
  }
  }
}


