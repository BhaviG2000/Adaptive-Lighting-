#include <dht.h>                //Library for Temperature Sensor 
#include <LiquidCrystal.h>     //Library for LCD display 
#include <FastLED.h>     //Library for the LED's
#define LED_PIN     37 //defines the input pin for the LED's 
#define NUM_LEDS    120 // number of LED's used in the LED strip 

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);  //inputs for the LCD display 
dht DHT;  //declaration for variable for the DHT sensor 
CRGB leds[NUM_LEDS];    //declaration for CRGB variable 

const int micPin  = 12;      //defines the input pin for the sound sensor 
const byte DHT_SENSOR_PIN = 9;    //defines the input pin for the temperature sensor 
int micVal  = 0;     //variable created for the value of the sound sensor to show TA that the code works but the sensor is not functioning 
int temp = 19;        // variable created for the temperature sensor to show TA that the code works but the sensor is not functioning 

void setup() {
  Serial.begin(9600); //threshold for the Sound Sensor
  Serial.flush();  
  lcd.begin(16, 2);  //shows the size of the LCD display 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);    
  Serial.begin(9600);  //threshold for the Sound Sensor 
  Serial.println(F("Initialize System"));  //Print statement Initialize System
  pinMode(micPin, INPUT); //Identify micPin as an input 

}
void loop() {
  DHT.read11(DHT_SENSOR_PIN);  //read the values recieved from the DHT sesnor 
  lcd.clear();  //Clear the LCD screen of any commands 
  lcd.setCursor(0, 0); //sets the location at 0,0 for the LCD to display the information 
  lcd.print("humidity: ");  //print humidity on the screen 
  lcd.print(DHT.humidity);  //print the value recieved from the DHT sensor beside the Humidity 
  lcd.print("%");  //Print the command after the value recieved from the DHT sensor
  lcd.setCursor(0, 1);  //uses the second line of the LCD to print a new statement in the following code
  lcd.print("temperature: ");  //Print the temperature in a new line 
  lcd.print(DHT.temperature); // Print the value recieved from the DHT sensor 
  lcd.print("C"); //Print the letter C for Celsius 
  readMicrophone(); //read the value from the microphone 

if (DHT.temperature <= 15) {  //after the temperature has been recieved, read the temperature value is below 15 degrees run the following loop
  // if (temp <= 15) { . // this is a variable created to test the code as the sensor had broken down last minute 
  for (int i = 0; i <= 119; i++) {  // For loop is initialized to go through the 120 LED's connected to the arduino 
    leds[i] = CRGB:: Blue;  // Change the color of the LED Blue at max brightness 
    FastLED.show(); //turn the LED's on 
    delay(100);  //Delay the way the LED's turn on in sequence 
    }
}
    else {  // for all other values that are greater than 15 
      for (int i = 119; i >= 0; i--) {   // For loop is initialized to go through the 120 LED's connected to the arduino
        leds[i] = CRGB:: Red;   // Change the color of the LED Blue at max brightness
        FastLED.show();  //turn the LED's on 
        delay(100);  //Delay the way the LED's turn on in sequence 
      }
    }
}

void readMicrophone( ) {  //Function created for reading the microphone 
 micVal = analogRead(micPin); //analyze the input from the analog pin that is connected to the arduino board
 micVal = 599;  //variable created because the sensor broke mid testing, this was made so the code can be tested
  Serial.print(F("mic val ")); Serial.println(micVal);  //print the statement mic val and the actual value recieved by the mic. 
  if (micVal > 600) {  //if statement created for the mic value to initialize a part of the code if the mic value is greater than 600
    FastLED.clear();  //Turns the LED lights off 
    delay(1000);      //keeps it off for 1 second
    FastLED.show();   // turns on the LED lights 
    delay(1000);      // keeps it on for 1 second 
  }
  else if (micVal < 600){   //else if statement created for the mic value to initialize a part of the code if the mic value is less than 600
      FastLED.clear();      // turns off the LED
    delay(100);             // keeps the LED off for 0.1 seconds
    FastLED.show();         // tuens on the LED 
    delay(100);            // keeps the LED on for 0.1 seconds
  } 
}
