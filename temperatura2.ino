#include "DHT.h"
#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int rele = 2;
bool coolerLigado = false; // Variável para rastrear o estado do cooler

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH); // Inicia com o cooler desligado
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if(isnan(t) || isnan(h)){
    Serial.println("Falha ao ler DHT");
  }
  else{
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" °C");
    
    // Lógica de controle
    if(t >= 31.0 && !coolerLigado){
      digitalWrite(rele, LOW); // Liga o cooler
      coolerLigado = true;
      Serial.println("Cooler LIGADO - Temperatura >= 31°C");
    }
    else if(t <= 30.5 && coolerLigado){
      digitalWrite(rele, HIGH); // Desliga o cooler
      coolerLigado = false;
      Serial.println("Cooler DESLIGADO - Temperatura <= 30.5°C");
    }
  }
  delay(2000); // Aguarda 2 segundos entre as leituras
}