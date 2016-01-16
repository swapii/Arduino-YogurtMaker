#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <AnalogButtons.h>
#include <EEPROMex.h>


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


static const int EEPROM_TARGET_TEMP_ADDR = 0;

static const float TARGET_TEMP_DEFAULT = 40;
static const float TARGET_TEMP_MIN = 0;
static const float TARGET_TEMP_MAX = 75;


OneWire tempSensorOneWire(TEMP_SENSOR_PIN);

DallasTemperature sensors(&tempSensorOneWire);

LiquidCrystal_I2C lcd(0x20, LCD_EN_PIN, LCD_RW_PIN, LCD_RS_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

AnalogButtons analogButtons = AnalogButtons(BUTTONS_PIN, INPUT, 1, 150);

bool needRedrawScreen;

long currentTempUpdatedAt;
float currentTemp;

bool needSaveTargetTemp;
float targetTemp;

void saveTargetTemp();
void targetTempDecrement();
void targetTempIncrement();

void setup(void) {

    lcd.begin(16, 2);
    lcd.setBacklightPin(LCD_BACKLIGHT_PIN, POSITIVE);
    lcd.home();
    lcd.print("Yogurt Maker");
    lcd.setCursor(0, 1);
    lcd.print("1.0.0");

    delay(2000);

    sensors.begin();

    analogButtons.add(Button(490, &targetTempDecrement));
    analogButtons.add(Button(994, &targetTempIncrement));

    while (!EEPROM.isReady()) {
        delay(10);
    }

    targetTemp = EEPROM.readFloat(EEPROM_TARGET_TEMP_ADDR);

    if (isnan(targetTemp) || targetTemp < TARGET_TEMP_MIN || targetTemp > TARGET_TEMP_MAX) {
        targetTemp = TARGET_TEMP_DEFAULT;
        needSaveTargetTemp;
    }

    int targetTempModulus = int(targetTemp * 10) % 5;
    if (targetTempModulus != 0) {
        targetTemp = TARGET_TEMP_DEFAULT;
        needSaveTargetTemp;
    }

    lcd.clear();

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
        lcd.print(currentTemp, 1);

        lcd.setCursor(0, 1);
        lcd.print(targetTemp, 1);

        needRedrawScreen = false;
    }

    if (needSaveTargetTemp) {
        saveTargetTemp();
        needSaveTargetTemp = false;
    }

    analogButtons.check();

}

void targetTempIncrement() {

    if (targetTemp >= TARGET_TEMP_MAX) {
        return;
    }

    targetTemp += 0.5;
    needSaveTargetTemp = true;
    needRedrawScreen = true;

}

void targetTempDecrement() {

    if (targetTemp <= TARGET_TEMP_MIN) {
        return;
    }

    targetTemp -= 0.5;
    needSaveTargetTemp = true;
    needRedrawScreen = true;

}

void saveTargetTemp() {
    EEPROM.updateFloat(EEPROM_TARGET_TEMP_ADDR, targetTemp);
}
