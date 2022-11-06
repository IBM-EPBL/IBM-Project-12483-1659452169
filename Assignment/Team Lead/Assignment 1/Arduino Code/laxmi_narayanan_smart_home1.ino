#include<Servo.h>

int output1value= 0;
int sen1value= 0;
int sen2value= 0;
int const gas_sensor= A1;
int const LDR= A0;
int limit= 400;

long readUltrasonicDistance(int triggerpin, int echopin)\
{
 pinMode(triggerpin, OUTPUT); // clear the trigger
 digitalWrite(triggerpin, LOW);
 delayMicroseconds(2);
//sets the trigger pin to high state for 10 microseconds
 digitalWrite(triggerpin, HIGH);
 delayMicroseconds(10);
 pinMode(echopin, INPUT);
// reads the echo pin, and return the sound wave travel time 
  return pulseIn(echopin, HIGH);
}

Servo servo_7;

void setup()
{
   Serial.begin(9600);     //initialiize serial communication
  pinMode (A0, INPUT);      //LDR
  pinMode (A1, INPUT);      //gas sensor
  pinMode(13, OUTPUT);      //connected to relay
  servo_7.attach(7, 500, 2500);  //Green LED	

  pinMode(8, OUTPUT);     //signal to piezo burger
  pinMode(9, INPUT);     //signal to PIR
  pinMode(10, OUTPUT);    //signal to nPn as switch
  pinMode(4, OUTPUT);     //Red LED
  pinMode(3, OUTPUT);    //Green LED
  

}
void loop()
{

   //-------light intensity control--------//
//------------------------------------------------------------------------------
   int vall= analogRead(LDR);
  if (vall > 500)
 {
     digitalWrite(13, LOW);
 Serial.print("Bulb ON = ");
 Serial.print(vall);
 }
else
{
     digitalWrite(13, HIGH);
  Serial.print("Bulb OFF= ");
 Serial.print(vall);
 }


//-----------------------------------------------------------------------------
          //--------Light & fan control-------------//
//---------------------------------------------------------------------------------
   sen2value = digitalRead(9);
   if (sen2value==0)
   {
      digitalWrite(10, LOW); //nPn as switch OFF
      digitalWrite(4, HIGH); //Red lED ON, indicating no motion
      digitalWrite(3, HIGH); //Green LED OFF, since no motion
   Serial.print("    || NO Motion Detected     ");
   }
if (sen2value== 1)
  { 
      digitalWrite(10, 	HIGH); // npn as swtich ON 
    delay(5000);
         digitalWrite(4,LOW);  //RED LED OFF
         digitalWrite(3,HIGH); //GREEN LED ON , indicatimg motion
    Serial.print("       ||Motion Detected!      ");
   }

 //-------------------------------------------------------------------------------------------------
         //-------------Gas Sensor -----//
//--------------------------------------------------------------------------------------
 int val= analogRead(gas_sensor);       //read sensor value
    Serial.print(" || Gas Sensor Value =");
    Serial.print(val);                 // printing in serial motion
//val =map(val, 300, 750, 0, 100); 
  if(val > limit)
    {
         tone(8, 650);
    }
    delay(300);
    noTone(8);

 //-------------------------------------------------------------------------------------
          //--------servo motor -----//
 //-------------------------------------------------------------------------------------------
  sen1value = 0.01723 * readUltrasonicDistance(6, 6);
 
  if  (sen1value < 100)
      {
        servo_7.write(90);
     Serial.print("    || Door Open!  ; Distance = ");
     Serial.print(sen1value);
    Serial.print("\n"); 

   }
 else

   {   
        servo_7.write(0);
     Serial.print("    || Door Closed!  ; Distance = ");
     Serial.print(sen1value);
    Serial.print("\n"); 
}
delay(10);
} 
                