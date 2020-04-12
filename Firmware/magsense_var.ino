#include <Adafruit_LIS2MDL.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LIS2MDL lis2mdl = Adafruit_LIS2MDL(12345);
#define LIS2MDL_CLK 13
#define LIS2MDL_MISO 12
#define LIS2MDL_MOSI 11
#define LIS2MDL_CS 10

int motor = 1;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS2MDL Magnetometer Test");
  Serial.println("");

  /* Enable auto-gain */
  lis2mdl.enableAutoRange(true);

  /* Initialise the sensor */
  if (!lis2mdl.begin()) {  // I2C mode
  //if (! lis2mdl.begin_SPI(LIS2MDL_CS)) {  // hardware SPI mode
  //if (! lis2mdl.begin_SPI(LIS2MDL_CS, LIS2MDL_CLK, LIS2MDL_MISO, LIS2MDL_MOSI)) { // soft SPI
    /* There was a problem detecting the LIS2MDL ... check your connections */
    Serial.println("Ooops, no LIS2MDL detected ... Check your wiring!");
    while (1) delay(10);
  }

  /* Display some basic information on this sensor */
  lis2mdl.printSensorDetails();
}

void loop(void) {
  /* Get a new sensor event */
  sensors_event_t event;
  lis2mdl.getEvent(&event);

  float x = event.magnetic.x;
  float y = event.magnetic.y;
  float z = event.magnetic.z;
  float sum = x+y+z;
  float sum2 = abs(x)+abs(y)+abs(z);
  float sum3 = sum+sum2;
  
  float var1 = 0;
  float var2 = 120;
  float var3 = 60;
  //calibrate these vars based on the magnet used
  
  if(sum>var1)
  {
    digitalWrite(motor, HIGH);
    delay(200);
    digitalWrite(motor, LOW);
  }
  else if(sum2>var2)
  {
    digitalWrite(motor, HIGH);
    delay(200);
    digitalWrite(motor, LOW);
  }
  else if(sum3>var3)
  {
    digitalWrite(motor, HIGH);
    delay(200);
    digitalWrite(motor, LOW);
  }
  
  delay(100);
}
