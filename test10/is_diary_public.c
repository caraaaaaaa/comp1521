#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    char *var = getenv("HOME");
    char path[200];
    snprintf(path, 200, "%s/.diary", var);

    struct stat s;
    if (stat(path, &s) == 0 && (s.st_mode & S_IRUSR) && (s.st_mode & S_IRGRP) && (s.st_mode & S_IROTH)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}