//bibliotecas
#include <DHT.h>
#include <DHT_U.h>

//sensor de temperatura e umidade
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//sensor LDR
#define LDRPIN A2
int valorLuz;

//leds
#define ledBranco 5
#define ledAmarelo 6

//variaveis comuns
#define bSwitch 11
#define bLeitura 2
#define bTrabalho 3
#define bAfazeres  4
int leitura = 0, trab = 0, afazeres = 0, sw = 0;
float h, t;



void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(ledBranco, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(LDRPIN, INPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(bSwitch, INPUT);
  pinMode(bLeitura, INPUT);
  pinMode(bTrabalho, INPUT);
  pinMode(bAfazeres, INPUT);
}

void loop() {
  TempUmid();
  LDR();
  
  //leitura
  if (bLeitura == 1) {
    leitura = 1;

  }
  else if (bLeitura == 0) {
    leitura = 0;
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAmarelo, LOW);
  }

  //trabalho
  if (bTrabalho == 1) {
    trab = 1;
  }
  else if (bTrabalho == 0) {
    trab = 0;
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAmarelo, LOW);
  }

  // afazeres
  if (bAfazeres == 1) {
    afazeres = 1;
  }
  else if (bAfazeres == 0) {
    afazeres = 0;
    digitalWrite(ledBranco, LOW);
    digitalWrite(ledAmarelo, LOW);
  }

  if (bSwitch == 1) {
    if (valorLuz > 700) {
      digitalWrite(ledBranco,HIGH );
      digitalWrite(ledAmarelo,HIGH) ;
    }
    else {
      digitalWrite(ledBranco, LOW);
      digitalWrite(ledAmarelo, LOW);
    }
  }
  
  if (bSwitch == 0) {
    if (leitura == 1) {
      digitalWrite(ledBranco,HIGH );
      digitalWrite(ledAmarelo, LOW);
    }
    if (trab == 1) {
      digitalWrite(ledBranco,HIGH );
      digitalWrite(ledAmarelo, 150);
    }
    if (afazeres == 1) {
      digitalWrite(ledBranco, 10);
      digitalWrite(ledAmarelo, HIGH);
    }
  }
}



void TempUmid () {
  //armazenamento da temperatura e da umidade, a leitura do sensor leva no maximo 250ms mas a informaçao chegar pode levar 2s
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.print("Umidade: ");
  Serial.println(h);
  Serial.print("Temperatura: ");
  Serial.println(t);
  delay(500);
}

void LDR() {
  valorLuz = analogRead(LDRPIN);
  //Serial.print("luz: ");
  //Serial.println(valorLuz);
  //delay(300);
}
