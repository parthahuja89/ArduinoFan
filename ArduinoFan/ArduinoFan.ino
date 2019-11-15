#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void printToLCD() {
  lcd.init();
  lcd.init();
  lcd.backlight(); 

}

int SENSOR = 2;
int temp, humid;
DHT dht (SENSOR, DHT11);

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

}
