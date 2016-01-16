#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
//#include <EEPROMex.h>
//#include <Bounce2.h>


//#define RELAY_OUT 12
//#define LED_OUT 13
//
//#define PLUS_IN 3
//#define MINUS_IN 2



#define TEMP_SENSOR_PIN 7
#define TEMP_ADDR 0
OneWire tempSensorOneWire(TEMP_SENSOR_PIN);
DallasTemperature sensors(&tempSensorOneWire);

#define BACKLIGHT_PIN  7
#define EN_PIN  4
#define RW_PIN  5
#define RS_PIN  6
#define D4_PIN  0
#define D5_PIN  1
#define D6_PIN  2
#define D7_PIN  3
LiquidCrystal_I2C lcd(0x20, EN_PIN, RW_PIN, RS_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);


//Bounce plusBouncer = Bounce();
//Bounce minusBouncer = Bounce();
//
//boolean isRelayOn;
//float targetTemp;


//void saveTemp() ;

void setup(void) {

    lcd.begin(16, 2);
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    lcd.home();
    lcd.print("Hello, ARDUINO ");
    lcd.setCursor(0, 1);
    lcd.print(" WORLD!  ");

    delay(1000);

    sensors.begin();

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

    delay(500);

    sensors.requestTemperatures();
    float currentTemp = sensors.getTempCByIndex(0);

    lcd.home();
    lcd.clear();
    lcd.print(currentTemp);

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
//  digitalWrite(RELAY_OUT, isRelayOn ? HIGH : LOW);
//  digitalWrite(LED_OUT, isRelayOn ? HIGH : LOW);
//
//  display.setCursor(0, 1);
//  display.print(targetTemp);
//
//  display.setCursor(13, 0);
//  display.print(isRelayOn ? "On " : "Off");

}


//void saveTemp() {
//    EEPROM.updateFloat(TEMP_ADDR, targetTemp);
//}
