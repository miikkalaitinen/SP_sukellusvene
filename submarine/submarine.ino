#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int value = 0;
long cutoff = 0;
bool prev = false;

void setup() {
  Serial.begin(9600);
  Serial.println("S");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(2, OUTPUT);
}

void loop() {  
  if (cutoff > 100000) {
    digitalWrite(2, LOW);
    prev = false;
    value = 0;
    cutoff = 0; 
    Serial.println("Cutoff time reached, turning led OFF");
  }
  if (radio.available()) {
    radio.read(&value, sizeof(int));
  }
  if(!prev && value) {
    digitalWrite(2, HIGH);
    prev = true;
    Serial.println("Received 1, turning led ON");
    cutoff = 0;
  }
  else if (prev && !value) {
    digitalWrite(2, LOW);
    prev = false;
    Serial.println("Received 0, turning led OFF");
    cutoff = 0;
  }
  if(prev){
  cutoff++;
  }
}