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
#ifndef __ALFABASE_H_
#define __ALFABASE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
/*---------------------------------------------------------------------------*/
#define API_VERSION		1.1.1
/*---------------------------------------------------------------------------*//*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
// Standard C functions
void *memcpy(void *dest, const void *src, size_t n)
{
    char *dp = dest;
    const char *sp = src;
    while (n--)
        *dp++ = *sp++;
    return dest;
}
int memcmp(const void* s1, const void* s2,size_t n)
{
    const unsigned char *p1 = s1, *p2 = s2;
    while(n--)
        if( *p1 != *p2 )
            return *p1 - *p2;
        else
            p1++,p2++;
    return 0;
}
void *memchr(const void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char*)s;
    while( n-- )
        if( *p != (unsigned char)c )
            p++;
        else
            return p;
    return 0;
}
void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char tmp[n];
    memcpy(tmp,src,n);
    memcpy(dest,tmp,n);
    return dest;
}
void *memset(void *s, int c, size_t n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}
int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}
size_t strlen(const char *s) {
  const char *p = s;
  while (*s) ++s;
  return s - p;
}
int strncmp(const char* s1, const char* s2, size_t n)
{
    while(n--)
        if(*s1++!=*s2++)
            return *(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1);
    return 0;
}
/*---------------------------------------------------------------------------*/
// Error Code
#define ENONE		 	0   /* No error occur */

// System
#define EINTERNAL    	1   /* Internal Error */
#define ENOMEM       	2   /* No Memory for operation */
#define ENULLP       	3   /* Null Pointer */
#define EINVAL       	4   /* Invalid argument */
#define ENOREADY	 	  5   /* Not ready */
#define EINVALSTATE  	6   /* Invalid state, operation disallowed in this state */
#define ENOFOUND     	7   /* Not found */
#define ENOSUPPORT   	8   /* Not supported */
#define ETIME        	9   /* Timer expired (timeout) */
#define EPERM        	10  /* Operation not permitted */
#define EIO      	  	11  /* I/O error */
#define EFAULT       	12  /* Bad address */
#define EBUSY        	13  /* Device or resource busy */
#define EBADRQC      	14  /* Invalid request code */
#define EALREADY     	15  /* Operation already in progress */
#define EOVERFLOW    	16  /* Value too large for defined data type */
#define ELOAR			    17	/* Limit of available resource */
#define EDSNM			    18	/* Data size not match */


// File System
#define ENOENT       	30  /* No such file or directory */
#define EBADF        	31  /* Bad file number */
#define EROFS        	32  /* Read-only file system */
#define ENOTDIR      	33  /* Not a directory */
#define E2BIG        	34  /* Argument list too long */
#define ENOEXEC      	35  /* Exec format error */
#define EEXIST       	36  /* File exists */
#define EISDIR       	37  /* Is a directory */
#define EAPPEN       	38  /* Append faild */
#define EISCA         39  /* Insufficient storage capacity available.*/

// ELF Loader
#define EBEH       		40  /* Bad ELF header */
#define ENSYMT       	41  /* No symbol table */
#define ENSTRT       	42  /* No string table */
#define ENTXTSG       43  /* No text segment */
#define ESYMNF       	44  /* Symbol not found */
#define ESGNF       	45  /* Segment not found */
#define ENSTARTP      46  /* No starting point */

// Network
#define ENONET      	50  /* Machine is not on the network */
#define EADV        	51  /* Advertise error */
#define ECOMM       	52  /* Communication error on send */
#define EPROTO      	53  /* Protocol error */
#define EMULTIHOP   	54  /* Multihop attempted */
#define EBADMSG     	55  /* Not a data message */
#define EMSGSIZE    	56  /* Message too long */
#define ENOPROTOOPT 	57  /* Protocol not available */
#define EPROTONOSUPPORT 58  /* Protocol not supported */
#define ENETDOWN    	59  /* Network is down */
#define ENETUNREACH 	60  /* Network is unreachable */
#define ENETRESET   	61  /* Network dropped connection because of reset */
#define ECONNRESET  	62  /* Connection reset by peer */
#define ETIMEDOUT   	63  /* Connection timed out */
#define ECONNREFUSED  64  /* Connection refused */
#define EHOSTDOWN   	65  /* Host is down */
#define EHOSTUNREACH  66  /* No route to host */

