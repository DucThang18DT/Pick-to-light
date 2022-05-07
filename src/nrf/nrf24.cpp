#include "nrf24.h"

NRF24::NRF24(const byte* inAddress, int inPort){
    address = new byte[strlen((const char*)inAddress) +1];
    address = inAddress;
    port = inPort;
}

NRF24::~NRF24(){
    delete [] address;
}

void NRF24::init(){
    radio = RF24(CE_PIN, CSN_PIN);
    while (!radio.begin())
    {
        Serial.println("Cannot start module...!");
        delay(200);
    }
    radio.openReadingPipe(NUM_PIPE, address);
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