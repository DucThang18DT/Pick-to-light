#ifndef _MYTASK_H_
#define _MYTASK_H_

    #include <fbInter/FBRtInteraction.h>
    #include <myWifi/myWifi.h>
    #include <nrf/nrf24.h>

    static NRF24 rf24 = NRF24((const byte*)CHANNEL_READ_ADDRESS, (const byte*)CHANNEL_SEND_ADDRESS, CHANEL_PORT);

     void init();
     void sendDataSendToCtler();
     void sendDataToCloud();
     void readDataFromCloud();
     void readDataFromCtler();
    
#endif