/*---------------------------------------------------------------------------*/
// BleUuid
enum {
  BLE_UUID_TYPE_16 = 16,
  BLE_UUID_TYPE_128 = 128,
};

typedef struct {
  uint8_t type;
  uint16_t value;
} BleUuid16;

typedef struct {
  uint8_t type;
  uint8_t value[16];
} BleUuid128;

#define BLE_UUID16_INIT(uuid16)         \
    {                                   \
      .type = BLE_UUID_TYPE_16,        \
      .value = (uuid16),             \
    }

#define BLE_UUID128_INIT(uuid128...)    \
    {                                   \
      .type = BLE_UUID_TYPE_128,        \
      .value = { uuid128 },             \
    }

/*---------------------------------------------------------------------------*/
// BleDevice
#define BLE_DEVICE_ADDRESS_LEN           	6

typedef struct{
  uint8_t address[BLE_DEVICE_ADDRESS_LEN];
  uint8_t type;
} BleDevice;

/*---------------------------------------------------------------------------*/
// AdvDataBuilder
typedef struct {
  uint16_t  size;
  uint8_t   data[31];
} AdvData;

typedef struct {
  int (*addService16bitUUID)(AdvData *advdata, uint16_t uuid);
  int (*addServiceData)(AdvData *advdata, uint16_t uuid, uint8_t *data, uint8_t data_length);
  int (*addCompleteLocalName)(AdvData *advdata, uint8_t *name, uint8_t complete_name_length);
  int (*addShortLocalName)(AdvData *advdata, uint8_t *name, uint8_t short_name_length);
  int (*addManufacturerData)(AdvData *advdata, uint16_t manufacturerId, uint8_t *specificData, uint8_t length);
  int (*init)(AdvData *advdata);
  int (*initScanRsp)(AdvData *advdata);
} AdvDataBuilder;

AdvDataBuilder* CKAdvDataBuilder(void);
/*---------------------------------------------------------------------------*/
// BleAdapter
#define ADVERTISE_MAX_DATA_SIZE           31				// Maximum size of advertising data in octets.
#define BLE_GATT_MAX_CHARATERISTICS_NUM   5

#define BLE_GATT_SERVICE_UUID16                             0x1801
#define BLE_GATT_DESCRIPTOR_CFG_UUID16                      0x2902
#define BLE_GATT_MTU_SIZE_DEFAULT                           23
#define BLE_GATT_CHR_MAX_SIZE                              (BLE_GATT_MTU_SIZE_DEFAULT - 3)

#define BLE_GATT_SVC_TYPE_END                               0
#define BLE_GATT_SERVICE_TYPE_PRIMARY                       1
#define BLE_GATT_SERVICE_TYPE_SECONDARY                     2

#define BLE_GATT_CHR_PROPS_BROADCAST                        0x0001
#define BLE_GATT_CHR_PROPS_READ                             0x0002
#define BLE_GATT_CHR_PROPS_WRITE_NO_RSP                     0x0004
#define BLE_GATT_CHR_PROPS_WRITE                            0x0008
#define BLE_GATT_CHR_PROPS_NOTIFY                           0x0010
#define BLE_GATT_CHR_PROPS_INDICATE                         0x0020
#define BLE_GATT_CHR_PROPS_AUTH_SIGN_WRITE                  0x0040
#define BLE_GATT_CHR_PROPS_EXTENDED                         0x0080

// Characteristic permission
#define BLE_GATT_CHR_PERMISSION_READ                        0x0001
#define BLE_GATT_CHR_PERMISSION_WRITE                       0x0010

#define BLE_GATT_STATE_UNKNOWN                              0x0000
#define BLE_GATT_STATE_DISCONNECTED                         0x0001
#define BLE_GATT_STATE_CONNECTED                            0x0002

typedef int (* BleGattAccessCallback)(uint16_t conn_handle, uint16_t attr_handle,
                                      void *args);

typedef struct{
  BleUuid16                       *uuid;
  uint16_t                        *value_handle;
  uint16_t                        *cccd_handle;
  uint16_t                        props;
  uint16_t                        permission;
  uint8_t                         *init_value;
  uint8_t                         init_value_len;
} BleGattCharacteristic;

