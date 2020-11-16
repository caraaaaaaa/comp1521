// 1521 Test08  non_ascii.c
// Zixuan Guo   z5173593

# include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *fp = fopen(argv[1], "r+");

	if (fp == NULL) printf("Can not print the target file\n");

	int count = 0;
	int re = fgetc(fp);

	while (re != EOF) {
		if ((re >= 128) && (re <= 255)) {
			printf("%s: byte %d is non-ASCII\n", argv[1], count);
			return 0;
		}
		count++;
		re = fgetc(fp);
	}

	printf("%s is all ASCII\n", argv[1]);

	return 0;
}