#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int re = 1;
    if (argc != 3) {
        exit(1);
    }
    //FILE *fp1 = open(argv[1], "r");
    //FILE *fp2 = open(argv[2], "r");

    int re1 = fgetc(fp1);
    int re2 = fgetc(fp2);

    while (re1 != EOF && re2 != EOF) {
        if (re1 != re2) {
            re = 0;
        }

        re1 = fgetc(fp1);
        re2 = fgetc(fp2);
    }

    if (re == 1 && re1 == EOF && re2 == EOF) {
        re = 1;
    } else {
        re = 0;
    }
    printf("%d\n", re);


    return 0;
}