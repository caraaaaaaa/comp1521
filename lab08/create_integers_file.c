// create_integers_file
// Zixuan Guo
// z5173593

#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[] ) {
	if (argc != 4) {
		exit(1);
	}

	FILE *fp = fopen(argv[1],"a");		

	if(fp == NULL) {				
		perror("Can not open target file");
		return 1;
	}

	int low_bound = atoi(argv[2]);
	int high_bound = atoi(argv[3]);

	for(int i = low_bound;i <= high_bound;i++) {	
		fprintf(fp, "%d\n",i );
	}

	fclose(fp);

	return 0;

}