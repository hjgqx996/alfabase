/**
 * © Copyright AlfaLoop Technology Co., Ltd. 2018
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/
#ifndef _DEV_ID_H_
#define _DEV_ID_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int devid_gen(uint8_t *id, int max_len);
int hwid_gen(uint8_t *id, int max_len);
int devid_reboot(void);
int devid_bootloader_mode(void);

#ifdef __cplusplus
}
#endif
#endif /* _DEV_ID_H_ */
