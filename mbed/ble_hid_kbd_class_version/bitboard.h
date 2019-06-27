#ifndef BITBOARD_H
#define BITBOARD_H

#include "MicroBit.h"
#include "mbed.h"
#include "ble/BLE.h"
#include "KeyboardService.h"
#include "MicroBitPin.h"
#include "examples_common.h"
#include "MicroBit.h"
#include <string>

class bitboard {
protected:
    KeyboardService* kbdServicePtr;
    const char* DEVICE_NAME;
    const char* SHORT_DEVICE_NAME;
    uint8_t Key;
    uint8_t Modifier;
public:
    MicroBit &uBit;
//    BLE &ble;
    bitboard(
    MicroBit &_uBit,
//    BLE &_ble,
    KeyboardService* _kbdServicePtr);
    ~bitboard();

    void init();
    void onDisconnect(const Gap::DisconnectionCallbackParams_t *params);
    void onConnect(const Gap::ConnectionCallbackParams_t *params);
    void send_string(std::string str);
    void send_keypress();
    uint8_t get_keycode(char c);

};



#endif
