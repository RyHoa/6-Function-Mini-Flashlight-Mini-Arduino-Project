# 6-Function-Mini-Flashlight-Arduino-Project
##
## 1. Rotary Encoder to control the brightness of the LED
I detected leading edge of A and depending on the state of B, count increases or decreases. That value is then used to analog write into the LED.
## 2. Increasing and diming the brightness automatically
I used 2 for loops to analogWrite on and off to the LED
## 3. Turns on the LED
I used digitalWrite HIGH
## 4. Blinks the LED at a certain timing
I used the concept of tON and tOFF to control the blinking of the LED 
## 5. Turns off the LED
I used digitalWrite LOW
## 6. Potentiometer to control the brightness of the LED
I used the wiper in the potentiometer to create a voltage divider. Then, I used the analog read command to get the voltage values. 
That command gives a digital value between 0-1023 with respect to the varying voltage level of 0-5 volts. Since analog write is only 0-255, 
I used the map command to convert the set of 0-1023 to a smaller set of 0-255 to analog write them into the LED.