typedef struct {
  uint8_t                    type;
  BleUuid128                 *uuid;
  uint16_t                   *handle;
  uint8_t                    characteristic_count;
  BleGattCharacteristic      *characteristics;
} BleGattService;

typedef struct {
  void (*onConnectionStateChanged)(uint16_t conn_handle, uint16_t state);
  void (*onCharacteristicReadRequest)(uint16_t conn_handle, uint16_t handle, uint8_t *value, uint16_t length);
  void (*onCharacteristicWriteRequest)(uint16_t conn_handle, uint16_t handle, uint8_t *value, uint16_t length);
} BleGattServerCallback;

// BLE Scanner
typedef enum {
  SCAN_INTERVAL_LEVEL_0 = 50,            // 50ms
  SCAN_INTERVAL_LEVEL_1 = 100,           // 100ms
  SCAN_INTERVAL_LEVEL_2 = 200,           // 200ms
  SCAN_INTERVAL_LEVEL_3 = 300,           // 300ms
  SCAN_INTERVAL_LEVEL_4 = 400,           // 400ms
  SCAN_INTERVAL_LEVEL_5 = 500,           // 500ms
  SCAN_INTERVAL_LEVEL_6 = 650,           // 650ms
  SCAN_INTERVAL_LEVEL_7 = 750,           // 750ms
  SCAN_INTERVAL_LEVEL_8 = 820            // 820ms
} ScanIntervalLevel;

typedef struct{
  BleDevice    device;
  int8_t       rssi;                  			// Received Signal Strength Indication in dBm.
  uint8_t		   scan_response:1;
  uint8_t 	   type:2;
  uint8_t      len:5;
  uint8_t      data[ADVERTISE_MAX_DATA_SIZE];    // Advertising or scan response data.
} ScanRecord;

typedef struct {
  void (*onScanCompleted)(void);
  void (*onScanAbort)(void);
  void (*onScanResult)(ScanRecord *record);
} BleScanCallback;

// BLE Advertiser
typedef enum {
  ADV_INTERVAL_LEVEL_0 = 152,           // 152.5ms
  ADV_INTERVAL_LEVEL_1 = 318,           // 318.75ms
  ADV_INTERVAL_LEVEL_2 = 546,           // 546.25ms
  ADV_INTERVAL_LEVEL_3 = 852,           // 852.5ms
  ADV_INTERVAL_LEVEL_4 = 1022,          // 1022.5ms
  ADV_INTERVAL_LEVEL_5 = 2045,          // 2045.0ms
  ADV_INTERVAL_LEVEL_6 = 4082,          // 4082.5ms
  ADV_INTERVAL_LEVEL_7 = 5120,          // 5120.0ms
  ADV_INTERVAL_LEVEL_8 = 10040          // 10040.0ms
} AdvIntervalLevel;

typedef struct {
  void (*onSendout)(void);
} BleAdvertiseCallback;

typedef struct{
  int (*getMacAddress)(uint8_t *address);
  int (*setTxPower)(int8_t power);
  int (*setDeviceName)(const char *name, int len);
  int (*setAdvertisementData)(AdvData *advdata, AdvData *scanrsp_data);
  int (*startAdvertising)(AdvIntervalLevel level, const BleAdvertiseCallback *advCallback, const BleGattServerCallback *gattServerCallback);
  int (*stopAdvertising)(void);
  int (*startScan)(ScanIntervalLevel level, const BleScanCallback *callback);
  int (*stopScan)(void);
  int (*addService)(BleGattService *service);
  int (*notifyCharacteristic)(uint16_t conn_handle, uint16_t handle, uint8_t *value, uint16_t length);
} BleManager;

BleManager* CKBleManager(void);
/*---------------------------------------------------------------------------*/
// OSFile
#define OSFILE_DATA_MAX_LENGTH 			64
#define OSFILE_DATA_MAX_OPEN 			  4

typedef enum
{
  SeekSet = 0x00,
  SeekCur,
  SeekEnd
} SeekMode;

