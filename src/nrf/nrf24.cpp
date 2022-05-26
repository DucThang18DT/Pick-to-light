#include "nrf24.h"

#define CE_PIN  8
#define CSN_PIN 9
#define NUM_PIPE 1
#define  TXT_MAX_LEN 100


NRF24::NRF24(){

}

NRF24::NRF24(const byte* inReadAddress, const byte* inWriteAddress, int inPort){
    readAddress = new byte[strlen((const char*)inReadAddress) +1];
    readAddress = inReadAddress;
    writeAddress = new byte[strlen((const char*)inWriteAddress) +1];
    writeAddress = inWriteAddress;
    port = inPort;
    init();
}

NRF24::~NRF24(){
    delete [] readAddress;
    delete [] writeAddress;
}

void NRF24::init(){
    radio = RF24(CE_PIN, CSN_PIN);
    while (!radio.begin())
    {
        Serial.println("Cannot start module...!");
        delay(200);
    }
    radio.openReadingPipe(NUM_PIPE, readAddress);
    radio.openWritingPipe(writeAddress);
  // Moi module RF24L01 co 6 duong truyen (tu 0 den 5)
  // Duong truyen 0 da dung cho viec ghi(mac dinh)
  // Vi vay chi dung 1-5, neu dung 0 se bi chong lan
  // mo kenh co dia chi la 00001 tren duong truyen 1 
  // kenh nay chi doc data tren dia chi 00001
    radio.setPALevel(RF24_PA_MIN); // cai dat bo khuech dai cong suat o muc MAX, HiGH, LOW, MIN (0, -6, -12, -18 dBm)
    radio.setChannel(port); // 125 kenh tu 0-124, TX va RX phai cung kenh
                        // 2.4GHz ~ 2400MHz, buoc kenh la 1MHz
                        // setChannel(80) => 2480MHz
                        // Cao nhat la 2525MHz, tuc la 2.525GHz
    radio.setDataRate(RF24_250KBPS); //Toc do truyen du lieu trong khong khi 
                                   // 250Kbps, 1Mbps, 2Mbps
                                   // 250 thap nhat nhung truyen xa, 1Mb va 2Mb manh nhung truyen khong xa
    radio.startListening(); // cai dat module la RX
    if(!radio.available())
    {
        Serial.println("Cannot connect to TX...!");
        Serial.println("Waiting...");
    } 
}

char* NRF24::readData(){
    if(radio.available())
  {
    char text[TXT_MAX_LEN] = ""; 
    radio.read(&text,sizeof(text)); // Doc du lieu thu duoc
    return text;
  }
  return '\0';
}

void NRF24::sendData(const char* inData){
  radio.stopListening();
  radio.write(inData, sizeof(*inData));
  radio.startListening();
}