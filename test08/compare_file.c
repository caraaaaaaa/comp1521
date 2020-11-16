// 1521 Test08 compare_file.c
// Zixuan Guo z5173593

# include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc != 3) printf("Please enter 2 arguments only.\n");

	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "r");

	int count = 0;
	int re1 = fgetc(fp1);
	int re2 = fgetc(fp2);

	while (re1 != EOF && re2 != EOF) {
		if (re1 != re2) {
			printf("Files differ at byte %d\n", count);
			return 0;
		}

		count++;
		re1 = fgetc(fp1);
		re2 = fgetc(fp2);
	}

	if (re1 == EOF && re2 != EOF) printf("EOF on %s\n", argv[1]);
	else if (re2 == EOF && re1 != EOF) printf("EOF on %s\n", argv[2]);
	else printf("Files are identical\n");

	return 0;
}