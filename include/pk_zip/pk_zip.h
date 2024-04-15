#if !defined(_LOCAL_PK_ZIP_H)
#define _LOCAL_PK_ZIP_H

#include "framework.h"

// https://pkwaredownloads.blob.core.windows.net/pkware-general/Documentation/APPNOTE-2.0.txt
// https://users.cs.jmu.edu/buchhofp/forensics/formats/pkzip.html
typedef struct LocalFileHeader
{
    // uint32_t signature;                // 4 bytes  (0x04034b50)
    uint16_t version_to_extract;       // 2 bytes
    uint16_t general_purpose_bit_flag; // 2 bytes
    uint16_t compression_method;       // 2 bytes
    uint16_t last_mod_file_time;       // 2 bytes
    uint16_t last_mod_file_date;       // 2 bytes
    uint32_t crc_32;                   // 4 bytes
    uint32_t compressed_size;          // 4 bytes
    uint32_t uncompressed_size;        // 4 bytes
    uint16_t filename_length;          // 2 bytes
    uint16_t extra_field_length;       // 2 bytes
    // filename follows right after

} __attribute__((packed)) pk_zip_lfh_t;







#endif // _LOCAL_PK_ZIP_H
