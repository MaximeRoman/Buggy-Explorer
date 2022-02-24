#include<SoftwareSerial.h>
#include <DHT.h>
#define RX 3
#define TX 2
#define DHTPIN 6     // branchée sur la pin D6

// Le type de DHT utilisé 
#define DHTTYPE    DHT22     // ici on utilise DHT22 

//Instanciation de la librairie DHT
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial BlueT(RX,TX);

String answer;
String message;

void setup() {
  Serial.begin(9600);
  Serial.println("5");
  Serial.println("Bonjour -Pret pour les commandes AT");
  Serial.println("Pour tester");
  Serial.println();
  dht.begin();
  BlueT.begin(9600);
}

void loop() {
  

  //lire les réponses de l'esclave
  while (BlueT.available()){
    delay(10);
    if (BlueT.available()>0) {
     char c = BlueT.read();
     answer += c;
    }
  }
   // Lecture des données
  float tauxHumidite = dht.readHumidity();        // Lecture du taux d'humidité zn pourcentage
  float tempCelsius = dht.readTemperature();   // Lecture de la température en degrés Celsius

  // Vérification
  if (isnan(tauxHumidite) || isnan(tempCelsius)) {
    Serial.println("Aucune valeur retournée. vérifier le branchement");
    delay(2000);
    return;     // Si aucune valeur reçu, on a une attente de deux secondes, puis redémarrage de cette fonction
  }
  
  // Calcul de la température ressentie
  float tempRessentieCelsius = dht.computeHeatIndex(tempCelsius, tauxHumidite, false); // le false permet de montrer qu'on est en celcius et non en fahrenheit
  
  // Affichage des valeurs
  Serial.print("Humidité = "); Serial.print(tauxHumidite); Serial.println(" %");
  Serial.print("Température = "); Serial.print(tempCelsius); Serial.println(" °C");
  Serial.print("Température ressentie = "); Serial.print(tempRessentieCelsius); Serial.println(" °C");
  Serial.println();

 //envoyer data vers esclave
    Serial.print("Le maître envoie : ");
    Serial.println(tempCelsius);
    BlueT.print(tempCelsius);
  
    //Serial.print("Le maître envoie : ");
    //Serial.println(tauxHumidite);
    //BlueT.print(tauxHumidite);
  
  
    //Serial.print("Le maître envoie : ");
    //Serial.println(tempRessentieCelsius);
    //BlueT.print(tempRessentieCelsius);
  
  
  //Send answer to monitor
  if(answer!=""){
    Serial.print("L'esclave reçoit : ");
    Serial.println(answer);
    answer="";
  } 

 
  delay(2000);

 Serial.flush();
}
