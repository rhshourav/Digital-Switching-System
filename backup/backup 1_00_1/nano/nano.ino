#include <LiquidCrystal_I2C.h>

#include <Wire.h>

//global variable for switch
int sval1 = 0;
int sval2 = 0;
int sval3 = 0;
int bklight = 1;
int fan_var = 0;

// ultrasonic pins
long trig=8;
long echo=9;
long Zeit;
long Strecke;


//switch pins
const int switc = 2; //this pin is for distance measuring
const int switc1 = 6; //this pin goes to esp8266's pin 7 /or gpio pin 13
const int switc2 = 7; //this pin goes to esp8266's pin 6 / or gpio pin 12
const int switc3 = 5;// this pin goes to esp8266's pin 5 / or gpio pin 14


// output pins
int led = 3;
int fan = 12;



//toggle switch for ultrasonic sensor
int state = 0 , loadstate = 0;
int distance = 15;
int distance_one = 53;
int global = 0;
int switch_valu = 2;


//toggle switch for wifi switch 
int state1 = 0 , loadstate1 = 0;



//toggle switch for distance measuring
int state2 = 0 , loadstate2 = 0;


//toggle switch for fan switch
int state3 = 0 , loadstate3 = 0;


//main light variable
int loadstateMain = 0;


LiquidCrystal_I2C lcd(0x27, 16, 2);




void setup() {
    //Switcg Setup
    pinMode(switc, INPUT);
    pinMode(switc1, INPUT);
    pinMode(switc2, INPUT);
    pinMode(switc3, INPUT);
    
    //output setup
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    pinMode(fan, OUTPUT);
    digitalWrite(fan, LOW);
    
    
    // ultra sonic setup
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    Serial.begin(9600);
    Serial.print("Welcome Shourav");
    delay(1000);

    //setup display
    lcd.begin();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welcome Shourav");
    delay(1000);
    
}

void loop() {
  /*
  int test = 0;
  Serial.println(test);
  test = !test;
  Serial.println(test);
  test = !test;
  Serial.println(test);
  delay(1000);
  */
    //ultra sonic date collection
    digitalWrite(trig,HIGH);
    delayMicroseconds(200);
    digitalWrite(trig,LOW);
    Zeit = pulseIn(echo,HIGH);
    Strecke=Zeit*0.017;
    digitalWrite(trig,LOW);
    delayMicroseconds(200);



  
  // logic unit for ultrasonic sensor
  if (state == 0 && Strecke <= distance ) {
    state = 1;
    loadstate=!loadstate;
    delay(100);
  }
  if (state == 1 && Strecke <= distance ) {
    state =0;
    delay(100);
  }

  

  //switch read
  sval1 = digitalRead(switc1);
  sval2 = digitalRead(switc2);
  sval3 = digitalRead(switc3);


  //switc1 logic
  if (sval1 == HIGH){
    loadstate=!loadstate;
    delay(120);
  }

  //bklight logic
  if ( sval2 == HIGH){
    bklight =! bklight;
  }

  if ( bklight == LOW ){
    lcd.setBacklight(0);
  }
  else{
    lcd.setBacklight(1);
  }

  //fan logic
  if ( sval3 == HIGH ){
    fan_var =! fan_var;
    delay(120);
  }

  if ( fan_var == HIGH) {
    digitalWrite(fan, HIGH);
    Serial.println(" Fan Is On");
    
  }
  else{
    digitalWrite(fan, LOW);
    Serial.println("Fan Is Off");
  }
  
  if (loadstate==HIGH  ) {
    Serial.println("woriking");
    digitalWrite(led, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("--Light Is ON---");
    lcd.setCursor(0, 4);
    lcd.print("     (*_*)");
    delay(35);
  }
  if (loadstate==LOW )  {
    digitalWrite(led, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("--Light Is OFF--");
    lcd.setCursor(0, 4);
    lcd.print("     (-_-)");
    delay(35);
  }


  //distance mesuring logic
    while (switc == HIGH){
    //ultra sonic date collection
  digitalWrite(trig,HIGH);
  delayMicroseconds(200);
  digitalWrite(trig,LOW);
  Zeit = pulseIn(echo,HIGH);
  Strecke=Zeit*0.017;
  digitalWrite(trig,LOW);
  delayMicroseconds(200);
    if ( Strecke <= distance_one ){
       lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Distance in cm:");
      Serial.print("Entfernung in cm:   ");
      lcd.setCursor(0,4);
      lcd.print(Strecke);
      Serial.println(Strecke);
      delay(300);
      lcd.clear();
     }
    else {
      lcd.setCursor(0,0);
      lcd.print("Distance < 53cm");
      lcd.setCursor(0,4);
      lcd.print("(^_^)(*_*)[-_-] ");
      delay(300);
      lcd.clear();
    }
  }
 
}

    
