#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



int main(int argc, char *argv[]) {

	FILE *fp = fopen(argv[1],"w+");

	if (fp == NULL) {				
		perror("Can not open target file\n");
		return 1;
	}

	for(int i = 2;argv[i] != NULL;i++) {
		int ans = atoi(argv[i]);			
		fputc(ans, fp);			
	}

	fclose(fp);
	return 0;
}