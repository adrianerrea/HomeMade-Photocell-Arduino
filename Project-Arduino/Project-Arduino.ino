#include <Wire.h>      // communication library for I2C
#include <LCD.h>      // library for LCD purposes
#include <LiquidCrystal_I2C.h>    // LCD library for I2C

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

const int EchoPin = 10; // for the Ultrasonic sensor
const int TriggerPin = 11; // for the Ultrasonic sensor

const int ledPIN1 = 13; // red LED
const int ledPIN2 = 12; // green LED

const int buzzer = 9;
int start=0;
unsigned long  starting_time=0;
unsigned long  final_time=0;
unsigned long  elapsed_time=0;
float  elapsed_time_seg=0; // to store the elapsed time in seconds
int counter=0; // need it for the nosiy signals received
int minimum_distance=100; // minimum distance in cm to make the ultrasonic sensor starts counting

// the passive buzzer plays the intro of Pirates of the Caribbean
void pirates_Of_The_Caribbean(){
  // uncomment for an extended version of the intro
  /*tone(buzzer,293.66,100);
  delay(100);
  tone(buzzer,440,100);
  delay(100);
  tone(buzzer,523.25,100);
  delay(100);
  tone(buzzer,587.33,100);
  delay(200);
  tone(buzzer,587.33,100);
  delay(200);
  tone(buzzer,587.33,100);
  delay(100);
  tone(buzzer,659.25,100);
  delay(100);
  tone(buzzer,698.45,100);
  delay(200);
  tone(buzzer,698.45,100);
  delay(200);
  tone(buzzer,698.45,100);
  delay(100);
  tone(buzzer,783.99,100);
  delay(100);
  tone(buzzer,659.25,100);
  delay(200);
  tone(buzzer,659.25,100);
  delay(200);
  tone(buzzer,587.33,100);
  delay(100);
  tone(buzzer,523.25,100);
  delay(100);
  tone(buzzer,523.25,100);
  delay(100);
  tone(buzzer,587.33,100);
  delay(300);
  tone(buzzer,440,100);
  delay(100);
  tone(buzzer,523.25,100);
  delay(100);
  tone(buzzer,587.33,100);
  delay(200);
  tone(buzzer,587.33,100);
  delay(200);
  tone(buzzer,587.33,100);
  delay(100);
  tone(buzzer,659.25,100);
  delay(100);
  tone(buzzer,698.45,100);
  delay(200);
  tone(buzzer,698.45,100);
  delay(200);
  tone(buzzer,698.45,100);
  delay(100);
  tone(buzzer,783.99,100);
  delay(100);
  tone(buzzer,659.25,100);
  delay(200);
  tone(buzzer,659.25,100);
  delay(200);
  tone(buzzer,587.33,100);
  delay(100);
  tone(buzzer,523.25,100);
  delay(100);
  tone(buzzer,587.33,100);
  delay(400);*/
  tone(buzzer,440,100);
  delay(100);
  tone(buzzer,523.25,100);
  delay(100);
  tone(buzzer,587.33,100);
  delay(200);
  tone(buzzer,587.33,100);
  delay(200);
  tone(buzzer,587.33,100);
  delay(100);
  tone(buzzer,698.45,100);
  delay(100);
  tone(buzzer,783.99,100);
  delay(200);
  tone(buzzer,783.99,100);
  delay(200);
  tone(buzzer,783.99,100);
  delay(100);
  tone(buzzer,880,100);
  delay(100);
  tone(buzzer,932.33,100);
  delay(200);
  tone(buzzer,932.33,100);
  delay(200);
  tone(buzzer,880,100);
  delay(100);
  tone(buzzer,783.99,100);
  delay(100);
  tone(buzzer,880,100);
  delay(100);
  tone(buzzer,587.33,100);
  delay(300);
  tone(buzzer,587.33,100);
  delay(100);
  tone(buzzer,659.25,100);
  delay(100);
  tone(buzzer,698.45,100);
  delay(200);
  tone(buzzer,698.45,100);
  delay(200);
  tone(buzzer,783.99,100);
  delay(200);
  tone(buzzer,880,100);
  delay(100);
  tone(buzzer,587.33,100);
  delay(300);
  tone(buzzer,587.33,100);
  delay(100);
  tone(buzzer,698.45,100);
  delay(100);
  tone(buzzer,659.25,100);
  delay(200);
  tone(buzzer,659.25,100);
  delay(200);
  tone(buzzer,698.45,100);
  delay(100);
  tone(buzzer,587.33,100);
  delay(100);
  tone(buzzer,659.25,100);
  delay(400); 
}


