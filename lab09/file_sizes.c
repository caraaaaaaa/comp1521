// 1521 Lab09 file_sizes.c
// Zixuan Guo (Z5173593)

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

long stat_file(char *pathname);

int main(int argc, char *argv[]) {
	long long int total = 0;
	for (int counter = 1; counter < argc; counter++) {
		total += stat_file(argv[counter]);
	}

	printf("Total: %lld bytes\n", total);
	return 0;
}

long stat_file(char *pathname) {
	struct stat s;
	

	if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
printf("%s: %ld bytes\n", pathname, s.st_size);
    return s.st_size;
}