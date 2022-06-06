#include "task/task.h"
Task task = Task();

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
    // Serial.begin(9600);
    task.addValueToData();
    task.sendDataToSlave();
    delay(200);
    task.sendDataToSlave();
}

void loop() {
    
    // Serial.print("size of test = ");
    // Serial.println(test.size());
    if (task.readDataFromGWay() == true){
        task.sendDataToSlave();
    }
    //Serial.println("Send to slave...");
    // task.sendDataToSlave();
}