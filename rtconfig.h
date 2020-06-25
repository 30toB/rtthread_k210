#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Project Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_USING_SMP
#define RT_CPUS_NR 2
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 4096
#define RT_DEBUG
#define RT_DEBUG_COLOR
#define RT_DEBUG_INIT_CONFIG
#define RT_DEBUG_INIT 1

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
#define RT_USING_SIGNALS

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SLAB
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uarths"
#define RT_VER_NUM 0x40003
#define ARCH_CPU_64BIT
#define ARCH_RISCV
#define ARCH_RISCV64

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 8192
#define RT_MAIN_THREAD_PRIORITY 10

/* C++ features */


/* Command shell */

#define RT_USING_FINSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 16384
#define FINSH_CMD_SIZE 80
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_MSH_ONLY
#define FINSH_ARG_MAX 10

/* Device virtual file system */

#define RT_USING_DFS
#define DFS_USING_WORKDIR
#define DFS_FILESYSTEMS_MAX 16
#define DFS_FILESYSTEM_TYPES_MAX 16
#define DFS_FD_MAX 64
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 4096
#define RT_DFS_ELM_REENTRANT
#define RT_USING_DFS_DEVFS

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_PIN
#define RT_USING_SPI
#define RT_USING_SPI_MSD
#define RT_USING_SFUD
#define RT_SFUD_USING_SFDP
#define RT_SFUD_USING_FLASH_INFO_TABLE
#define RT_SFUD_SPI_MAX_HZ 50000000
#define RT_DEBUG_SFUD

/* Using USB */


/* POSIX layer and C standard library */

#define RT_USING_LIBC
#define RT_USING_POSIX

/* Network */

/* Socket abstraction layer */


/* Network interface device */


/* light weight TCP/IP stack */


/* AT commands */


/* VBUS(Virtual Software BUS) */


/* Utilities */


/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */


/* IoT Cloud */


/* security packages */


/* language packages */


/* multimedia packages */


/* tools packages */


/* system packages */


/* peripheral libraries and drivers */

#define PKG_USING_KENDRYTE_SDK
#define PKG_USING_KENDRYTE_SDK_V055
#define PKG_KENDRYTE_SDK_VERNUM 0x0055
#define BSP_USING_SPI1

/* miscellaneous packages */


/* samples: kernel and components samples */

#define BOARD_K210_EVB
#define BSP_USING_UART_HS
#define BSP_USING_UART1
#define BSP_USING_UART2
#define BSP_USING_UART3
#define BSP_SPI1_CLK_PIN 27
#define BSP_SPI1_D0_PIN 28
#define BSP_SPI1_D1_PIN 26
#define BSP_SPI1_USING_SS0
#define BSP_SPI1_SS0_PIN 29
#define BSP_LCD_CS_PIN 36
#define BSP_LCD_WR_PIN 39
#define BSP_LCD_DC_PIN 38
#define BSP_LCD_X_MAX 240
#define BSP_LCD_Y_MAX 320
#define BSP_USING_LCD_ILI9341
#define BSP_LCD_RST_PIN 37
#define BSP_USING_LED
#define BSP_LED1_PIN 12
#define BSP_LED2_PIN 13
#define BSP_LED3_PIN 14
#define BSP_USING_CAMERA
#define BSP_CAMERA_SCCB_SDA_PIN 40
#define BSP_CAMERA_SCCB_SCLK_PIN 41
#define BSP_CAMERA_CMOS_RST_PIN 42
#define BSP_CAMERA_CMOS_VSYNC_PIN 43
#define BSP_CAMERA_CMOS_PWDN_PIN 44
#define BSP_CAMERA_CMOS_XCLK_PIN 46
#define BSP_CAMERA_CMOS_PCLK_PIN 47
#define BSP_CAMERA_CMOS_HREF_PIN 45
#define __STACKSIZE__ 4096

#endif
