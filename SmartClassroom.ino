#include <Servo.h>
#include "DHT.h"
#define DHTPIN 7     // Digital pin connected to the DHT sensor

Servo servo;

int angle = 10;
int gasValue;
int motion;
int TempValue;
int redLed = 6;
int greenLed = 13;
int blueLed = 10;
int yellowLed = 4;
int buzzer = 9;
int gasSensor = A1;
int PIR = 8;
int DHT_11 = A5;
//int fanMotor =
int windowMotor = 2;
DHT dht(DHTPIN, DHT11);
  int windstatus=0;

void setup() {
  servo.attach(12);
  servo.write(angle);
  pinMode(gasSensor, INPUT);
 // pinMode(DHT_11, INPUT);
dht.begin(); 
  pinMode(PIR, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
  Serial.begin(9600);
  Serial.begin(9600);


       

}

void loop() {
  //TempValue = analogRead(DHT_11);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float TempValue = dht.readTemperature();  

  float hic = dht.computeHeatIndex(TempValue, h, false);

  gasValue = analogRead(gasSensor);
  motion = digitalRead(PIR);

  Serial.println("MOTION:  ");
  Serial.println(motion);


  Serial.println("Air Quality is:  ");
  Serial.println(gasValue, DEC);


  Serial.print(" Room temperatue is: ");
  Serial.println(TempValue);
  Serial.print(" Humidity is: ");
  Serial.print(h);
   Serial.print(F(" °F  Heat index: "));
  Serial.println(hic);

  if (motion == HIGH) {
    digitalWrite(blueLed, HIGH);
    Serial.println("someone is inside!!");
    delay(100);

    if (hic > 48) {
          if(windstatus==0){  

Serial.println("window is opening")   ; 
        windstatus=1;
      // scan open from 0 to 180 degrees
        for (angle = 0; angle < 90; angle++) {
        servo.write(angle);
        delay(100);
      }  
          }
    

      // Serial.println("Temp is high!");
      // delay(10000);
    } else {

      if (windstatus==1){
        Serial.println("window is clossing")   ; 
               windstatus=0; 
      //    // now scan back from 180 to 0 degrees
      for (angle = 90; angle > 0; angle--) {
        servo.write(angle);
        delay(100);
      }
      }
      Serial.println("Temperature is normal!");
      delay(2000);
    }
  }

  else {
    digitalWrite(blueLed, LOW);

    Serial.println("motion not detected");
    delay(2000);
  }
 
  if (gasValue > 320) {
    digitalWrite(redLed, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenLed, LOW);
    Serial.print("Alert!! Bad Gas Detected!");
    delay(2000);
  }

  else {
    digitalWrite(redLed, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLed, HIGH);
    Serial.println("The room air is normal!");
    delay(2000);
  }
}
