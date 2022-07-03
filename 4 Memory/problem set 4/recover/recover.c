#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // only one argument
    if (argc != 2)
    {
        printf("Usage: ./recover xxx.jpeg\n");
        return 1;
    }

    // open file (memory card)
    FILE *file = fopen(argv[1], "r");
    // if file is null
    if (file == NULL)
    {
        return 1;
    }

    // read data
    BYTE *buffer = (BYTE *)malloc(BLOCK_SIZE * sizeof(BYTE));
    char *file_name = (char *)malloc(sizeof(char) * 7);
    int file_name_cnt = 0;

    bool already_first = false;


    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE * sizeof(BYTE)) // fread returns the number of bytes that it has read
    {
        // look for the begin of jpeg
        // first three bytes of JPEGs are 0xff 0xd8 0xff
        // the fourth byte’s first four bits are 1110: The fourth byte is either 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef.

        if (*buffer == 0xff && *(buffer + 1) == 0xd8 && *(buffer + 2) == 0xff && ((*(buffer + 3) & 0xf0) == 0xe0))
        {
            already_first = true;
            // printf("%d\n", fime_name_cnt);
            // make a new jpeg file name
            sprintf(file_name, "%03i.jpg", file_name_cnt);
            // make a new jpeg file
            FILE *img = fopen(file_name, "w");
            // write 512 bytes until a new jpeg is found
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            fclose(img);
            file_name_cnt++;
        }
        else if (already_first == true)
        {
            // open exit file (appending mode)
            FILE *img = fopen(file_name, "a");
            // continue write
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            fclose(img);
        }
    }

    free(buffer);
    free(file_name);
    fclose(file);
}