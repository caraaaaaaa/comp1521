#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char *name = getenv(argv[1]);
    if (name == NULL) {
        printf("0\n");
    } else {
        if (name[0] == '\0') {
            printf("0\n");
        } else {
            printf("1\n");
        }
    }
    return 0;
}
    
