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
     Serial.println("Sent 1");
     prev = true;
  }
  else if (prev && !value) {
    Serial.println("Sent 0");
    radio.write(&value, sizeof(int));
    prev = false;
  }
}

void sendMoveInstruction(char dir) {

  int s = 1; 
  int l = 2;
  int r = 3;

  if(dir == 'f') {
    radio.write(&s, sizeof(int));
  }

  if(dir == 'r') {
    radio.write(&l, sizeof(int));
  }

  if(dir == 'l') {
    radio.write(&r, sizeof(int));
  }
}
