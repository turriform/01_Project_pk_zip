#if !defined(_L_FILETOOLS_H)
#define _L_FILETOOLS_H

// https://en.wikipedia.org/wiki/JPEG_File_Interchange_Format

typedef enum FileMainType
{
    NONE,
    JPEG,
    PNG,

} file_main_t;

typedef struct FileData
{
    file_main_t main_file_type;
    bool is_zip;
    size_t file_count;

} file_data_t;


typedef struct JPEG
{
    // uint16_t marker; //FF D8
    uint16_t app_0; // FF E0
    uint16_t length;
    uint8_t identifier[5];
    uint16_t version;
    uint8_t density_units;
    uint16_t x_density;
    uint16_t y_density;
    uint8_t x_thumbnail;
    uint8_t y_thumbnail;
    // uint8_t *data;

}
__attribute__((packed))
jpeg_t;



void bits_convert(uint8_t buf[], size_t value, size_t size);

void file_data_print(file_data_t * filedata);

bool file_find_signature(FILE *fp, size_t value, size_t size);

void file_main_type_extract(FILE *fp, file_main_t type);

void file_find_all_lfh(FILE *fp);

void file_contains_zip(file_data_t *filedata, size_t filesize, size_t current_pos);

void file_look_for_main_file(FILE *fp, file_data_t *filedata);

void init(char * filepath);


#endif // _L_FILETOOLS_H
