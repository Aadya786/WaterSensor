#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int sensorPin = 32;
 
const int DRY_VALUE = 3300;
const int WET_VALUE = 1100;

void setup() {
  Serial.begin(115200);
  Wire.begin(25, 26);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed!"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int rawMoisture = analogRead(sensorPin);


  int moisturePercent = map(rawMoisture, DRY_VALUE, WET_VALUE, 0, 100);

  moisturePercent = constrain(moisturePercent, 0, 100);

  display.clearDisplay();

  display.setTextSize(1);            
  display.setCursor(0, 0);          
  display.println("SOIL MOISTURE");
  display.println("---------------------");
 
  display.setTextSize(3);
  display.setCursor(10, 20);
  display.print(moisturePercent);
  display.print("%");

  display.setTextSize(1);
  display.setCursor(0, 54);

  if (moisturePercent < 30) {
    display.print("Status: DRY (WATER ME!)");
  }
  else if (moisturePercent>= 30 && moisturePercent <= 75) {
    display.print("Status: Moist (Good)");
  }
  else {
    display.print("Status:WET (Perfect)");
  }

  display.display();
  delay(1000);
}
