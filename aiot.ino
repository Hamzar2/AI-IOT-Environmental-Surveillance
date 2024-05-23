#include <LiquidCrystal.h>
#include <DHT.h>
#include <FreqCount.h>

// Définir les broches et les constantes
#define DHT_PIN 13      // Broche du capteur DHT11
#define LDR_PIN A0     // Broche de la photorésistance
#define DHTTYPE DHT11  // Type de capteur DHT (DHT11 ou DHT22)

// Initialiser l'écran LCD I2C
LiquidCrystal lcd(7,6,9,4,3,2);  // Adresse I2C et dimensions de l'écran

// Initialiser le capteur DHT
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  // Initialiser le port série
  Serial.begin(9600);
  
  // Initialiser l'écran LCD
  lcd.begin(16,5);
  
  // Initialiser le capteur DHT
  dht.begin();
  FreqCount.begin(2000);

  pinMode(11,INPUT);
}

void loop() {
  // Lire les valeurs du capteur DHT
  float temperature = dht.readTemperature();
  float humidite = dht.readHumidity();

  // Lire la valeur de la photorésistance
  int luminosite = digitalRead(11);
  // int wind = digitalRead(ANEMOMETRE);

  int freq = FreqCount.read();
  int windSpeed = freq * 2.4 ;
  // Afficher les valeurs sur l'écran LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidite);
  lcd.print("%");
  lcd.setCursor(0, 2);
  lcd.print("Lum: ");
  lcd.print(luminosite);
 
  

  // Envoyer les données au port série
  // Serial.print("Temperature:");
  Serial.print(temperature);
  Serial.print(",");
  // Serial.print("Humidite:");
  Serial.print(humidite);
  Serial.print(",");
  // Serial.print("Luminosite:");
  Serial.print(luminosite);
  Serial.print(",");
  Serial.println(freq);
  

  delay(2000);  // Attendre 2 secondes avant la prochaine lecture
}