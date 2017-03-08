#include "Interface.h"
#include "Arduino.h"
#include <max6675.h>

/* RS E D4 D5 D6 D7 */
LiquidCrystal lcd(7, 8, 9, 24, 10, 22);

void setup()
{
    lcd.begin(16, 2);
    lcd.print("hello, world!");
}

void loop()
{
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
}
