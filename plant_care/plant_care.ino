// Author: William Stein

// ARDUINO PINOUT
// A0 -> Moisture Sensor Analog
// A7 -> Sunlight Sensor Analog
// A4 -> OLED SDA pin
// A5 -> OLED SCL pin


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Declaration section for SSD1306 display
#define OLED_RESET 4
#define SCREEN_WIDTH 128            // OLED display width in pixels
#define SCREEN_HEIGHT 32            // OLED display height in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Declaration section for FC-28 moisture sensor
#define moisture_sensor_pin A0
int moisture_value;
int moisture_status;

// Declaration section for LDR light sensor module
#define sunlight_sensor_pin A7
int sunlight_value;

void setup() {
  pinMode(5, OUTPUT);            //sets up D1 pin for the moisture on/off switch
  //analogReference(EXTERNAL);   // use AREF for reference voltage of the main power supply
  
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {   // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));  // Print failure notice to Serial
    for(;;);                                         // Don't proceed, loop forever
  }
  display.clearDisplay();
}

void loop() {
  //digitalWrite(5, HIGH);      // turn on moisture sensor
  delay(2000);
  moisture_value = analogRead(moisture_sensor_pin);
  //digitalWrite(5, LOW);       // turn off moisture sensor

  sunlight_value = analogRead(sunlight_sensor_pin);
  
  displayvalues(moisture_value, sunlight_value);
  //delay(28000);             // wait approx. 30 seconds between readings
  delay(1000);                //this line is for testing
}

void displayvalues(int moisture_value, int sunlight_value) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  //MOISTURE OUTPUT
  //Serial
  Serial.print("Detected Moisture Value: ");
  Serial.println(moisture_value);
  moisture_value = map(moisture_value, 1023, 0, 0 , 100);
  //OLED
  display.print("Moisture: ");
  display.print(moisture_value);
  display.println("%");

  delay(500);
  
  //LIGHTING OUTPUT
  //Serial
  Serial.print("Detected Sunlight Value: ");
  Serial.println(sunlight_value);
  sunlight_value = map(sunlight_value, 0, 1023, 0 , 100);
  //OLED
  display.print("Sunlight: ");
  display.print(sunlight_value);
  display.print("%");

  display.display();
}
