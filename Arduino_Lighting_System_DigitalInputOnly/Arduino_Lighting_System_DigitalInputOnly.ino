/////////////////////// INITIALIZATION OF LIGHTING CONTROL SYSTEM  ////////////////////////////
  // Assigning Digital Input PIN numbers
  #define LCS_turnONButton 2
  #define LCS_turnOFFButton 3
  #define LCS_whiteButton 4
  #define LCS_yellowButton 5
  #define LCS_blueButton 6
  #define LCS_redButton 7
  #define LCS_ledWhite 8
  #define LCS_ledYellow 9
  #define LCS_ledBlue 10
  #define LCS_ledRed 11

  // This will indicate when the LED is turned ON or OFF  -   FALSE means OFF
  boolean LCS_blue = false, LCS_red = false, LCS_yellow = false, LCS_white = false;

///////////////////////  INITIALIZATION OF EARTHQUAKE ALARM SYSTEM   ////////////////////////////
  // Assigning Digital Input PIN numbers
  #define EQAS_buzzer1 22
  #define EQAS_ledBlue 24
  #define EQAS_blueButton 26
  #define EQAS_ledRed 28
  #define EQAS_redButton 30
  #define EQAS_buzzer2 32

  // This will indicate if the red button or blue button is pressed
  boolean EQAS_redIndicator = false, EQAS_blueIndicator = false;

///////////////////////  INITIALIZATION OF GATE ACCESS SYSTEM   ////////////////////////////
  #include <LiquidCrystal_I2C.h>
  #include <Servo.h>
  Servo servoMain;
  LiquidCrystal_I2C lcd(0x27,16,2);

  int trigpin = 34; //Location of the pin
  int echopin = 13; //Location of the pin
  int distance;
  float duration;
  float cm;

///////////////////////  INITIALIZATION OF GSM MODULE   ////////////////////////////
  #include <SoftwareSerial.h>
  // Assigning Communication from Digital Input Pins
  SoftwareSerial sim(14, 15); // tx, rx PINs
  String number = "+639351539638"; //-> change with your number
void setup() {

  ///////////////////  LIGHTING CONTROL SYSTEM SETUP////////////////////////////////
    pinMode(LCS_ledBlue, OUTPUT);
    pinMode(LCS_ledRed, OUTPUT);
    pinMode(LCS_ledYellow, OUTPUT);
    pinMode(LCS_ledWhite, OUTPUT);
    pinMode(LCS_blueButton, INPUT);
    pinMode(LCS_redButton, INPUT);
    pinMode(LCS_yellowButton, INPUT);
    pinMode(LCS_whiteButton, INPUT);
    pinMode(LCS_turnOFFButton, INPUT);
    
  ///////////////////////  EARTHQUAKE ALARM SYSTEM SETUP ////////////////////////////
    pinMode(EQAS_buzzer1, OUTPUT);
    pinMode(EQAS_buzzer2, OUTPUT);
    pinMode(EQAS_ledBlue, OUTPUT);
    pinMode(EQAS_ledRed, OUTPUT);
    pinMode(EQAS_blueButton, INPUT);
    pinMode(EQAS_redButton, INPUT);  
  
  ///////////////////////  GATE ACCESS SYSTEM SETUP  ////////////////////////////
    servoMain.attach(12); //Location of the pin
    servoMain.write(0); //set initial position of servo
    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);
    
    lcd.begin(16,2); //Nilagyan ko parameter

    // Turn on the blacklight and print a message.
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("  Gate Closed!");

  ///////////////////////  INITIALIZATION OF GSM MODULE   ////////////////////////////
    //delay(7000); //delay for 7 seconds to make sure the modules get the signal
    sim.begin(9600);
    Serial.begin(9600);
    delay(5000);
}

