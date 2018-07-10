/*
* Copyright (C) 2016 AlfaLoop Technology Co., Ltd.
*
* Licensed under the Apache License, Version 2.0 (the "License";
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* 	  www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef __LSB_PROFILE_H_
#define __LSB_PROFILE_H_
#ifdef __cplusplus
extern "C" {
#endif

#define DEAULT_HWID 0x32, 0xAF, 0x51, 0x9E, 0x88
#define DEFAULT_DEVICE_MESSAGE 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '!'

/* LINE Simple Beacon Profile {A78D0001-F6C2-09A3-E9F9-128ABCA31297} */
const BleUuid128 gatt_alfa_lsb_service_uuid =
    BLE_UUID128_INIT(0x97, 0x12, 0xa3, 0xbc, 0x8a, 0x12, 0xF9, 0xE9,
                     0xa3, 0x09, 0xc2, 0xF6, 0x01, 0x00, 0x8D, 0xA7);
/* LINE Simple Beacon HWID {A78D0002-F6C2-09A3-E9F9-128ABCA31297} */
const BleUuid16 gatt_alfa_lsb_chr_hwid = BLE_UUID16_INIT(0x0002);

/* LINE Simple Beacon device message {A78D0003-F6C2-09A3-E9F9-128ABCA31297} */
const BleUuid16 gatt_alfa_lsb_chr_dm = BLE_UUID16_INIT(0x0003);

#ifdef __cplusplus
}
#endif
#endif /* __LSB_PROFILE_H_ */