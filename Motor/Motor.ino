#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <utility/imumaths.h>
#include <Servo.h>
#define BNO055_SAMPLERATE_DELAY_MS (100)

short int home;
int x,y,z,xtemp,ytemp,ztemp,i,setinitial=0;
Servo servox,servoy,servoz;
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup(void){
  Serial.begin(9600);
  servox.attach(9);//X-axis servo attache to PWM pin 9
    servoy.attach(10);//Y-axis servo attached to PWM pin 10
    servoz.attach(11);//Z-axis servo attached to PWM pin 11
    if(!bno.begin()){
        Serial.print("Sensor not found. :(");
        while(1);
    }
  delay(1000);
  bno.setExtCrystalUse(true);
}

void loop(void){
  sensors_event_t event;
    bno.getEvent(&event);
    x=event.orientation.x;
    y=event.orientation.y;
    z=event.orientation.z;
    // for y axis only
    if(setinitial == 0){
      for(i=1;i<=90;i++)
        servoy.write(i);
      
      for(i=1;i<=90;i++)
        servox.write(i);
        
      for(i=1;i<=90;i++)
      	servoz.write(i);
      setinitial=1;
    }
    else{
      servoy.write(y+90);
      servox.write((x+90)%360);
      servoz.write(z+90);
    }
    //
    
    //x axis
    
    delay(15);
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