void loop() {

  ///////////////////////  ARDUINO GUI  ////////////////////////////
    if (Serial.available()){
      String data = Serial.readString();

    ///////////////////  LIGHTING SYSTEM  ////////////////////////////////
      if(data == "redLED"){
        if(LCS_red == false){
          LCS_red = true;
          Serial.write("Red LED turned ON\n");
        }
        else {
          LCS_red = false;
          Serial.write("Red LED turned OFF\n");
        }
      }
      else if (data == "blueLED"){
        if(LCS_blue == false){
          LCS_blue = true;
          Serial.println("Blue LED turned ON\n");
        }
        else if (LCS_blue == true) {  
          LCS_blue = false;
          Serial.println("Blue LED turned OFF\n");
        }
      }
      else if (data == "yellowLED"){
        if(LCS_yellow == false){
          LCS_yellow = true;
          Serial.println("Yellow LED turned ON\n");
        }
        else {
          LCS_yellow = false;
          Serial.println("Yellow LED turned OFF\n");
        }
      }
      else if (data == "whiteLED"){
        if(LCS_white == false){
          LCS_white = true;
          Serial.println("White LED turned ON\n");
        }
        else {
          
          LCS_white = false;
          Serial.println("White LED turned OFF\n");
        }
      }
      else if (data == "onAllLED"){
          LCS_blue = true;
          LCS_red = true;
          LCS_yellow = true;
          LCS_white = true;
          Serial.println("ALL LEDs turned ON\n");
      }
      else if (data == "offAllLED"){
          LCS_blue = false;
          LCS_red = false;
          LCS_yellow = false;
          LCS_white = false;
          Serial.println("ALL LEDs turned OFF\n");
      }

    ///////////////////////////  EARTHQUAKE ALARAM SYSTEM  ///////////////////////
      if(data == "Emergency"){
        if(EQAS_redIndicator == false){      // If the LCS_red button is clicked and the indicators are off, this will turn the alarm ON
          EQAS_redIndicator = true;
          EQAS_blueIndicator = false;    // turns off the other alarm if it is turned on
          Serial.println("EARHTQUAKE ALARM ACTIVATED!!");
        }
        else if (EQAS_redIndicator == true){ // If the LCS_red button is clicked and the indicators are ON, this will turn the alarm OFF
          EQAS_redIndicator = false;
          Serial.println("EARHTQUAKE ALARM DEACTIVATED!!");
        }  
      }
      if(data == "Drill"){
        if(EQAS_blueIndicator == false){
          EQAS_redIndicator = false;
          EQAS_blueIndicator = true;
          Serial.println("EARHTQUAKE DRILL ALARM ACTIVATED!!");
        }
        else if (EQAS_blueIndicator == true){
          EQAS_blueIndicator = false;
          Serial.println("EARHTQUAKE DRILL ALARM DEACTIVATED!!");
        }
      }
    }

  ////////////////////////  LIGHTING SYSTEM CONTROLLER  ////////////////////////////////////////////
    // TURN ON BUTTON   -   Turns on all LED
    if(digitalRead(LCS_turnONButton) == HIGH){
      LCS_blue = true;
      LCS_red = true;
      LCS_yellow = true;
      LCS_white = true;
      Serial.println("ALL LEDs turned ON\n");
    }
    // TURN OFF BUTTON   -   Turns off all LED
    else if (digitalRead(LCS_turnOFFButton) == HIGH){ 
      LCS_blue = false;
      LCS_red = false;
      LCS_yellow = false;
      LCS_white = false;
      Serial.println("ALL LEDs turned OFF\n");
    }
    // White  Button    -   Turns on White LED
    else if (digitalRead(LCS_whiteButton) == HIGH){
      if(LCS_white == false){
        LCS_white = true;
        Serial.println("White LED turned ON\n");
      }
      else {   
        LCS_white = false;
        Serial.println("White LED turned OFF\n");
      }
    }
    // Red Button    -   Turns on Red LED
    else if (digitalRead(LCS_redButton) == HIGH){
      if(LCS_red == false){
        LCS_red = true;
        Serial.write("Red LED turned ON\n");
      }
      else {
        LCS_red = false;
        Serial.write("Red LED turned OFF\n");
      }
    }
    // Blue Button    -   Turns on Blue LED
    else if (digitalRead(LCS_blueButton) == HIGH){
      if(LCS_blue == false){
        LCS_blue = true;
        Serial.println("Blue LED turned ON\n");
      }
      else if (LCS_blue == true) {  
        LCS_blue = false;
        Serial.println("Blue LED turned OFF\n");
      }
    }
    // Yellow Button     -   Turns on Yellow LED
    else if (digitalRead(LCS_yellowButton) == HIGH){
      if(LCS_yellow == false){
        LCS_yellow = true;
        Serial.println("Yellow LED turned ON\n");
      }
      else {
        LCS_yellow = false;
        Serial.println("Yellow LED turned OFF\n");
      }
    }

    // This will control the LEDs
    if (LCS_red == true){
      digitalWrite(LCS_ledRed, HIGH);
    }
    else if (LCS_red == false){
      digitalWrite(LCS_ledRed, LOW);
    }
    if (LCS_white == true){
      digitalWrite(LCS_ledWhite, HIGH);
    }
    else if (LCS_white == false){
      digitalWrite(LCS_ledWhite, LOW);
    }
    if (LCS_blue == true){
      digitalWrite(LCS_ledBlue, HIGH);
    }
    else if (LCS_blue == false){
      digitalWrite(LCS_ledBlue, LOW);
    }
    if (LCS_yellow == true){
      digitalWrite(LCS_ledYellow, HIGH);
    }
    else if (LCS_yellow == false){
      digitalWrite(LCS_ledYellow, LOW);
    }
  
  
  ///////////////////////  EARTHQUAKE SYSTEM CONTROLLER  ////////////////////////////
    if (digitalRead(EQAS_redButton) == HIGH) {  
      if(EQAS_redIndicator == false){      // If the LCS_red button is clicked and the indicators are off, this will turn the alarm ON
        EQAS_redIndicator = true;
        EQAS_blueIndicator = false;    // turns off the other alarm if it is turned on
        Serial.println("EARHTQUAKE ALARM ACTIVATED!!");
      }
      else if (EQAS_redIndicator == true){ // If the LCS_red button is clicked and the indicators are ON, this will turn the alarm OFF
        EQAS_redIndicator = false;
        Serial.println("EARHTQUAKE ALARM DEACTIVATED!!");
      }
    } 
    else if (digitalRead(EQAS_blueButton) == HIGH) {
      if(EQAS_blueIndicator == false){
        EQAS_redIndicator = false;
        EQAS_blueIndicator = true;
        Serial.println("EARHTQUAKE DRILL ALARM ACTIVATED!!");
      }
      else if (EQAS_blueIndicator == true){
        EQAS_blueIndicator = false;
        Serial.println("EARHTQUAKE DRILL ALARM DEACTIVATED!!");
      }
    } 

    if(EQAS_redIndicator == true){
      digitalWrite(EQAS_ledRed, HIGH);
      tone(EQAS_buzzer2, 1000);
      delay(500);
      tone(EQAS_buzzer2, 500);
      delay(500);

      // GSM MODULE ACTUALIZATION
      sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(200);;
      sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
      delay(200);
      String SMS = "EARTHQUAKE DETECTED!! PLEASE EVACUATE IMMEDIATELY";
      sim.println(SMS);
      delay(100);
      sim.println((char)26);// ASCII code of CTRL+Z
    }
    else if (EQAS_redIndicator == false){
      digitalWrite(EQAS_ledRed, LOW);
      noTone(EQAS_buzzer2);
    }
    if(EQAS_blueIndicator == true){
      digitalWrite(EQAS_ledBlue, HIGH);
      tone(EQAS_buzzer1, 1000);
      delay(200);
      tone(EQAS_buzzer1, 100);
      delay(100);
      tone(EQAS_buzzer1, 800);
      delay(200);
      tone(EQAS_buzzer1, 300);
      delay(100);

      // GSM MODULE ACTUALIZATION
      sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(200);;
      sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
      delay(200);
      String SMS = "EARTHQUAKE DRILL SIMULATION!! Please Follow the procedure!! DROP, COVER AND HOLD!!!";
      sim.println(SMS);
      delay(100);
      sim.println((char)26);// ASCII code of CTRL+Z
    }
    else if (EQAS_blueIndicator == false){
      digitalWrite(EQAS_ledBlue, LOW);
      noTone(EQAS_buzzer1);
    }
  
  /*
  //////////////////////// GATE ACCESS SYSTEM CONTROLLER  ///////////////////////////////////
    digitalWrite(trigpin, LOW);   //Clears the trigpin
    delay(2);
    digitalWrite(trigpin, HIGH); //Sets the trigpin high for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW); 
    duration = pulseIn(echopin, HIGH);
    cm =  (duration/58.82);
    distance = cm;


    if (distance<20){
      //lcd.setCursor(0,0);
      //lcd.print("  Gate Opened!");
      servoMain.write(90);
      delay(1000);
    }
    else{
      //lcd.setCursor(0,0);
      servoMain.write(0);
      //lcd.print("  Gate Closed!");
      delay(500);

    }*/

    
delay(200);
}