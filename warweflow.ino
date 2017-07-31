 /***********Notice and Trouble shooting***************
13 1.Connection and Diagram can be found here http://www.dfrobot.com/wiki/i
ndex.php?title=Water_Flow_Sensor_-_1/8%22_SKU:_SEN0216
14 2.This code is tested on Arduino Uno.
 ****************************************************/
 
// This Teensy3 native optimized version requires specific pins
//
#define TFT_SCLK 13  // SCLK can also use pin 14
#define TFT_MOSI 11  // MOSI can also use pin 7
#define TFT_CS   10  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    9  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   8  // RST can use any pin
#define SD_CS     4  // CS for SD card, can use any pin

#include <Adafruit_GFX.h>    // Core graphics library
#include <ST7735_t3.h> // Hardware-specific library
#include <SPI.h>

// Option 1: use any pins but a little slower
ST7735_t3 tft = ST7735_t3(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Option 2: must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
//ST7735_t3 tft = ST7735_t3(cs, dc, rst);
//float p = 3.1415926;


volatile double waterFlow;
volatile double newWaterFlow;


void setup() {
  Serial.begin(9600); //baudrate
  //-----------------------------------------inciando la pantalla-------------------------------------------------------------------------------//
  Serial.println(F("inicializando ST7735"));
  Serial.println("ST7735 Test!"); 
   // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);
  Serial.println("init");
  Serial.println(F("Finalizing Setup")); //enviamos un mensaje de depuracion 
  tft.setRotation(1);
  tft.println(F("Finalizing Setup")); //enviamos un mensaje de depuracion 
  delay(250);
  //------------------------------------------------------------------------------------------------------------------------------------------
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  tft.println(F("Ready to start")); //enviamos un mensaje de depuracion 
  time = millis() - time;
  //------------------------------------------------------------------------------------------------------------------------------------------
  waterFlow = 0;
  attachInterrupt(2, pulse, RISING); //DIGITAL Pin 2: Interrupt 0
}
void loop() {
  Serial.print("waterFlow:");
  Serial.print(waterFlow);
  Serial.println(" L");
  if (waterFlow != newWaterFlow){
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(50, 10);
    tft.setTextColor(ST7735_GREEN);
    tft.setCursor(35, 60);
    tft.setTextSize(1);
    tft.println(waterFlow);
    newWaterFlow = waterFlow;
    delay(500);
  }
}

void pulse() //measure the quantity of square wave
{
  waterFlow += 1.0/1323;
} 