typedef struct {
  int (*open)(int16_t *fd, const uint32_t key, const char *mode);
  int (*write)(const int16_t fd, const void *data, const uint32_t size);
  int (*read)(const int16_t fd, void *data, const uint32_t size);
  int (*seek)(const int16_t fd, const uint32_t offset, const SeekMode mode);
  int (*close)(const int16_t fd);
  int (*size)(const uint32_t key);
  int (*remove)(const uint32_t key);
  int (*removeAll)(void);
  int (*space)(uint32_t *total, uint32_t *used);
} FileIO;

FileIO *OSFileIO(void);
/*---------------------------------------------------------------------------*/
// OSTimer
#define OSTIMER_MAX_NUMBER  3
typedef void (* OSTimerHandler)(uint8_t id);

typedef enum {
  TIMER0 = 0x00,
  TIMER1 = 0x01,
  TIMER2 = 0x02
} TimerId;

typedef struct{
  int (*start)(TimerId id, uint16_t milliseconds, OSTimerHandler handler);
  int (*stop)(TimerId id);
} Timer;

Timer* OSTimer(void);
/*---------------------------------------------------------------------------*/
// Logger
#define LOG_BLE      0x00000001
#define LOG_SERIAL   0x00000002
#define LOG_RTT      0x00000004

typedef struct{
  int (*printf)(uint32_t interface, const char *fmt, ...);
  int (*sprintf)(char *buf, const char *fmt, ...);
} Logger;

// Singleton instance of OSLog
Logger* OSLogger(void);
/*---------------------------------------------------------------------------*/
// Process
typedef struct {
  void (*onEnterBackground)(void);
  void (*onEnterForeground)(void);
  void (*onWillTerminate)(void);
} OSProcessCallback;

typedef struct{
  int (*waitForEvent)(void);
  uint32_t (*getUuid)(void);
  uint32_t (*getVersion)(void);
  uint32_t (*getClockTick)(void);
  void (*delay)(uint16_t millis);
  void (*delayUs)(uint16_t microseconds);
} Process;

// Singleton instance of OSLog
Process* OSProcess(void);
int OSProcessEventAttach(const OSProcessCallback *callback);
int OSProcessEventDetach(void);
/*---------------------------------------------------------------------------*/
// Localtime
typedef struct{
  uint32_t (*getSeconds)(void);
  uint32_t (*getMinutes)(void);
  uint32_t (*getHour24)(void);
  uint32_t (*getHour12)(void);
  uint32_t (*getDayOfWeek)(void);
  uint32_t (*getDayOfMonth)(void);
  uint32_t (*getDayOfYear)(void);
  uint32_t (*getMonth)(void);
  uint32_t (*getYear)(void);
} Localtime;

// Singleton instance of HwInfo
Localtime* OSLocaltime(void);
/*---------------------------------------------------------------------------*/
typedef enum {
  TYPE_ACCELEROMETER,
  TYPE_MOTION_RAW,
  TYPE_MOTION_FUSION,
  TYPE_HEARTRATE,
  TYPE_FOOT_PRESSURE
} SensorType;

typedef struct {
  SensorType type;
  uint8_t data_len;
  uint8_t data[24];
  uint32_t timestamp;
} SensorEvent;

typedef void (* SensorEventHandler)(SensorEvent *event);

typedef struct {
  int16_t  (*getRawX)(void);
  int16_t  (*getRawY)(void);
  int16_t  (*getRawZ)(void);
  float  (*getX)(void);
  float  (*getY)(void);
  float  (*getZ)(void);
  void   (*start)(void);
  void   (*stop)(void);
} Accelerometer;

enum {
  MotionRaw_Rate_10hz = 0x00000001,
  MotionRaw_Rate_20hz,
  MotionRaw_Rate_40hz,
  MotionRaw_Rate_50hz,
  MotionRaw_Rate_100hz
};

typedef struct {
  int (* start)(void);
  int (* stop)(void);
  int (* setUpdateRate)(uint32_t rate);
  int (* getAccel)(float *value, int32_t *data, uint32_t *timestamp);
  int (* getGyro)(float *value, int32_t *data, uint32_t *timestamp);
  int (* getCompass)(float *value, int32_t *data, uint32_t *timestamp);
} MotionRaw;

enum {
  MotionFusion_Rate_10hz = 0x00000001,
  MotionFusion_Rate_20hz,
  MotionFusion_Rate_40hz,
  MotionFusion_Rate_50hz,
  MotionFusion_Rate_100hz
};

