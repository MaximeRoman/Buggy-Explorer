#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
#define RX 11
#define TX 10

String message;
float t=0;
float h=0;

SoftwareSerial BlueT(RX,TX);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup() {
  Serial.begin(9600);
  Serial.println("6");
  lcd.begin(20, 4);
  BlueT.begin(9600);
}

void loop() {
  if (BlueT.available()){
    Data=BlueT.read();
    if (Data=='A') {
      PWM=BlueT.parseInt();
      Serial.println(PWM);
      analogWrite(LED, PWM);}
  //Humi=BleuT.read();
  //res=BleuT.read();

  }
  
  //Affichages : 
  // Ligne 1: 
  lcd.setCursor(0, 0); 
  // positionne le curseur à la colonne 1 et à la ligne 1 
  lcd.print("Humidite: ");
  lcd.print(t); 
  //lcd.setCursor(10, 0); 
  //lcd.print(h); 
  //lcd.setCursor(15, 0); 
  //lcd.print("%");
  //lcd.setCursor(0,2);
  //lcd.print("mode :");
  //lcd.setCursor(10,2);
  //lcd.print("sport");


  // Ligne 2: 
  //lcd.setCursor(0, 1); 
  // positionne le curseur à la colonne 1 et à la ligne 2 
  //lcd.print("Temp: "); 
  //lcd.setCursor(10, 1); 
  //lcd.print(t); 
  
  delay(3000);
}
