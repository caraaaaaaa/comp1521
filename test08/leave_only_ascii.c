#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    FILE *tmp = fopen("tmp.txt", "w");

    int byte;
    while ((byte = fgetc(fp)) != EOF) {
        if (byte < 128 || byte > 255) fputc(byte, tmp);
    }

    fclose(fp);
    fclose(tmp);


    FILE *fp1 = fopen(argv[1], "w");
    FILE *tmp1 = fopen("tmp.txt", "r");
    while ((byte = fgetc(tmp1)) != EOF) {
        fputc(byte, fp1);
    }

    fclose(fp1);
    fclose(tmp1);
    
    return 0;
}           