enum {
  MotionFusion_Data_Accel = 0x01,
  MotionFusion_Data_Gyro = 0x02,
  MotionFusion_Data_Compass = 0x04,
  MotionFusion_Data_Quat = 0x08,
  MotionFusion_Data_Euler = 0x10,
  MotionFusion_Data_Heading = 0x20,
  MotionFusion_Data_Linear_Accel = 0x40,
  MotionFusion_Data_Gravity_Vector = 0x80
};

typedef struct {
  int (* start)(void);
  int (* stop)(void);
  int (* setUpdateRate)(uint32_t rate);
  int (* getAccel)(float *value, int32_t *data, uint32_t *timestamp);
  int (* getGyro)(float *value, int32_t *data, uint32_t *timestamp);
  int (* getCompass)(float *value, int32_t *data, uint32_t *timestamp);
  int (* getQuaternion)(float *value, int32_t *data, uint32_t *timestamp);
  int (* getEulerAngle)(float *value, int32_t *data, uint32_t *timestamp);
  int (* getLinearAccel)(float *value, uint32_t *timestamp);
  int (* getGravityVector)(float *value, uint32_t *timestamp);
  int (* getHeading)(float *value, int32_t *data, uint32_t *timestamp);
} MotionFusion;

typedef struct {
  int (*start)(void);
  int (*stop)(void);
  uint8_t (*getBPM)(void);
  bool (*isTouch)(void);
} HeartrateMonitor;

#define FOOTPRESSURE_TYPE_LEFT          0x00;
#define FOOTPRESSURE_TYPE_RIGHT         0x01;

typedef struct {
  void (*start)(void);
  void (*stop)(void);
  uint8_t (*getType)(void);
  int16_t (*getThumb)(void);
  int16_t (*getOuterBall)(void);
  int16_t (*getInnerBall)(void);
  int16_t (*getHeel)(void);
} FootPressure;

typedef struct {
  bool  (*isAccelerometerExist)(void);
  bool  (*isMotionRawExist)(void);
  bool  (*isMotionFusionExist)(void);
  bool  (*isHeartrateExist)(void);
  bool  (*isFootPressureExist)(void);
  Accelerometer* (*getAccelerometer)(void);
  MotionRaw* (*getMotionRaw)(void);
  MotionFusion* (*getMotionFusion)(void);
  HeartrateMonitor* (*getHeartrateMonitor)(void);
  FootPressure* (*getFootPressure)(void);
} SensorManager;

SensorManager* OSSensorManager(void);
int OSSensorEventAttach(SensorEventHandler handler);
int OSSensorEventDetach(void);
/*---------------------------------------------------------------------------*/
// Device
#define DEVICE_HWID_MAX_LEN									 8

typedef struct{
  int (* getHwid)(uint8_t *hwid, int max_len);
  char* (* getPlatformName)(void);
  char* (*getKernelVersion)(void);
  uint8_t (* getBatteryLevel)(void);
} Device;

// Singleton instance of Device
Device* OSDevice(void);
/*---------------------------------------------------------------------------*/
#if defined(UIKit)
// UIWINDOW
#define UIWINDOW_CONTROL_EVENT_CLICK            0x00000001
#define UIWINDOW_CONTROL_EVENT_DOUBLE_TAP       0x00000002
#define UIWINDOW_CONTROL_EVENT_PAUSE            0x00000004
#define UIWINDOW_CONTROL_EVENT_RESUME           0x00000008

typedef void (* UIWindowEventHandler)(uint32_t type);

typedef enum {
  FONT_KEY_SERIF_6 = 0x00000001,
  FONT_KEY_SERIF_7,
  FONT_KEY_SERIF_9,
  FONT_KEY_SERIF_12,
} GRAPHICS_FONT_KEYS;

typedef enum {
  BITMAP_COLOR_WHITE = 0x00000000,
  BITMAP_COLOR_BLOCK,
} BITMAP_COLOR_KEYS;

