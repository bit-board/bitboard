#include "MicroBit.h"
#include "bitboard.h"

MicroBit uBit;
//BLE ble;
KeyboardService* kbdServicePtr;

int main()
{
    HID_DEBUG("starting program \r\n");
    uBit.init();
    bitboard btboard(
        uBit,
//        ble,
        kbdServicePtr);
//    bitboard* btboardPtr;
//    btboardPtr = &btboard;
    HID_DEBUG("init bitboard object\r\n");
    btboard.init();
    
//    button1.rise(btboardPtr, &bitboard::send_keypress);
//    button1.rise(btboardPtr, &bitboard::send_keypress);
    while(1){
//        ble.waitForEvent();  
        wait(2);
        btboard.send_keypress();
//        btboard.send_string("Quick Brown Fox ");
    }
}

