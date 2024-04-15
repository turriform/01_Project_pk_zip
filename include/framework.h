#if !defined(_LOCAL_FRAMEWORK_H)
#define _LOCAL_FRAMEWORK_H
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FILE_FOLDER_PATH "./assets/"

#define PRINT_BYTES(x) (uint8_t *)&(x), sizeof(x)


#define PK_ZIP_SIG 0x504b0304
#define PK_ZIP_SIG_SZ 4

#define PK_ZIP_LFH_SIG 0x504b0102 
#define PK_ZIP_LFH_SIG_SZ 4

#define PK_ZIP_CDIR_SIG 0x02014b50 
#define PK_ZIP_CDIR_SIG_SZ 4

#define PK_ZIP_EOCD_SIG 0x06054b50
#define PK_ZIP_EOCD_SIG_SZ 4


#define JPEG_START 0xFFD8FF
#define JPEG_START_SZ 3

#define JPEG_END 0xFFD9
#define JPEG_END_SZ 2

#define PNG_START 0x89504e470d0a1a0a
#define PNG_START_SZ 8

#define PNG_END 0x49454E44
#define PNG_END_SZ 4

#endif