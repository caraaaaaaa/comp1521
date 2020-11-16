#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    if (argc < 1){
        printf("Usage: ./diary <note>\n");
        exit(1);
    }

    char *buffer = getenv("HOME");
    char path[100];
    snprintf(path, 100, "%s/.diary", buffer);


    FILE *f;
    f = fopen(path, "a");

    for (int i = 1; i < argc - 1; i++){
        fputs(argv[i], f);
        fputs(" ", f);
    }

    fputs(argv[argc - 1], f);
    fputs("\n", f);

    fclose(f);

    return 0;
}