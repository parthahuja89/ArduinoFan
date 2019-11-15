#include <ArduinoUnit.h>
#include <ArduinoUnitMock.h>

test(ok) 
{
  int x=3;
  int y=3;
  assertEqual(x,y);
}

test(bad)
{
  int x=3;
  int y=3;
  assertNotEqual(x,y);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial) {} 
}

void loop()
{
  Test::run();
}
