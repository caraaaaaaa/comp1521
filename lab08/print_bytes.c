#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int main(int argc, char *argv[]) {
	FILE *fp = fopen(argv[1], "r");	

	if (fp == NULL) {
		perror("Can not open target file\n");
		return 1;
	}

	unsigned int bytes = 0;
	int re;

	while ((re = fgetc(fp)) != EOF) {
		printf("byte %4d: %3d 0x%02x",bytes,re,re);	
		bytes ++;								
		if(isprint(re) != 0) {				
			printf(" '%c'\n",re );
		}
		else {
			printf("\n");
		}
	}
	
	fclose(fp);

	return 0;

}