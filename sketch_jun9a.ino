#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 2, 3, 4, 5);

#include <Servo.h>
Servo cover;

#include<SoftwareSerial.h>
SoftwareSerial mySerial(10,11); // gsm

int gas=0;

// USS PIN DESCRIPTION

const int trigPin1 = A5 ; // OUTSIDE A3 
const int echoPin1 = A4; // OUTSIDE A2 

const int trigPin2 = A3 ; // INSIDE A1
const int echoPin2 = A2; // INSIDE  A0

long duration1;
int distance1;

long duration2;
int distance2;

// NODE MCU VARIABLES

int a=0, s =1;
String finalCode;
String a1,b1,c1;

void setup() 
{
 Serial.begin(9600); // BEGIN SERIAL MONITOR WITH 9600 BAUDRATE // IOT NODEMCU
 mySerial.begin(9600); // GSM
 
  cover.attach(9); //servo motor connected
  cover.write(70); //intial servo motor close

  pinMode(12,OUTPUT); // GREEN
  pinMode(13,OUTPUT); // BUZZER

  digitalWrite(12,LOW); // GREEN OFF
  digitalWrite(13,LOW);// BUZZER OFF

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" ANALYTIC  BASED ");
  lcd.setCursor(0, 1);
  lcd.print("GARBAGE MONTORING");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  SYSTEM  USING  ");
  lcd.setCursor(0, 1);
  lcd.print("   GSM AND IOT  ");
  delay(1000); 

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" GARBAGE  LEVEL ");
  delay(1000); 
  
}

void loop() 
{ 
  gas=analogRead(A0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GAS LEVEL : ");
  lcd.print(gas);
  
  if(gas>800)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GAS LEVEL HIGH");
  digitalWrite(13,HIGH);  
  delay(1000);
  }
  else
  {
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  }
  delay(1000); 
  
  level();
  obstacle();
  upload();
}

void obstacle()
{
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);

digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);

duration1 = pulseIn(echoPin1, HIGH);
distance1= duration1*0.034/2;

if(distance1<25) // LID OPEN AND CLOSE IS DISTANCE IS <25 CM
{
  if(s == 1)
  {
  cover.attach(9); 
  digitalWrite(13,HIGH);
  delay(400);
  digitalWrite(13,LOW);
  cover.write(0);
  delay(2000);
  cover.write(70);
  delay(2000);
  cover.detach(); 
  }
} 
}

void level()
{
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);

digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);

duration2 = pulseIn(echoPin2, HIGH);
distance2= duration2*0.034/2;

if(distance2 > 100)
{
  distance2 = 100;
}

if(distance2<4) 
{
  lcd.setCursor(0, 1);
  lcd.print("   BIN FULL ");  
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  a=1;
  s=0;
  cover.detach(); 
  lcd.setCursor(0, 0);           
  lcd.print("SENDING SMS.....");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  mySerial.println("AT+CMGS=\"+918341231111\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("DUSTBIN No. 2456 IS FULL, PLEASE EMPTY IMMEDIATELY");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  lcd.setCursor(0, 1);           
  lcd.print("MESSAGE SENT");
  delay(1000);
  lcd.clear();
  delay(300);
}

else
{
  lcd.setCursor(0, 1);
  lcd.print("   BIN EMPTY");  
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  a=0;
  s=1;
  delay(200); 
}

}

void upload()
{
// SEND DATA TO NODE MCU

   a1=String(gas); // GAS LEVEL

   finalCode = a1 + "@";
   Serial.print(finalCode);
    delay(200);  
  }