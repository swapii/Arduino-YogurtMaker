#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <EEPROMex.h>
#include <Bounce2.h>

#define TEMP_SENSOR 11
#define RELAY_OUT 12
#define LED_OUT 13

#define PLUS_IN 3
#define MINUS_IN 2

#define TEMP_ADDR 0

OneWire tempWire(TEMP_SENSOR);

DallasTemperature sensors(&tempWire);

LiquidCrystal display(10, 9, 8, 7, 6, 5, 4);

Bounce plusBouncer = Bounce();
Bounce minusBouncer = Bounce();


boolean isRelayOn;
float targetTemp;


void setup(void) {
  
  while (!EEPROM.isReady()) {
    delay(50);  
  }
  
  targetTemp = EEPROM.readFloat(TEMP_ADDR);
  
  if (isnan(targetTemp)) {
    targetTemp = 40;
    saveTemp();
  }
  
  sensors.begin();

  display.begin(16,2);
  display.clear();
  
  pinMode(LED_OUT, OUTPUT);
  pinMode(RELAY_OUT, OUTPUT);

  pinMode(PLUS_IN, INPUT);
  pinMode(MINUS_IN, INPUT);
  
  digitalWrite(PLUS_IN, HIGH);
  digitalWrite(MINUS_IN, HIGH);
  
  plusBouncer.attach(PLUS_IN);
  plusBouncer.interval(5);
  
  minusBouncer.attach(MINUS_IN);
  minusBouncer.interval(5);

}


void loop(void) {

  sensors.setWaitForConversion(false);  // makes it async
  sensors.requestTemperatures();
  sensors.setWaitForConversion(true);

  float currentTemp = sensors.getTempCByIndex(0);

  if (currentTemp > targetTemp + 0.5) {
    
    isRelayOn = false;
    
  } else {
    
    if (currentTemp < targetTemp) isRelayOn = true;
    
  }
  
  if (plusBouncer.update() && plusBouncer.read() == LOW) {
    targetTemp += 0.1;
    saveTemp();
  }
  
  if (minusBouncer.update() && minusBouncer.read() == LOW) {
    targetTemp -= 0.1;
    saveTemp();
  }
  
  

  digitalWrite(RELAY_OUT, isRelayOn ? HIGH : LOW);
  digitalWrite(LED_OUT, isRelayOn ? HIGH : LOW);


  display.setCursor(0, 0);
  display.print(currentTemp);

  display.setCursor(0, 1);
  display.print(targetTemp);

  display.setCursor(13, 0);
  display.print(isRelayOn ? "On " : "Off");

}


void saveTemp() {
    EEPROM.updateFloat(TEMP_ADDR, targetTemp);
}
