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

#include "ble/services/BatteryService.h"

#include "HIDDeviceInformationService.h"

#include "examples_common.h"

static void passkeyDisplayCallback(Gap::Handle_t handle, const SecurityManager::Passkey_t passkey)
{
    printf("Input passKey: ");
    for (unsigned i = 0; i < Gap::ADDR_LEN; i++) {
        printf("%c", passkey[i]);
    }
    printf("\r\n");
}

static void securitySetupCompletedCallback(Gap::Handle_t handle, SecurityManager::SecurityCompletionStatus_t status)
{
    if (status == SecurityManager::SEC_STATUS_SUCCESS) {
        printf("Security success %d\r\n", status);
    } else {
        printf("Security failed %d\r\n", status);
    }
}

static void securitySetupInitiatedCallback(Gap::Handle_t, bool allowBonding, bool requireMITM, SecurityManager::SecurityIOCapabilities_t iocaps)
{
    printf("Security setup initiated\r\n");
}

void initializeSecurity(BLE &ble)
{
    bool enableBonding = true;
    bool requireMITM = HID_SECURITY_REQUIRE_MITM;
    HID_DEBUG("security callback 1\r\n");
    ble.securityManager().onSecuritySetupInitiated(securitySetupInitiatedCallback);
    HID_DEBUG("security callback 2\r\n");
    ble.securityManager().onPasskeyDisplay(passkeyDisplayCallback);
    HID_DEBUG("security callback 3\r\n");
    ble.securityManager().onSecuritySetupCompleted(securitySetupCompletedCallback);
    HID_DEBUG("security manager init\r\n");
    ble.securityManager().init(enableBonding, requireMITM, HID_SECURITY_IOCAPS);
}

void initializeHOGP(BLE &ble)
{
    printf("HOGP 1\r\n");
    static const uint16_t uuid16_list[] =  {GattService::UUID_HUMAN_INTERFACE_DEVICE_SERVICE,
        GattService::UUID_DEVICE_INFORMATION_SERVICE,
        GattService::UUID_BATTERY_SERVICE};
    printf("HOGP 2\r\n");
//    PnPID_t pnpID;
    printf("HOGP 3\r\n");
//    pnpID.vendorID_source = 0x2; // from the USB Implementer's Forum
    printf("HOGP 4\r\n");
//    pnpID.vendorID = 0x0D28; // NXP
//    pnpID.productID = 0x0204; // CMSIS-DAP (well, it's a keyboard but oh well)
//    pnpID.productVersion = 0x0100; // v1.0
    printf("HOGP 5\r\n");
    //already in microbit init (LIne 351, MicrobitBLEManager)
//    HIDDeviceInformationService deviceInfo(ble, "ARM", "m1", "abc", "def", "ghi", "jkl", NULL);

    printf("HOGP 6\r\n");
    BatteryService batteryInfo(ble, 90);
    
    printf("HOGP 7\r\n");
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED |
            GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    printf("HOGP 8\r\n");
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS,
            (uint8_t *)uuid16_list, sizeof(uuid16_list));

    // see 5.1.2: HID over GATT Specification (pg. 25)
    printf("HOGP 9\r\n");
    ble.gap().setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    // 30ms to 50ms is recommended (5.1.2)
    printf("HOGP 10\r\n");
    ble.gap().setAdvertisingInterval(50);
}

