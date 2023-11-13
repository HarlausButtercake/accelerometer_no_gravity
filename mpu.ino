#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
double coeff = 0.8;
double gravity = 9.81;
double x, y, z;
double scale = 6;
double pre_x, pre_y, pre_z;
sensors_event_t a, g, temp;

void setup(void) {
  Serial.begin(115200);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  pre_x = 0;
  pre_y = 0;
  pre_z = 0;
}

void loop() {
  
  mpu.getEvent(&a, &g, &temp);
  x = a.acceleration.x;
  y = a.acceleration.y;
  z = a.acceleration.z;

  pre_x = pre_x*coeff + (1 - coeff)*x;
  pre_y = pre_y*coeff + (1 - coeff)*y;
  pre_z = pre_z*coeff + (1 - coeff)*z;

  Serial.print(scale);
  Serial.print(",");

  Serial.print(-scale);
  Serial.print(",");

  Serial.print(x - pre_x);
  Serial.print(",");

  Serial.print(y - pre_y);
  Serial.print(",");

  Serial.println(z - pre_z);
}


