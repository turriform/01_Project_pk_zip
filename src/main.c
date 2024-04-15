#include "framework.h"
#include "file_tools/file_tools.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("No file provided \n");
        return 0;
    }

    for (size_t i = 1; i != argc; i++)
    {
        printf("\nChecking for file %s \n", argv[i]);
        init(argv[i]);
        
    }
}