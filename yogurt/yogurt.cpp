#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
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

#define BACKLIGHT_PIN  7
#define En_pin  4
#define Rw_pin  5
#define Rs_pin  6
#define D4_pin  0
#define D5_pin  1
#define D6_pin  2
#define D7_pin  3
LiquidCrystal_I2C lcd(0x20, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);


Bounce plusBouncer = Bounce();
Bounce minusBouncer = Bounce();

boolean isRelayOn;
float targetTemp;


void saveTemp() ;

int counter;

void setup(void) {

    // Switch on the backlight
//    pinMode ( BACKLIGHT_PIN, OUTPUT );
//    digitalWrite ( BACKLIGHT_PIN, HIGH );
//
//    lcd.setBacklightPin(BACKLIGHT_PIN,NEGATIVE);

    lcd.begin(16, 2);
    lcd.home();                   // go home
    lcd.print("Hello, ARDUINO ");
    lcd.setCursor ( 0, 1 );        // go to the next line
    lcd.print (" WORLD!  ");

    delay(1000);
    lcd.setBacklight(0);
    delay(1000);
    lcd.setBacklight(1);

//  while (!EEPROM.isReady()) {
//    delay(50);
//  }
//
//  targetTemp = EEPROM.readFloat(TEMP_ADDR);
//
//  if (isnan(targetTemp)) {
//    targetTemp = 40;
//    saveTemp();
//  }
//
//  sensors.begin();
//
//  display.begin(16,2);
//  display.clear();
//
//  pinMode(LED_OUT, OUTPUT);
//  pinMode(RELAY_OUT, OUTPUT);
//
//  pinMode(PLUS_IN, INPUT);
//  pinMode(MINUS_IN, INPUT);
//
//  digitalWrite(PLUS_IN, HIGH);
//  digitalWrite(MINUS_IN, HIGH);
//
//  plusBouncer.attach(PLUS_IN);
//  plusBouncer.interval(5);
//
//  minusBouncer.attach(MINUS_IN);
//  minusBouncer.interval(5);

}


void loop(void) {

    counter++;

    delay(1000);

    lcd.home();
    lcd.clear();
    lcd.print(counter);

//  sensors.setWaitForConversion(false);  // makes it async
//  sensors.requestTemperatures();
//  sensors.setWaitForConversion(true);
//
//  float currentTemp = sensors.getTempCByIndex(0);
//
//  if (currentTemp > targetTemp + 0.5) {
//
//    isRelayOn = false;
//
//  } else {
//
//    if (currentTemp < targetTemp) isRelayOn = true;
//
//  }
//
//  if (plusBouncer.update() && plusBouncer.read() == LOW) {
//    targetTemp += 0.1;
//    saveTemp();
//  }
//
//  if (minusBouncer.update() && minusBouncer.read() == LOW) {
//    targetTemp -= 0.1;
//    saveTemp();
//  }
//
//
//
//  digitalWrite(RELAY_OUT, isRelayOn ? HIGH : LOW);
//  digitalWrite(LED_OUT, isRelayOn ? HIGH : LOW);
//
//
//  display.setCursor(0, 0);
//  display.print(currentTemp);
//
//  display.setCursor(0, 1);
//  display.print(targetTemp);
//
//  display.setCursor(13, 0);
//  display.print(isRelayOn ? "On " : "Off");

}


void saveTemp() {
    EEPROM.updateFloat(TEMP_ADDR, targetTemp);
}
