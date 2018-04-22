#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

Adafruit_SSD1306 display(16); // D0

void turnDisplay(bool state) {
  if (state) {
    display.ssd1306_command(SSD1306_DISPLAYON);
  } else {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
  }
}

void splashscreen() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(2);

  display.setCursor(22, 15);
  display.println("Weather");

  display.setCursor(22, 40);
  display.println("Station");

  display.display();
}

void setup() {
  Serial.begin(9600);
  Serial.println("");

  Serial.println("START: setup()");

  // init display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  Serial.println("splashscreen()");
  splashscreen();

  Serial.println("END: setup()");
}

void loop() {
}
