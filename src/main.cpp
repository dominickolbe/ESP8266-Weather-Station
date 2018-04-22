#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>

#define PIN_DHT_Sensor D3
#define PIN_LDR_Sensor A0
#define PIN_SSD1306_RESET D0
#define DHTTYPE DHT22

Adafruit_SSD1306 display(PIN_SSD1306_RESET);
DHT_Unified dht(PIN_DHT_Sensor, DHTTYPE);

// SENSOR VALUES
float brightness = 0;
float temperature = 0;
float humidity = 0;

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

void readSensors() {

  sensors_event_t event;

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  } else {
    temperature = event.temperature;
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    Serial.println("Error reading humidity!");
  } else {
    humidity = event.relative_humidity;
  }

  brightness = (int)(100 - (analogRead(PIN_LDR_Sensor) * 100 / 1024));
}

void displaySensors() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("BRIGHTNESS:  " + (String)brightness + " %");

  display.setCursor(0, 12);
  display.println("TEMPERATURE: " + (String)temperature + " 'C");

  display.setCursor(0, 24);
  display.println("HUMIDITY:    " + (String)humidity + " %");

  display.display();
}

void readSensorsLoop() {
  readSensors();
  Serial.println("");
  Serial.println("BRIGHTNESS: " + (String)brightness + " %");
  Serial.println("TEMPERATURE: " + (String)temperature + " 'C");
  Serial.println("HUMIDITY: " + (String)humidity + " %");
}

void setup() {
  Serial.begin(9600);
  Serial.println("");

  Serial.println("START: setup()");

  // init display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // setup PIN MODES
  pinMode(LED_BUILTIN, OUTPUT);

  // LED_BUILTIN ON
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("splashscreen()");
  splashscreen();

  delay(1000);

  // LED_BUILTIN OFF
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("END: setup()");
}

void loop() {
  readSensorsLoop();
  displaySensors();
  delay(1000);
}
