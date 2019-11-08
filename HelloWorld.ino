#include <dht.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


dht DHT;
#define DHT11_PIN 7
LiquidCrystal_I2C lcd(0x27, 20, 4);


void printToLCD() {
  lcd.init();
  lcd.init();
  lcd.backlight();


  Serial.begin(9600);

}

void setup()
{
  printToLCD();
  pinMode(13, OUTPUT);
}


void loop()
{

  analogWrite(13, 200);
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("Fan: "); // Print the string "Hello World!"
  lcd.setCursor(8, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("GPU: ");
  lcd.setCursor(8, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("CPU: ");

  //temp
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(2000);


}
