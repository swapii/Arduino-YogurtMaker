#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <AnalogButtons.h>


#define LCD_BACKLIGHT_PIN  7
#define LCD_EN_PIN  4
#define LCD_RW_PIN  5
#define LCD_RS_PIN  6
#define LCD_D4_PIN  0
#define LCD_D5_PIN  1
#define LCD_D6_PIN  2
#define LCD_D7_PIN  3
#define BUTTONS_PIN A0


LiquidCrystal_I2C lcd(0x20, LCD_EN_PIN, LCD_RW_PIN, LCD_RS_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);


void setup(void) {

    lcd.begin(16, 2);
    lcd.setBacklightPin(LCD_BACKLIGHT_PIN, POSITIVE);
    lcd.home();
    lcd.print("Buttons level");

    delay(1000);

    lcd.home();
    lcd.clear();

}

void loop(void) {

    int buttonsLevel = analogRead(BUTTONS_PIN);

    lcd.clear();
    lcd.home();
    lcd.print(buttonsLevel);

    delay(200);

}
