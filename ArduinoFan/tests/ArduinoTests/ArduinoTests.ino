#include <ArduinoUnit.h>

#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int SENSOR = 2;
int temp, humid;
DHT dht (SENSOR, DHT11);


//TESTS
/*
* Temperature should be >0 C 
*/
test()
{
  int t = dht.readTemperature();
  assertNotEqual(t, -1);
  assertNotEqual(t, -10);
  assertNotEqual(t, -100);
}
/*
* Temperature should be <50 C 
*/
test(bad)
{
  int t = dht.readTemperature();
  assertNotEqual(t, 100);
  assertNotEqual(t, 60);
  assertNotEqual(t, 70);
}

void printToLCD() {
  lcd.init();
  lcd.init();
  lcd.backlight(); 

}

void setup()
{
  printToLCD();
  Serial.begin(9600);
  dht.begin();
}

void loop()
{

  humid = dht.readHumidity();
  temp = dht.readTemperature(true);
  Serial.print(temp);
  Serial.print(humid);
  delay(500);
  analogWrite(13, 200);
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("Fan: "); // Print the string "Hello World!"
  lcd.setCursor(6, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("F");
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("GPU: ");
  lcd.setCursor(8, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("CPU: ");

  Test::run();
}
