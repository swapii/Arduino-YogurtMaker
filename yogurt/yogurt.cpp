#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <AnalogButtons.h>
//#include <EEPROMex.h>


#define TEMP_SENSOR_PIN 7
#define LCD_BACKLIGHT_PIN  7
#define LCD_EN_PIN  4
#define LCD_RW_PIN  5
#define LCD_RS_PIN  6
#define LCD_D4_PIN  0
#define LCD_D5_PIN  1
#define LCD_D6_PIN  2
#define LCD_D7_PIN  3
#define BUTTONS_PIN A0


OneWire tempSensorOneWire(TEMP_SENSOR_PIN);

DallasTemperature sensors(&tempSensorOneWire);

LiquidCrystal_I2C lcd(0x20, LCD_EN_PIN, LCD_RW_PIN, LCD_RS_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

AnalogButtons analogButtons = AnalogButtons(BUTTONS_PIN, INPUT, 1, 150);

boolean needRedrawScreen = true;
long currentTempUpdatedAt;
float currentTemp;
float targetTemp = 40;

void targetTempDecrement();
void targetTempIncrement();

void setup(void) {

    lcd.begin(16, 2);
    lcd.setBacklightPin(LCD_BACKLIGHT_PIN, POSITIVE);
    lcd.home();
    lcd.print("Hello, ARDUINO ");
    lcd.setCursor(0, 1);
    lcd.print(" WORLD!  ");

    delay(1000);

    lcd.home();
    lcd.clear();

    sensors.begin();

    analogButtons.add(Button(490, &targetTempDecrement));
    analogButtons.add(Button(994, &targetTempIncrement));

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

}


void loop(void) {

    long currentMillis = millis();
    if (currentMillis - currentTempUpdatedAt > 2000) {
        sensors.requestTemperatures();
        currentTemp = sensors.getTempCByIndex(0);
        currentTempUpdatedAt = millis();
        needRedrawScreen = true;
    }

    if (needRedrawScreen) {

        lcd.setCursor(0, 0);
        lcd.print(currentTemp);

        lcd.setCursor(0, 1);
        lcd.print(targetTemp);

        needRedrawScreen = false;
    }

    analogButtons.check();

}

void targetTempIncrement() {
    targetTemp += 0.5;
    needRedrawScreen = true;
}

void targetTempDecrement() {
    targetTemp -= 0.5;
    needRedrawScreen = true;
}

//void saveTemp() {
//    EEPROM.updateFloat(TEMP_ADDR, targetTemp);
//}
