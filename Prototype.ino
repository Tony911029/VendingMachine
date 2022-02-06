
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

int creditPoint = 0; // count how many user has taged

// Rfid
// rfid reader
#include <SPI.h>
#include <RFID.h>
#define SS_PIN 9 
#define RST_PIN 8
RFID rfid(SS_PIN, RST_PIN);

String rfidCard;
String key1 = "247 26 207 180";
String key2 = "68 150 254 41";
String key3 = "74 42 252 132";

// LED
#include <Adafruit_NeoPixel.h>


#define LED_PIN    12
#define LED_COUNT 120
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

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


  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  
  Serial.begin(9600);

  SPI.begin(); // init SPI bus
  rfid.init();

  
  // Assign Push Button Pin input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  

  // Assign pin output
  pinMode(ENABLE, OUTPUT); 
  digitalWrite(ENABLE, LOW);
  

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

  theaterChaseRainbow(30); // Rainbow-enhanced theaterChase variant
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
    Serial.println(item1);
    } 

    if (strMsg.startsWith(item2)){
    Serial.print(item2);
    Serial.print(",");
    Serial.println(getValue(strMsg, ',', 1));
    item2Num = getValue(strMsg, ',', 1).toInt();
    Serial.println(item2);
    } 

    if (strMsg.startsWith(item3)){
    Serial.print(item3);
    Serial.print(",");
    Serial.println(getValue(strMsg, ',', 1));
    item3Num = getValue(strMsg, ',', 1).toInt();
    Serial.println(item3);
    } 

    if (strMsg.startsWith(item4)){
    Serial.print(item4);
    Serial.print(",");
    Serial.println(getValue(strMsg, ',', 1));
    item4Num = getValue(strMsg, ',', 1).toInt();
    Serial.println(item4);
    } 
    
    
/////////////////////////////////


  // read button assignment
  int button1State, button2State, button3State, button4State;
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  button4State = digitalRead(button4Pin);
  
  

 // define action when button 1 is pressed  // red button
 if (((button1State == LOW) && !(button2State == LOW)))// if we're pushing button 1 OR button 2
 { 
  if (item1Num !=0 && creditPoint > 0){
    digitalWrite(ENABLE, HIGH);// Set relay

    colorWipe(strip.Color(255,   0,   0), 5); // Red
    
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Dispensing");
    
    lcd.setCursor(3, 1);
    lcd.print("Your Item");
    
    myStepper0.step(-stepsPerRevolution); //run motor: clockwise

    theaterChaseRainbow(10); // Rainbow-enhanced theaterChase variant
    
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
    creditPoint--;
    
    }else if (creditPoint == 0){
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Not Enough");
      lcd.setCursor(2, 1);
      lcd.print("CreditPoint");
      }else{
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Out Of Stock");
     }
  } 



  // define action when button 2 is pressed  // blue button
  if (((button2State == LOW) && !(button1State == LOW)))  // if we're pushing button 1 OR button 2
  { 
    if (item2Num!=0 && creditPoint > 0){
      digitalWrite(ENABLE, HIGH);// Set state

      colorWipe(strip.Color(  0,   0, 255), 5); // Blue
      
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Dispensing");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      
      myStepper1.step(stepsPerRevolution);//run motor  //topright

      theaterChaseRainbow(10); // Rainbow-enhanced theaterChase variant
      
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
      creditPoint--;
      
      }else if(creditPoint == 0) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Not Enough");
      lcd.setCursor(2, 1);
      lcd.print("CreditPoint");
      }else{
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Out Of Stock");
       }
  }

    
  // define action when button 3 is pressed  // yellow button
  if (((button3State == LOW) && !(button4State == LOW)))  // if we're pushing button 1 OR button 2
  { 
    if (item3Num!=0 && creditPoint > 0){
      digitalWrite(ENABLE, HIGH);// Set state

      colorWipe(strip.Color(  225,   255,  0), 5); // yellow
      
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Dispensing");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      
      myStepper2.step(-stepsPerRevolution);//run motor

      theaterChaseRainbow(10); // Rainbow-enhanced theaterChase variant
      
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
      creditPoint--;
      
      }else if(creditPoint == 0) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Not Enough");
      lcd.setCursor(2, 1);
      lcd.print("CreditPoint");
      }else{
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Out Of Stock");
      }
  }

  
  // define action when button 4 is pressed // green button
  if (((button4State == LOW) && !(button3State == LOW)))  // if we're pushing button 1 OR button 2
  { 
    if (item4Num != 0 && creditPoint > 0){
      digitalWrite(ENABLE, HIGH);// Set state

      colorWipe(strip.Color(  0, 255,   0), 5); // Green
      
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Dispensing");
      lcd.setCursor(3, 1);
      lcd.print("Your Item");
      
      myStepper3.step(-stepsPerRevolution);//run motor buttomleft

      theaterChaseRainbow(10); // Rainbow-enhanced theaterChase variant
      
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
      creditPoint--;
      
      }else if(creditPoint == 0) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Not Enough");
      lcd.setCursor(2, 1);
      lcd.print("CreditPoint");
      }else{
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Out Of Stock");
      }
     
  }




  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      if ((rfidCard == key1)||(rfidCard == key2)||(rfidCard == key3)) {
          creditPoint++;  
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("CreditPoint");
          lcd.setCursor(2, 1);
          lcd.print(creditPoint);   
      } else {  
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Do Not Steal");
        lcd.setCursor(4, 1);
        lcd.print("My Stuff"); 
      }
    }
    rfid.halt();
    delay(1000);
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


// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
