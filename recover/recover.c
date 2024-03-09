#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
typedef uint8_t byte;

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s filename \n", argv[0]);
        return 1;
    }
    FILE *rcvr=fopen(argv[1], "r");
    if (rcvr==NULL)
    {
        printf("Unable to open file.\n");
        return 1;
    }
    byte c[512];
    int filecount=0;
    FILE *jpg;
    while (fread(c, sizeof(byte), 512, rcvr))
    {
        char filename[8];
        if (c[0]==0xff && c[1]==0xd8 && c[2]==0xff && (c[3] & 0xf0) == 0xe0)
        {
            if (jpg != NULL) {fclose(jpg);}
            filecount+=1;
            sprintf(filename, "%03d.jpg", filecount);
            jpg=fopen(filename, "w");
            if (jpg==NULL)
            {
                printf("Unable to open file.\n");
                return 1;
            }
            size_t written=fwrite(c, sizeof(byte), 512, jpg);
            if (written<512)
            {
                printf("Unable to open file.\n");
                return 1;
            }
        }
        else
        {
            if (jpg != NULL)
            {
                fwrite(c, sizeof(byte), 512, jpg);
            }
        }
    }
    fclose(jpg);
    fclose(rcvr);
}
