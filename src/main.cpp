#include "task/task.h"
#include "port/port.h"
#include "nrf/nrf24.h"
//Task task = Task();
//NRF24 NRF1;
// NRF24 NRF2;
RF24 radio(7, 8); // CE, CSN
const byte diachi[][6] = {"12345", "10000"}; //0, 1

int button = 6;
boolean button_value;

int led = 5;
boolean nutnhan = 0;

static void init123()
{
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }   
  radio.openWritingPipe(diachi[0]);
  //Chỉ có thể mở 1 đường ghi
  //Lệnh openWritingPipe có số đường truyền mặc định là 0
  //Mở 1 kênh có địa chỉ 10000 trên đường truyền 0
  //kênh này chỉ ghi data trên địa chỉ 10000   
  radio.openReadingPipe(1, diachi[1]);
  //Có thể mở 6 đường đọc cùng lúc
  //Nhưng đường 0 mặc định dùng cho ghi
  //Lệnh openReadingPipe có thể mở đường truyền từ 1-5
  //Đọc data của địa chỉ 12345 trên đường truyền 1
     
  radio.setPALevel(RF24_PA_MIN); //Cài bộ khuyết địa công suất ở mức MIN
  radio.setChannel(85);
  radio.setDataRate(RF24_250KBPS);    
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
}
void setup() {
    Serial.begin(9600);
    pinMode(button, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    init123();
}

void loop() {
    
  radio.stopListening();
  button_value = digitalRead(button);
  Serial.print("Gui nut nhan 2: "); Serial.println(button_value);
  radio.write(&button_value, sizeof(button_value));
  delay(10);

  radio.startListening();
  //while(!radio.available());
  radio.read(&nutnhan, sizeof(nutnhan));
  Serial.print("Nhan nut nhan 1: "); Serial.println(nutnhan);
  if(nutnhan == HIGH)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
  delay(10);
  
    // button_value = digitalRead(button);
    // if(button_value == 0)
    // {
    //     Serial.print("Gui nut nhan 1: "); Serial.println(button_value);
    //     NRF1.sendData("0");
    // }
    // else
    // {
    //     Serial.print("Gui nut nhan 1: "); Serial.println(button_value);
    //     NRF1.sendData("1");
    // }

  
    // delay(10);

    // nutnhan = NRF1.readData()[0];
    // Serial.print("Nhan nut nhan 2: "); Serial.println(nutnhan);
    // if(nutnhan == "1")
    // {
    //     digitalWrite(led,HIGH);
    // }
    // else
    // {
    //     digitalWrite(led,LOW);
    // }
    // delay(10);
    
}