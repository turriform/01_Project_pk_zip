#include "framework.h"
#include "file_tools/file_tools.h"
#include "pk_zip/pk_zip.h"
void bits_convert(uint8_t buff[], size_t value, size_t size)
{
    const uint8_t bits = 8;
    size_t initial = (size - 1) * bits;
    for (size_t i = 0; i != size; i++)
    {
        buff[i] = (value >> initial) & 0xFF;
        initial -= bits;
    }
}

void file_data_print(file_data_t *fd)
{
    file_main_t dt = fd->main_file_type;

    printf("Main file type: %s \n", dt == JPEG ? "JPEG" : dt == PNG ? "PNG"
                                                                    : "UNDEFINED");

    bool is_zip = fd->is_zip;
    printf("%s\n", is_zip ? "Contains zip" : "Doesnt't contain zip");
}

bool file_find_signature(FILE *fp, size_t value, size_t size)
{
    //signature search based on a magic number (signature) and its size
    uint8_t buff[size];
    uint8_t sig[size];
    //converting magic number to bytes array
    bits_convert(sig, value, size);
    uint8_t c;
    while (fread(&buff, size, 1, fp))
    {
        // fseek(fp, -(size - 1), SEEK_CUR);
        if (memcmp(&buff, sig, size) == 0)
        {
            return true;
        }
    }

    return false;
}

bool _file_main_type_contains(FILE *fp, file_data_t *filedata, size_t signature, size_t sig_sz)
{
    // moving fp to the top since we're looking for the main single file
    fseek(fp, 0, SEEK_SET);
    bool found = file_find_signature(fp, signature, sig_sz);

    return found ? true : false;
};

void _file_main_type_ends(FILE *fp, size_t signature, size_t sig_sz)
{
    file_find_signature(fp, signature, sig_sz);
}

void file_main_type_extract(FILE *fp, file_main_t type)
{
    // defining a proper filestring name for extraction
    char *file_string;
    switch (type)
    {
    case PNG:
        file_string = "./output/file_extract.png";
        break;

    default:
        file_string = "./output/file_extract.jpeg";
    }

    size_t start = 0, end = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    uint8_t buff[end];
    fread(buff, end, 1, fp);
    FILE *fp_out = fopen(file_string, "wb");
    fwrite(buff, end, 1, fp_out);
    fclose(fp_out);
}

bool _file_conains_lfh(FILE *fp)
{
    bool found = file_find_signature(fp, PK_ZIP_SIG, PK_ZIP_SIG_SZ);

    return found ? true : false;
};

void file_find_all_lfh(FILE *fp)
{
    uint16_t c;
    int total = 0;

    bool found = _file_conains_lfh(fp);

    while (found)
    {

        total++;
        pk_zip_lfh_t lfh;
        fread(&lfh, sizeof(lfh), 1, fp);
        size_t filename_len = lfh.filename_length;
        while (filename_len--)
        {
            printf("%lc", fgetc(fp));
        }
        printf("\n");

        found = _file_conains_lfh(fp);
    }

    printf("Total files %ld \n", total);
}

void file_contains_zip(file_data_t *filedata, size_t filesize, size_t current_pos)
{
    filedata->is_zip = (current_pos < filesize) ? true : false;
}

void file_look_for_main_file(FILE *fp, file_data_t *filedata)
{
    //determine which file is the main file
    //first checking if file exists              file_main_type_contains()
    //then looking for the end                   _file_main_type_ends()  
    //checking only for 2 file types (PNG, JPEG)

    bool main_jpeg = _file_main_type_contains(fp, filedata, JPEG_START, JPEG_START_SZ);
    if (main_jpeg)
    {
        filedata->main_file_type = JPEG;

        _file_main_type_ends(fp, JPEG_END, JPEG_END_SZ);
        return;
    }
    fseek(fp, 0, SEEK_SET);
    bool main_png = _file_main_type_contains(fp, filedata, PNG_START, PNG_START_SZ);

    if (main_png)
    {
        filedata->main_file_type = PNG;

        _file_main_type_ends(fp, PNG_END, PNG_END_SZ);
        return;
    }
     filedata->main_file_type = NONE;
}

void init(char * filepath)
{
    /*
        1) opening file, checking if its intact
        2) looking for the main file (jpeg or png)
        3) comparing current position with the file size,
            if values match, then there is no archive present -> Printing, Cleaning and Exiting (1)
            if file size is larger, then program assumes the archive is in the file
            4) (?) extracting main file
            5) looking for all localfileheaders (lfh) in the file
            6) after lfh type is read printing the filename using the lfh filesize field
            7) Printing, Cleaning and Exiting (2)

    */

    FILE *fp = fopen(filepath, "rb");
    if(fp == NULL){
        printf("Couldn't open file %d \n", errno);
        return;
    }

    struct stat file_system_stat;
    fstat(fileno(fp), &file_system_stat);

    file_data_t filedata = {};
    file_look_for_main_file(fp, &filedata);
    file_contains_zip(&filedata, (size_t)file_system_stat.st_size, (size_t)ftell(fp));

    if (filedata.is_zip)
    {
        file_main_type_extract(fp, filedata.main_file_type);
        file_find_all_lfh(fp);
    }

    file_data_print(&filedata);
    fclose(fp);
}
