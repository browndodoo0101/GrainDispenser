/*
Written: 23/08/2024
*/

#include <LiquidCrystal_I2C.h>
#include <DFRobot_HX711.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <Servo.h>
#include <string.h>


//Initialisation of 1602 LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);


//Initialisation of the keypad...
//I am using a 4x4 matrix keypad
const byte ROWS = 4;
const byte COLS = 4;

//Booleans to control looping
bool grainType = true;

//Letter of the selected grain type  
char grainSelected;
String weightSelected; 

//List of grains
String grains1 = "Chagua nafaka";
String grains2 =  "(A, B, C au D)";

//How the keys are labeled
char myKeypad [ROWS][COLS] = {
  "123A",
  "456B",
  "789C",
  ".0#D",
};

//Pinout of the keypad with my Arduino
byte rowPins[] = {8, 9, 10, 11};
byte colPins[] = {4, 5, 6, 7};

Keypad keypad(makeKeymap(myKeypad), rowPins, colPins, ROWS, COLS);
//...keypad object has been created

Servo servo;  //Initialisation of servo
DFRobot_HX711 scale(A0, A1); //Initialization of scale

float _slope;        //These values are read
float _intercept;     //from EEPROM
long data_x;        //Instantaneous readings after calibration
float weight;

void setup() {
  lcd.init(); //The LCD is now ready for communication
  lcd.backlight();
  lcd.clear();

  servo.attach(12); //My servo is attached to digital pin 12 of Uno
  EEPROM.get(0, _slope);
  EEPROM.get(10,_intercept);
  closeLid();
}

void loop() {
  
    grainSelected = selectGrain();
    weightSelected = correctWeight();  
    verify();
    
    dispense();
  
}
