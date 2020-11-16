#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    FILE *fp = fopen(argv[1], "r");
    int count = 0;
    int byte;
    while ((byte = fgetc(fp)) != EOF) {
        if (byte <= 127 && byte >= 0) {
            count++;
        }
    }
    printf("%s contains %d ASCII bytes\n", argv[1], count);
    return 0;

}    