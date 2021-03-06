# Platform makefile
PROJECT_MAIN = main
all: PROJECT_MAIN

TARGET := blelora51

PROJECT = ../..

include $(PROJECT)/Makefile.vars

$(info $(PROJECT)/platform/$(TARGET))

# Core usage configuration
USE_FREERTOS = 1
USE_NEST_STACK = 1
USE_CONTIKI = 1
USE_FRAMEWORK=1
USE_SPIFFS=1
USE_MPU=0
USE_ELFLOADER = 1
CONF_ELF_LOADER_TEXT_SIZE := 0x600

# Use CPU-peripherals
USE_UART0 = 1
USE_GPIOTE = 1
USE_SPI0 = 0
USE_SPI1 = 1
USE_SPI2 = 0
USE_TWIHW0 = 0
USE_TWIHW1 = 0
USE_TWISW0 = 1
USE_TWISW1 = 0
USE_ADC = 1
USE_CRYPTO_AES = 0

# Use Device-peripherals
USE_SPI_FLASH=1
USE_LOGGER=1
USE_DRIVERS_INV_MPU_RAW = 1
USE_DRIVERS_INV_MPU_DMP = 0

### Nordic nRF Softdevice
USE_ARCH_SOFTDEVICE = 1
NRF_SD_BLE_API_VERSION=2
CHIP_VERSION := xxac
STACK_SIZE := 1536
HEAP_SIZE := 0

PROJECT_TARGET_DIRS = .
PROJECT_TARGET_SOURCEFILES = bsp_init.c bsp_led.c bsp_button.c bsp_mpuraw.c bsp_e32ttl.c

BOARD_FLAGS := -DMPU9250 -DEMPL_TARGET_NRF5X
BOARD_LIBS :=
ifeq ($(PROD), 1)
	BOARD_FLAGS += -DDEBUG_DISABLE
else
	BOARD_FLAGS += -DDEBUG_ENABLE
endif

$(info $(PROJECT_TARGET_SOURCEFILES))

PROJECT_SOURCEFILES += $(PROJECT_TARGET_SOURCEFILES)

CLEAN += *.$(TARGET)
BOARD := BOARD_BLELORA51

### Define the Arch directory
PROJECT_ARCH=$(PROJECT)/arch/cortex-m0/nrf51822
PROJECT_BOARD=$(PROJECT)/platform/$(TARGET)

include $(PROJECT_ARCH)/Makefile.nrf51
include $(PROJECT)/Makefile.include
