#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat s;

    if (stat(argv[1], &s) == 0 && S_ISDIR(s.st_mode)){
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}