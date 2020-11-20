#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // width in pixels
#define SCREEN_HEIGHT 32 // height in pixels

// ARDUINO PINOUT
// A0 -> Moisture Sensor Analog
// A1 -> Sunlight Sensor Analog
// A4 -> OLED SDA pin
// A5 -> OLED SCL pin

// Declaration section for SSD1306 display
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Declaration section for FC-28 moisture sensor
#define moisture_sensor_pin A0
int moisture_value;

// Declaration section for LDR light sensor module
#define sunlight_sensor_pin A1
int sunlight_value;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  //display.display();
  //delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}

void loop() {
  moisture_value = analogRead(moisture_sensor_pin);
  sunlight_value = analogRead(sunlight_sensor_pin);
  displayvalues(moisture_value);
  delay(28000); // wait approx. 30seconds between readings
}

void displayvalues(int moisture_value) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  //MOISTURE OUTPUT
  //Serial
  Serial.print("Detected Value: ");
  Serial.println(moisture_value);
  moisture_value = map(moisture_value, 1023, 280, 0 , 100);
  //OLED
  display.print("Moisture: ");
  display.print(moisture_value);
  display.println("%");

  //LIGHTING OUTPUT
  //Serial
  Serial.print("Detected Value: ");
  Serial.println(sunlight_value);
  sunlight_value = map(sunlight_value, 900, 20, 0 , 100);
  //OLED
  display.print("Sunlight: ");
  display.print(sunlight_value);
  display.print("%");

  display.display();
}
