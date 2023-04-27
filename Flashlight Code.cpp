#include <LiquidCrystal.h> //imported the lcd library

const int rs = 11, en = 10, d4 = 9, d5 = 8, d6 = 7, d7 = 6; //created ints for the lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int outA = 13; //set variable outA to pin 13
int outB = 12; //set variable outB to pin 12
int outC = 3;// set variable outC to pin 3
bool previous = 1; //created a bool previous at 1
int interruptPin0 = 2; //set interruptpin0 at 2
volatile int toggleMode = 0; //created volatile variable toggleMode at 0
int count = 50; //created volatile varible count at 50


int sensorA = A0; //set variable sensorA to A0
int sensorVal = 0; //set variable senorVal to 0
int mapVal = 0; //set variable mapVal to 0


float startTime = 0;
float tOn = 500;
float tOff = 500;
float currentTime = 0;

void setup() 
{
  pinMode(outA, INPUT); //set pin 13 to input
  pinMode(outB, INPUT); //set pin 12 to input
  pinMode(outC, OUTPUT); //set pin 3 to output
  pinMode(interruptPin0, INPUT); //set pin 2 to input
  lcd.begin(16,2);
  Serial.begin(9600); //begin comms
  attachInterrupt(digitalPinToInterrupt(interruptPin0), toggle, RISING); //interrupt command that uses 
                                                                         //pin 2 and the toggle method 
                                                                         //when a rising edge is detect
}

void loop() 
{

    lcd.setCursor(0,1);
    
    //if statement for 3 modes of the leds
    //toggleMode0 lets the user control the LED
    
    if(toggleMode == 0)
    {
        Serial.println("0");
        Serial.println(count);
        lcd.print("Mode 1");
        controlLight();
    }
    //toggleMode1 just flashes the LED on and off
    else if(toggleMode == 1)
    {    
        Serial.println("1");
        lcd.print("Mode 2");    
        fadeBrightness();      
    }
    //toggleMode2 turns on the LED
    else if(toggleMode == 2)
    {   
        Serial.println("2");
        lcd.print("Mode 3");     
        turnOnStatic();      
    }
    //toggleMode3 blink on and off at a half rate
    else if(toggleMode == 3)
    {
      Serial.println("3");
      lcd.print("Mode 4");
      blinkClock();
    }
    //toggleMode4 turns off the LED
    else if(toggleMode == 4)
    {    

        Serial.println("4");
        lcd.print("Mode 5");   
        turnOffStatic();
    }
    //toggleMode 5 used a pot to control the brightness of an led
    else if(toggleMode == 5)
    {
      Serial.println("5");
      lcd.print("Mode 6");
      potLED();
    }
    lcd.clear();
}

void blinkClock()
{
  currentTime = millis();
  if(currentTime > startTime + tOn)
  {
    digitalWrite(outC, LOW);
    
  }
  if(currentTime > startTime + tOn + tOff)
  {
    digitalWrite(outC, HIGH);
    startTime = currentTime;
  }  
}


void toggle()
{
    
    toggleMode++; //increments the toggleMode to switch to each phrase
    if(toggleMode == 6) //if it hits the maximum we reset to 0
    {
      toggleMode = 0;
    }
}
//method to turn off LED
void turnOffStatic()
{
  digitalWrite(outC, LOW);
}


//method to turn on LED
void turnOnStatic()
{
  digitalWrite(outC, HIGH);
}

//method to turn the LED on and off
void fadeBrightness()
{
  
  // turn on LED
  for (int i = 0; i < 256; i++) {
    analogWrite(outC, i);
    delay(1); 
  }
  
  //dim LED
  for (int i = 255; i >= 0; i--) {
    analogWrite(outC, i);
    delay(1); 
  
}

    

  
}

void potLED()
{
  sensorVal = analogRead(sensorA); //reads analog value and converts to a digital value
  mapVal = map(sensorVal, 0, 1023, 0, 255); //maps range 0 - 1023 to 0 - 255
  analogWrite(outC, mapVal); //analog writes i to led
}




//uses the rotary encoder to control the turning and turning off the LED
void controlLight()
{
  
  //bool to read outA and outB
  bool a = digitalRead(outA);
  bool b = !digitalRead(outB); //reverse the output to make it consistent
  
  if(a != previous) //if current state is not equal to previous state and outA is high
  {   if(a)
      {
          if (b) //if b is "low"
          {
            count += 5; //increment count or brightness            
          }
          else if(!b) //if b is "high"
          {
            count -=5; //decrement count or brightness              
          }
      }  
      previous = a; //previous state sent to current state          
  }  
      
      //if else if statements to analog write to LED
      //if count is greater than 255 then we just hold it there since it past max analogWrite
      if(count > 255)
      {
        analogWrite(outC, 255);
      }
      //if count within the bounds of analogWrite then we use count to output
      else if (count >= 0 && count < 256)
      {
        analogWrite(outC, count);
      }

      //if count is near the lower bounds of analogWrite then we keep it analog at 0
      else
      {
        analogWrite(outC,0);
      }
}