#ifndef _MYTASK_H_
#define _MYTASK_H_

    #include <fbInter/FBRtInteraction.h>
    #include <myWifi/myWifi.h>
    #include <nrf/nrf24.h>

    static NRF24 rf24 = NRF24(CHANNEL_READ_ADDRESS, CHANNEL_SEND_ADDRESS, CHANEL_PORT);

    void gWayInit();
    void sendDataSendToCtler();
    void sendDataToCloud(char* list);
    void readDataFromCloud();
    void readDataFromCtler(char* list);
    
#endif