// function to get the distance from the ultrasonic sensor
int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  // to generate a clear pulse let's set it to LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  // let's generate a Trigger of 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  // let's measure the time between pulses, in microseconds
   
   distanceCm = duration * 10 / 292/ 2;   // let's convert the distance to cm
   return distanceCm;
}

void setup() {
  
   Serial.begin(9600);
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
   pinMode(ledPIN1 , OUTPUT); 
   pinMode(ledPIN2 , OUTPUT);  
   pinMode(buzzer , OUTPUT);  
   digitalWrite(ledPIN2 , HIGH);

   lcd.setBacklightPin(3,POSITIVE);  // port P3 of PCF8574 as positive
   lcd.setBacklight(HIGH);   // enables BackLight of the LCD
   lcd.begin(16, 2);     // 16 columns for 2 rows for the LCD
   lcd.clear();      // cleaning the screen

   lcd.setCursor(0, 0);    // set cursor on column 0 and row 0
   lcd.print("Welcome");  // printing out a Welcome message
  
   pirates_Of_The_Caribbean(); // beautiful melody when the kit starts 
  
}

// after measuring the time, we reset everything
void reset(){
    start=0;
    starting_time=0;
    final_time=0;
    elapsed_time=0;
    elapsed_time_seg=0;
    counter=0;
    digitalWrite(ledPIN2 , HIGH); // turning on the green LED
    lcd.clear();    
}

void loop() {
   int cm = ping(TriggerPin, EchoPin);
   
   // just for debugging purposes
   Serial.print("Distance: ");
   Serial.println(cm);

   // we need at least 3 consecutives signals below minimum distance for starting to avoid noisy signals
   if(cm<minimum_distance and start==0 and counter>=3){
    
    start=1;
    starting_time=millis();
    //Serial.print("Tiempo inicial: ");
    //Serial.println(starting_time);
    
    lcd.clear();  
    lcd.setCursor(0, 0); 
    lcd.print("Start");
    
    digitalWrite(ledPIN1 , HIGH); // turning on the red LED
    digitalWrite(ledPIN2 , LOW); // turning off the green LED
    
    // let's play a tone to notify
    tone(buzzer,700);
    delay(1000);
    noTone(buzzer);
    
    delay(2000);
    
   }else if(cm<minimum_distance and start==1){
    
      final_time=millis();
      //Serial.print("Final time: ");
      //Serial.println(final_time);
      elapsed_time=final_time-starting_time;
      elapsed_time_seg=elapsed_time/1000.0;
      //Serial.print("Elapsed time: ");
      //Serial.println(elapsed_time_seg);
      
      digitalWrite(ledPIN1 , LOW); // turning off the red LED

      lcd.clear();  
      lcd.setCursor(0, 0); 
      lcd.print("Elapsed time: ");
      lcd.setCursor(0, 1); 
      lcd.print(elapsed_time_seg); // showing the elapsed time
      
      // let's play a tone to notify
      tone(buzzer,700);
      delay(1000);
      noTone(buzzer);
      
      delay(30000); //Enough time for visualization
      delay(5000);
      reset();
      
   }else if(start==1){
    
      final_time=millis();
      elapsed_time=final_time-starting_time;
      elapsed_time_seg=elapsed_time/1000.0;
      lcd.clear();  
      lcd.setCursor(0, 0); 
      lcd.print("Elapsed time: ");
      lcd.setCursor(0, 1); 
      lcd.print(elapsed_time_seg); // showing the current time
       
   }else if(cm<minimum_distance){
      counter=counter+1; // let's create a counter to avoid noisy signals make the kit starting
    
   }else{
     counter=0;
   }
}