typedef struct {
  int (* clear)(void);
  int (* update)(void);
  int (* drawPixel)(int16_t x, int16_t y);
  int (* drawLine)(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
  int (* drawRect)(int16_t x, int16_t y, int16_t width, int16_t height);
  int (* fillRect)(int16_t x, int16_t y, int16_t width, int16_t height);
  int (* drawCircle)(int16_t x, int16_t y, int16_t radius);
  int (* fillCircle)(int16_t x, int16_t y, int16_t radius);
  int (* drawHorizontalLine)(int16_t x, int16_t y, int16_t length);
  int (* drawVerticalLine)(int16_t x, int16_t y, int16_t length);
  int (* drawProgressBar)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress);
  int (* drawBitmap)(uint8_t *bitmap, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
  int (* drawText)(const char *text, int len, uint32_t x, uint32_t y);
  int (* drawChar)(char text, uint32_t x, uint32_t y);
  int (* setCursor)(int16_t x, int16_t y);
  int (* setFont)(uint32_t font_key);
  int (* setRotation)(uint8_t rotation);
} Canvas;

typedef struct {
  int (*shortPulse)(void);
  int (*longPulse)(void);
  int (*doublePulse)(void);
} Vibrator;

typedef struct {
  Canvas* (*getCanvas)(void);
  int (*displayOff)(void);
  int (*displayOn)(void);
  int (*getDisplayWidth)(void);
  int (*getDisplayHeight)(void);
  int (*setBackgroundMode)(bool enable);
  Vibrator* (*getVibrator)(void);
} Window;

// Singleton instance of Window
Window* UIWindow(void);
int UIWindowEventAttach(UIWindowEventHandler handler);
int UIWindowEventDetach(void);

#endif

/*---------------------------------------------------------------------------*/
#if defined(HKKit)
// Pedometer
typedef struct {
  float* (*getTodayCalories)(void);
  float* (*getTodayDistance)(void);
  int* (*getTodaySteps)(void);
} Pedometer;

Pedometer* HKPedometer(void);
#endif

/*---------------------------------------------------------------------------*/
// Hardware API
#if defined(HWKit)
/*---------------------------------------------------------------------------*/
// PIN
enum {
  PIN_DEFAULT = 0x00,
  PIN_OUTPUT = 0x01,
  PIN_INPUT = 0x02
};

enum {
  PIN_OUTPUT_LOW = 0x00,
  PIN_OUTPUT_HIGH = 0x01,
  PIN_OUTPUT_TOGGLE
};

enum {
  PIN_INPUT_FLOATING = 0x00,
  PIN_INPUT_PULLUP = 0x01,
  PIN_INPUT_PULLDOWN = 0x02
};

enum {
  PIN_EDGE_NONE = 0x00,
  PIN_EDGE_RISING = 0x01,
  PIN_EDGE_FALLING = 0x02
};

typedef void (* PinEventHandler)(uint32_t pin, uint32_t edge);

typedef struct {
  int (* setup)(uint32_t pin, uint8_t value);
  int (* output)(uint32_t pin, uint8_t value);
  int (* input)(uint32_t pin, uint8_t value);
  int (* read)(uint32_t pin);
  int (* attachInterrupt)(uint32_t pin, uint32_t edge, PinEventHandler handler);
  int (* detachInterrupt)(void);
} Pin;

Pin* HWPin(void);

/*---------------------------------------------------------------------------*/
// Uart
enum {
	BAUDRATE_1200 = 1200,
  BAUDRATE_2400 = 2400,
  BAUDRATE_4800 = 4800,
  BAUDRATE_9600 = 9600,
	BAUDRATE_19200 = 19200,
  BAUDRATE_38400 = 28400,
  BAUDRATE_57600 = 57600,
  BAUDRATE_115200 = 115200,
};

typedef void (* UartRxHandler)(uint8_t data);

typedef struct {
	int (* open)(uint32_t pin_tx, uint32_t pin_rx, uint32_t baudrate, UartRxHandler handler);
  int (* close)(void);
  int (* send)(uint8_t *data, uint32_t length);
} Uart;

Uart* HWUart(uint8_t number);
/*---------------------------------------------------------------------------*/
// I2c
// I2c* HWI2c(uint8_t number);
/*---------------------------------------------------------------------------*/
// Spi
// Spi* HWSpi(uint8_t number);
#endif  /*  HWKit */

#ifdef __cplusplus
}
#endif
#endif /* __ALFABASE_H_ */
