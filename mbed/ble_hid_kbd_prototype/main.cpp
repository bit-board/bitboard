/* mbed Microcontroller Library
 * Copyright (c) 2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "mbed.h"
#include "ble/BLE.h"
#include "KeyboardService.h"
#include "MicroBitPin.h"
#include "examples_common.h"
#include "MicroBit.h"
/**
 * This program implements a complete HID-over-Gatt Profile:
 *  - HID is provided by KeyboardService
 *  - Battery Service
 *  - Device Information Service
 *
 * Complete strings can be sent over BLE using printf. Please note, however, than a 12char string
 * will take about 500ms to transmit, principally because of the limited notification rate in BLE.
 * KeyboardService uses a circular buffer to store the strings to send, and calls to putc will fail
 * once this buffer is full. This will result in partial strings being sent to the client.
 */
 
 //The micro:bit has a matrixed display, this is a simple way to use some LEDs on it
DigitalOut col9(P0_12, 0);
 
DigitalOut waiting_led(P0_13);
DigitalOut connected_led(P0_15);
 
InterruptIn button1(BUTTON_A);
InterruptIn button2(BUTTON_B);
 
//InterruptIn key1(MICROBIT_PIN_P0);
// Try to use external signal, rather than button a&b as keys
 
BLE ble;
KeyboardService *kbdServicePtr;
 
static const char DEVICE_NAME[] = "micro:bit xx316";
static const char SHORT_DEVICE_NAME[] = "kbd1";
 
static void onDisconnect(const Gap::DisconnectionCallbackParams_t *params)
{
    HID_DEBUG("disconnected\r\n");
    connected_led = 0;
 
    ble.gap().startAdvertising(); // restart advertising
}
 
static void onConnect(const Gap::ConnectionCallbackParams_t *params)
{
    HID_DEBUG("connected\r\n");
    waiting_led = false;
}
 
static void waiting() {
    if (!kbdServicePtr->isConnected())
        waiting_led = !waiting_led;
    else
        connected_led = !connected_led;
}
 
void send_string(const char * c) {
    if (!kbdServicePtr)
        return;
 
    if (!kbdServicePtr->isConnected()) {
        HID_DEBUG("we haven't connected yet...");
    } else {
        int len = strlen(c);
        kbdServicePtr->printf(c);
        HID_DEBUG("sending %d chars\r\n", len);
    }
}
 
void send_stuff() {
    send_string("n");
    wait(0.1);
}
 
void send_more_stuff() {
    send_string("p");
    wait(0.1);
}
 
 
void send_one(){
    inputReportData[0] = 0;
    inputReportData[2] = 0x1e;
    kbdServicePtr->send(inputReportData); //key down event?
    kbdServicePtr->send(emptyInputReportData); // key up event?
    wait(0.1);
}
 
void send_zero(){// testing input from pins
    inputReportData[0] = 0;
    inputReportData[2] = 0x27;
    kbdServicePtr->send(inputReportData); //key down event?
    kbdServicePtr->send(emptyInputReportData); // key up event?
    wait(0.1);
}
 
void send_up(){// testing input from pins
    inputReportData[0] = 0;
    inputReportData[2] = 0x52;
    kbdServicePtr->send(inputReportData); //key down event?
    kbdServicePtr->send(emptyInputReportData); // key up event?
    wait(0.1);
}
 
void send_down(){// testing input from pins
   // kbdServicePtr->putc(DownArrow);
    inputReportData[0] = 0;
    inputReportData[2] = 0x51;
    kbdServicePtr->send(inputReportData);
    kbdServicePtr->send(emptyInputReportData);
    wait(0.1);
}
 
void send_left(){// testing input from pins
    inputReportData[0] = 0;
    inputReportData[2] = 0x50;
    kbdServicePtr->send(inputReportData);
    kbdServicePtr->send(emptyInputReportData);
    wait(0.1);
}
 
void send_right(){// testing input from pins
    inputReportData[0] = 0;
    inputReportData[2] = 0x4f;
    kbdServicePtr->send(inputReportData);
    kbdServicePtr->send(emptyInputReportData);
    wait(0.1);
}
 
void send_space(){// testing input from pins
    inputReportData[0] = 0;
    inputReportData[2] = 0x2c;
    kbdServicePtr->send(inputReportData);
    kbdServicePtr->send(emptyInputReportData);
    wait(0.1);
}
 
void send_release(){
    kbdServicePtr->send(emptyInputReportData);
    wait(0.1);
}
    
 
//#define MICROBIT_PIN_P13                    P0_23       //SCK
//InterruptIn key2(MICROBIT_PIN_P13);
DigitalIn touch1(MICROBIT_PIN_P13);
//#define MICROBIT_PIN_P0                     P0_3  
AnalogIn x_axis(MICROBIT_PIN_P0);
//#define MICROBIT_PIN_P1                     P0_2
AnalogIn y_axis(MICROBIT_PIN_P1);
 
//Thread joystick_control_thread; // "Identifier "Thread" is undefined"???
 
void JoystickControl(){
    float x,y;
//    
//    if (touch1 == 1) send_one();
//        if (touch1 == 0) send_zero();
 
    x = x_axis.read();
    if (x < 0.05f) send_left();
    if (x > 0.95f) send_right();
    
    y = y_axis.read();
    if (y < 0.05f) send_down();
    if (y > 0.95f) send_up();
    
    wait(0.05);
}
 
void touch_control(){
    if (touch1 == 1) send_space();
    wait(0.05);
}
 
//void BLE_fiber(){
//    while (true) {
//        ble.waitForEvent();     
//    }
//}
 
int main(){
    //create_fiber(JoystickControl);
//    create_fiber(BLE_fiber);
    Ticker heartbeat;
 
    button1.rise(send_one);
    button2.rise(send_zero);
 
    HID_DEBUG("initialising ticker\r\n");
 
    heartbeat.attach(waiting, 1);
 
    HID_DEBUG("initialising ble\r\n");
    ble.init();
 
    ble.gap().onDisconnection(onDisconnect);
    ble.gap().onConnection(onConnect);
 
    initializeSecurity(ble);
 
    HID_DEBUG("adding hid service\r\n");
    KeyboardService kbdService(ble);
    kbdServicePtr = &kbdService;
 
    HID_DEBUG("adding device info and battery service\r\n");
    initializeHOGP(ble);
 
    HID_DEBUG("setting up gap\r\n");
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::KEYBOARD);
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME,
                                           (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::SHORTENED_LOCAL_NAME,
                                           (uint8_t *)SHORT_DEVICE_NAME, sizeof(SHORT_DEVICE_NAME));
    ble.gap().setDeviceName((const uint8_t *)DEVICE_NAME);
 
    HID_DEBUG("advertising\r\n");
    ble.gap().startAdvertising();
    
    float x,y;
    
    while (true) {
        ble.waitForEvent();  
        
        JoystickControl();  
        touch_control();
    }
//    release_fiber();
}