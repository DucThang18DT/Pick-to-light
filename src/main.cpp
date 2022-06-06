#include <Arduino.h>
#include <myTask/myTask.h>

//unsigned long referenceTime;

void setup() {
  // Serial.begin(9600);
  Serial.println("Hello");
  gWayInit();
  // Serial.printf("\nRunning on core: ");
  // Serial.println(xPortGetCoreID());
}

void loop() {
  readDataFromCloud();
  if (strlen(listDevices) > 0){
    sendDataSendToCtler();
  }
  readDataFromCtler(listConfirm);
  if (strlen(listConfirm) > 0){
    sendDataToCloud(listConfirm);
  }
  delay(500);
}


// #include <Arduino.h>
// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// RF24 radio(15, 2); // CE, CSN
// const char diachi[][6] = {"00001", "00002"};

// // int button = 6;
// // boolean button_value;

// // int led = 5;
// // boolean nutnhan = 0;

// void setup() 
// {
//   Serial.begin(9600);

//   if (!radio.begin()) 
//   {
//     Serial.println("Module không khởi động được...!!");
//     while (1) {}
//   }   
//   radio.openWritingPipe((byte*)diachi[0]);
//   //Chỉ có thể mở 1 đường ghi
//   //Lệnh openWritingPipe có số đường truyền mặc định là 0
//   //Mở 1 kênh có địa chỉ 12345 trên đường truyền 0
//   //kênh này chỉ ghi data trên địa chỉ 12345   
//   radio.openReadingPipe(1, (byte*)diachi[1]);
//   //Có thể mở 6 đường đọc cùng lúc
//   //Nhưng đường 0 mặc định dùng cho ghi  
//   //Lệnh openReadingPipe có số đường truyền từ 1-5
//   //Đọc data của địa chỉ 10000 trên đường truyền 1  
  
//   radio.setPALevel(RF24_PA_MIN); //Cài bộ khuyết địa công suất ở mức MIN
//   radio.setChannel(85);
//   radio.setDataRate(RF24_250KBPS);    
//   if (!radio.available())
//   {
//     Serial.println("Chưa kết nối được với TX...!!");
//     Serial.println("CHỜ KẾT NỐI.......");
//   }
//   // pinMode(button, INPUT_PULLUP);
//   // pinMode(led, OUTPUT);
// }

// void loop() 
// {  
//   radio.stopListening(); //Ngưng nhận
//   const char text1[] = "HUY DEP GAI"; // tao mang chua chuoi ki tu
//   radio.write(&text1, sizeof(text1)); //Gui du lieu co trong mang text
//   Serial.println("Da gui module 2");
//   delay(10);
      
  
//   //while(!radio.available());
//   radio.startListening(); //Bắt đầu nhận
//   char text2[32] = ""; 
//   radio.read(&text2,sizeof(text2)); // Doc du lieu thu duoc
//   Serial.println(text2); // chuyen du lieu len cong Serial
//   delay(10); 
// }