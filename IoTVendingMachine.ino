// Selling Item
String item1 = "chocolatebar";
String item2 = "popcorn";
String item3 = "twix";
String item4 = "gummybear";

// change the number here
int item1Num = -1;
int item2Num = -1;
int item3Num = -1;
int item4Num = -1;



// Display
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Stepper Library
#include <Stepper.h> //including stepper motor library

//Relay Setup
#define ENABLE 10   /////// change this if needed

//defining pins section
//Stepper Connect 1
int stepIN1Pin = 22;
int stepIN2Pin = 24;
int stepIN3Pin = 26;
int stepIN4Pin = 28;

//Stepper Connect 2
int stepIN1Pin1 = 23; 
int stepIN2Pin1 = 25;
int stepIN3Pin1 = 27;
int stepIN4Pin1 = 29;

//Stepper Connect 3
int stepIN1Pin2 = 30;
int stepIN2Pin2 = 32;
int stepIN3Pin2 = 34;
int stepIN4Pin2 = 36;

//Stepper Connect 4
int stepIN1Pin3 = 31;
int stepIN2Pin3 = 33;
int stepIN3Pin3 = 35;
int stepIN4Pin3 = 37;

//define steps
int stepsPerRevolution = 2048; // amount of steps per revolution

//define buttons pin ports
const int button1Pin = A0;  // Push Button 1 Analog Pin A0
const int button2Pin = A1;  // Push Button 2 Analog Pin A1
const int button3Pin = A2;  // Push Button 3 Analog Pin A2
const int button4Pin = A3;  // Push Button 4 Analog Pin A3

//define each stepper
// 1
Stepper myStepper0(stepsPerRevolution, stepIN1Pin, stepIN3Pin, stepIN2Pin, stepIN4Pin);
//2
Stepper myStepper1(stepsPerRevolution, stepIN1Pin1, stepIN3Pin1, stepIN2Pin1, stepIN4Pin1);
//3
Stepper myStepper2(stepsPerRevolution, stepIN1Pin2, stepIN3Pin2, stepIN2Pin2, stepIN4Pin2);
//4
Stepper myStepper3(stepsPerRevolution, stepIN1Pin3, stepIN3Pin3, stepIN2Pin3, stepIN4Pin3);


void setup() {
  item1.toLowerCase();
  item2.toLowerCase();
  item3.toLowerCase();
  item4.toLowerCase();
  
  Serial.begin(9600);

  // Assign Push Button Pin input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  
  // Assign pin output
  pinMode(ENABLE, OUTPUT); // pin10, enable input1,2


  // Assign Stepper Speed
  myStepper0.setSpeed(15);
  myStepper1.setSpeed(15);
  myStepper2.setSpeed(15);
  myStepper3.setSpeed(15);

  //Initialize LCD Display
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select your item");
  lcd.setCursor(0, 1);
  lcd.print(" #1 #2 #3 #4");
}
void loop() {
///////////////////////////////////////////////
// Initialize stock from c# program
    String strMsg;
    if (Serial.available()>0){
      strMsg = Serial.readStringUntil('\n');
      strMsg.replace(" ","");
      strMsg.toLowerCase();
    }
    
     // input string: "itemName,Num"
    if (strMsg.startsWith(item1)){
    Serial.print(item1);
    Serial.print(",");
    Serial.println(getValue(strMsg, ',', 1));
    item1Num = getValue(strMsg, ',', 1).toInt();
    } 

    if (strMsg.startsWith(item2)){
    Serial.print(item2);
    Serial.print(",");
    Serial.println(getValue(strMsg, ',', 1));
    item2Num = getValue(strMsg, ',', 1).toInt();
    } 

    if (strMsg.startsWith(item3)){
    Serial.print(item3);
    Serial.print(",");
    Serial.println(getValue(strMsg, ',', 1));
    item3Num = getValue(strMsg, ',', 1).toInt();
    } 

    if (strMsg.startsWith(item4)){
    Serial.print(item4);
    Serial.print(",");
    Serial.println(getValue(strMsg, ',', 1));
    item4Num = getValue(strMsg, ',', 1).toInt();
    } 
    
/////////////////////////////////

  // read button assignment
  int button1State, button2State, button3State, button4State;
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  button4State = digitalRead(button4Pin);
  

  // define action when button 1 is pressed
  if (((button1State == LOW) && !(button2State == LOW)))// if we're pushing button 1 OR button 2
 { 
  if (item1Num !=0){
    digitalWrite(ENABLE, HIGH);// Set relay
    
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Dispensing");
    
    lcd.setCursor(3, 1);
    lcd.print("Your Item");
    
    myStepper0.step(-stepsPerRevolution); //run motor: clockwise
    
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Please take");
    lcd.setCursor(3, 1);
    lcd.print("Your Item");
    delay(2500);
    lcd.setCursor(0, 0);
    lcd.print("Button State 1");
    lcd.setCursor(2, 1);
    lcd.print("1 2 3 or 4");

    digitalWrite(ENABLE, LOW);// Set state
    
    Serial.println(item1);
    item1Num--;
    
    }else{
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Out Of Stock");
      }

  } 
  
  // define action when button 2 is pressed
  if (((button2State == LOW) && !(button1State == LOW)))  // if we're pushing button 1 OR button 2
  { 
    if (item2Num!=0){
      digitalWrite(ENABLE, HIGH);// Set state
      
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Dispensing");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      
      myStepper1.step(stepsPerRevolution);//run motor  //topright
      
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Please take");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      delay(2500);
      lcd.setCursor(0, 0);
      lcd.print("Button State 2");
      lcd.setCursor(2, 1);
      lcd.print("1 2 3 or 4");
  
      digitalWrite(ENABLE, LOW);// Set state
  
      Serial.println(item2);
      item2Num--; 
      
      }else{
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Out Of Stock");
        }
  }
  
  // define action when button 3 is pressed
  if (((button3State == LOW) && !(button4State == LOW)))  // if we're pushing button 1 OR button 2
  { 
    if (item3Num!=0){
      digitalWrite(ENABLE, HIGH);// Set state
      
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Dispensing");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      
      myStepper2.step(-stepsPerRevolution);//run motor
      
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Please take");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      delay(2500);
      lcd.setCursor(0, 0);
      lcd.print("Button State 3");
      lcd.setCursor(2, 1);
      lcd.print("1 2 3 or 4");
      
      digitalWrite(ENABLE, LOW);// Set state
      
      Serial.println(item3);
      item3Num--;
      
      }else{
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Out Of Stock");
      }


  }
  
  // define action when button 4 is pressed
  if (((button4State == LOW) && !(button3State == LOW)))  // if we're pushing button 1 OR button 2
  { 
    if (item4Num != 0){
      digitalWrite(ENABLE, HIGH);// Set state
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Dispensing");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      
      myStepper3.step(-stepsPerRevolution);//run motor buttomleft
      
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Please take");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      delay(2500);
      lcd.setCursor(0, 0);
      lcd.print("Button State 4");
      lcd.setCursor(2, 1);
      lcd.print("1 2 3 or 4");
      
      digitalWrite(ENABLE, LOW);// Set state
      
      Serial.println(item4);
      item4Num--;
      
      }else{
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Out Of Stock");
      }
 
  }
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
