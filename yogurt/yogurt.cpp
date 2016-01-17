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


enum State {
    READY, WORK
};


static const int EEPROM_TARGET_TEMP_ADDR = 0;

static const float TARGET_TEMP_DEFAULT = 40;
static const float TARGET_TEMP_MIN = 0;
static const float TARGET_TEMP_MAX = 75;


OneWire tempSensorOneWire(TEMP_SENSOR_PIN);

DallasTemperature sensors(&tempSensorOneWire);

LiquidCrystal_I2C lcd(0x20, LCD_EN_PIN, LCD_RW_PIN, LCD_RS_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

AnalogButtons analogButtons = AnalogButtons(BUTTONS_PIN, INPUT, 1, 50);


bool needRedrawScreen;

long currentTempUpdatedAt;
float currentTemp;

long targetTempUpdatedAt;
float targetTemp;

long remainTimeUpdatedAt;
int remainTimeSeconds;

State state = READY;


void saveTargetTemp();
void setTargetTemp(float newValue);
void setRemainTime(int newValue);
String remainTimeFormatted();

void targetTempDecrement();
void targetTempIncrement();

void remainTimeDecrement();
void remainTimeIncrement();

void start();
void stop();


void setup(void) {

    lcd.begin(16, 2);
    lcd.setBacklightPin(LCD_BACKLIGHT_PIN, POSITIVE);
    lcd.home();
    lcd.print("Yogurt Maker");
    lcd.setCursor(0, 1);
    lcd.print("1.0.0");

    delay(2000);

    sensors.begin();

    analogButtons.add(Button(170, &targetTempDecrement));
    analogButtons.add(Button(340, &targetTempIncrement));

    analogButtons.add(Button(500, &remainTimeDecrement));
    analogButtons.add(Button(670, &remainTimeIncrement));

    analogButtons.add(Button(835, &stop));
    analogButtons.add(Button(1010, &start));

    while (!EEPROM.isReady()) {
        delay(10);
    }

    targetTemp = EEPROM.readFloat(EEPROM_TARGET_TEMP_ADDR);

    if (isnan(targetTemp) || targetTemp < TARGET_TEMP_MIN || targetTemp > TARGET_TEMP_MAX) {
        setTargetTemp(TARGET_TEMP_DEFAULT);
    }

    int targetTempModulus = int(targetTemp * 10) % 5;
    if (targetTempModulus != 0) {
        setTargetTemp(TARGET_TEMP_DEFAULT);
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

    if (currentMillis - remainTimeUpdatedAt > 1000 * 30) {
        //TODO Save remain time to EEPROM
    }

    if (needRedrawScreen) {

        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print(currentTemp, 1);

        lcd.setCursor(0, 1);
        lcd.print(targetTemp, 1);

        lcd.setCursor(9, 1);
        lcd.print(remainTimeFormatted());

        lcd.setCursor(11, 0);
        lcd.print(state == READY ? "Ready" : " Work");

        needRedrawScreen = false;
    }

    if (targetTempUpdatedAt > 0 && currentMillis - targetTempUpdatedAt > 5000) {
        saveTargetTemp();
        targetTempUpdatedAt = 0;
    }

    analogButtons.check();

}

void targetTempIncrement() {

    if (targetTemp >= TARGET_TEMP_MAX) {
        return;
    }

    setTargetTemp(targetTemp + 0.5);

}

void targetTempDecrement() {

    if (targetTemp <= TARGET_TEMP_MIN) {
        return;
    }

    setTargetTemp(targetTemp - 0.5);

}

void remainTimeDecrement() {
    setRemainTime(remainTimeSeconds - 60 * 30);
}

void remainTimeIncrement() {
    setRemainTime(remainTimeSeconds + 60 * 30);
}

void stop() {
    state = READY;
    needRedrawScreen = true;
}

void start() {
    state = WORK;
    needRedrawScreen = true;
}

void setTargetTemp(float newValue) {
    targetTemp = newValue;
    targetTempUpdatedAt = millis();
    needRedrawScreen = true;
}

void setRemainTime(int newValue) {
    remainTimeSeconds = newValue;
    remainTimeUpdatedAt = millis();
    needRedrawScreen = true;
}

String remainTimeFormatted() {

    int hours = remainTimeSeconds / 60 / 60;
    int minutes = remainTimeSeconds / 60 - hours * 60;
    int seconds = remainTimeSeconds - hours * 60 * 60 - minutes * 60;

    char resultString[8];
    sprintf(resultString, "%d:%02d:%02d", hours, minutes, seconds);

    return String(resultString);
}

void saveTargetTemp() {
    EEPROM.updateFloat(EEPROM_TARGET_TEMP_ADDR, targetTemp);
}
