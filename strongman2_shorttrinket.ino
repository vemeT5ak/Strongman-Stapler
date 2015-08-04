#include <Adafruit_NeoPixel.h>
#define NEOPIXELPIN 0
#define FSR   1   // Force Sensative Resistor on Trinket Pin #2 (Analog 1)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, NEOPIXELPIN, NEO_GRB + NEO_KHZ800); // set IDE board to 8mHz trinket


const int resetButton = 3;     // the number of the pushbutton pin
const int readyLED =  1;      // the number of the LED pin


// variables:
int sensorValue = 0;  // the sensor value
int spectrumValue[1]; // to hold a2d values
int avg = 0;
int maxReading = 0;
int resetState = 1;         // variable for reading the pushbutton status


void setup()
{
  strip.begin();
  strip.setBrightness(150);
  strip.show(); // Initialize all pixels to 'off'
  
  // initialize the LED pin as an output:
  pinMode(readyLED, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(resetButton, INPUT);
}


void loop()
{
  
     // read the sensor:
  sensorValue=analogRead(FSR);                // Read voltage on potentiometer

  if (sensorValue > maxReading) maxReading = sensorValue;

  //Measure the magnitude of the force sensor
  avg = 0;
  for (int i = 0; i < 1; i++){
   delayMicroseconds(5); // to allow the output to settle
    spectrumValue[i] = (maxReading); // this takes whatever output as the input to lighting up the strip
    avg += spectrumValue[i];
    
   /* Serial.print("avg");
    Serial.println ("");
    Serial.print(avg);
    Serial.println ("");
    
    Serial.print("sensorValue");
    Serial.println ("");
    Serial.print(sensorValue);
    Serial.println ("");
    
    */
    
    delay (10);
    
   
  }
  avg = avg/.5; // this number is the "handicap". A higher number will make it harder to reach the top of the scale.

  //Clear out the NeoPixel String
   for(int i = 0; i < 60; i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  
  //Draw the meter on the NeoPixel string
  for(int i = 0; i < map(avg, 0, 1023, 0, 10); i++){
     strip.setPixelColor(i, strip.Color(i*30, 35 - i, 0)); // the numbers here represent color brightness and length interger. play with these to match what you want in terms of color and length.
  }
    
  strip.show();
  
  resetState = digitalRead(resetButton);

  // check if the pushbutton is pressed.
  // if it is, the resetState is LOW:
  if (resetState == LOW) {     
    // turn LED on:    
    digitalWrite(readyLED, LOW);
    maxReading = 0;
  } 
  else {
    // turn LED off:
    digitalWrite(readyLED, HIGH);
  }
 }
