#include "nrf24.h"

#define CE_PIN      15
#define CSN_PIN     2
#define NUM_PIPE 1
#define  TXT_MAX_LEN 100


NRF24::NRF24(){

}

NRF24::NRF24(const char* inReadAddress, const char* inWriteAddress, int inPort){
  Serial.begin(9600);
    Serial.println("\n--- NRF Init ---");
    //readAddress = new char[strlen(inReadAddress)];
    //strcpy(readAddress, inReadAddress);
    // readAddress = inReadAddress;
    Serial.print("\nread Add: ");
    Serial.println(CHANNEL_READ_ADDRESS);
    //writeAddress = new char[strlen(inWriteAddress)];
    //strcpy(writeAddress, inWriteAddress);
    // writeAddress = inWriteAddress;
    Serial.print("\nwrite Add: ");
    Serial.println(CHANNEL_SEND_ADDRESS);
    port = inPort;
    init();
    Serial.println("\n--- End NRF Init ---");
}

NRF24::~NRF24(){
    // delete [] readAddress;
    // delete [] writeAddress;
}

void NRF24::init(){
    radio = RF24(CE_PIN, CSN_PIN);
    while (!radio.begin())
    {
        Serial.println("Cannot start module...!");
        delay(200);
    }
    radio.openReadingPipe(NUM_PIPE, (byte*)CHANNEL_READ_ADDRESS);
    radio.openWritingPipe((byte*)CHANNEL_SEND_ADDRESS);
    radio.setPALevel(RF24_PA_MIN); 
    radio.setChannel(port); 
    radio.setDataRate(RF24_250KBPS); 
    radio.startListening(); 
    if(!radio.available())
    {
        Serial.println("Cannot connect to TX...!");
        Serial.println("Waiting...");
    } 
}

char* NRF24::readData(){
  char* text = new char[TXT_MAX_LEN];
  memset(text, 0, TXT_MAX_LEN);
  if(radio.available())
  {
    radio.read(text, TXT_MAX_LEN); 
  }
  return text;
}

void NRF24::sendData(const char* inData){
  radio.stopListening();
  radio.write(inData, strlen(inData));
  radio.startListening();
}