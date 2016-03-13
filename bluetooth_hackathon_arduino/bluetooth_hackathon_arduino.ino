#include <SoftwareSerial.h>// import the serial library

SoftwareSerial Genotronex(7, 8); // RX, TX

int ledpin=13; // led on D13 will show blink on / off
int motorpin=12;
int SOS=2;
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  Genotronex.begin(115200);
  Genotronex.println("\nBluetooth On please press 1 or 0 blink LED ..");
  //attachInterrupt(digitalPinToInterrupt(SOS), blink, RISING);
  pinMode(ledpin,OUTPUT);
  pinMode(SOS, INPUT_PULLUP);
  pinMode(motorpin,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  digitalWrite(motorpin,LOW);
}

void blink() {
    long current=millis();
    bool accident=false;
    while (millis()-current<5000){
      if (digitalRead(SOS)==HIGH){
        accident=true;
        break;
      }
    }
    if (accident==false){
      Genotronex.println("H");
      delay(500);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  int index = 0;
  char c;
  if (digitalRead(SOS)==LOW) blink();
  if (Genotronex.available()>0){
    BluetoothData=Genotronex.read();
    c = BluetoothData;
    if (c=='L'){
      digitalWrite(ledpin,HIGH);
      digitalWrite(motorpin,HIGH);
      delay(250);
      digitalWrite(ledpin,LOW); digitalWrite(motorpin,LOW);
    }else if (c=='R'){
      digitalWrite(ledpin,HIGH); digitalWrite(motorpin,HIGH);
      delay(250);
      digitalWrite(ledpin,LOW);digitalWrite(motorpin,LOW);
      delay(250);
      digitalWrite(ledpin,HIGH);digitalWrite(motorpin,HIGH);
      delay(250);
      digitalWrite(ledpin,LOW);digitalWrite(motorpin,LOW);
    }else if (c=='S'){
      digitalWrite(ledpin,HIGH); digitalWrite(motorpin,HIGH);
      delay(750);
      digitalWrite(ledpin,LOW);digitalWrite(motorpin,LOW);
    }
    else if (c=='U'){
      digitalWrite(ledpin,HIGH); digitalWrite(motorpin,HIGH);
      delay(750);
      digitalWrite(ledpin,LOW);digitalWrite(motorpin,LOW);
      delay(750);
      digitalWrite(ledpin,HIGH); digitalWrite(motorpin,HIGH);
      delay(750);
      digitalWrite(ledpin,LOW);digitalWrite(motorpin,LOW);
    }
    //Genotronex.println(BluetoothData);
  }
  delay(100);// prepare for next data ...
}
