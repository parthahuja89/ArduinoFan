#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
 
LiquidCrystal_I2C lcd(0x27, 20, 4);
String readString = "";
int SENSOR = 2;
int temp, humid;
DHT dht (SENSOR, DHT11);
Servo servo; 

int triggerTemp = 0; 

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
  digitalWrite(8, HIGH);
  servo.attach(9);
  servo.write(0);

  triggerTemp = 73;
  //stick 
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  
}


void loop()
{

  //stick
  Serial.print("X: ");
  Serial.print(analogRead(11));
  Serial.print("\n");
  
  humid = dht.readHumidity();
  temp = dht.readTemperature(true);

  Serial.print(temp);
  Serial.print("\n");
  Serial.print(humid);
  Serial.print("\n");
  delay(500);
  analogWrite(13, 200);
  lcd.setCursor(1, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("F");
  lcd.setCursor(11, 0);
  lcd.print("Humid: ");
  lcd.print(humid);
  lcd.print("%");
  
  lcd.setCursor(1, 1);
  lcd.print("Tigger Temp: ");
  lcd.print(triggerTemp);
  lcd.print("F");

  lcd.autoscroll();
  if(temp > triggerTemp) { 
    servo.write(90);
  }else{
    servo.write(0);
  }
}
