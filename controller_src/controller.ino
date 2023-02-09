#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
bool prev = false;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(4, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = digitalRead(4);
  if (!prev && value) {
     radio.write(&value, sizeof(int));
     Serial.print("Sent 1");
     Serial.print("\n");
     prev = true;
  }
  else if (prev && !value) {
    Serial.print("Sent 0");
    Serial.print("\n");
    radio.write(&value, sizeof(int));
    prev = false;
  }
}
