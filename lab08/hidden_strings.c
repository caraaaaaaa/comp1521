#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int detect_nextchar(FILE *fp, int char_num);
int main(int argc, char *argv[]) {
	FILE *fp = fopen(argv[1], "r");			
	if (fp == NULL) {
		perror("Can not open target file\n");
		return 1;
	}

	int BUFF[1000];									
	int counter = 0;								
	int re;											
	while ((re = fgetc(fp)) != EOF) {
		if(isprint(re) != 0){
			BUFF[counter] = re;
			counter ++;
			if(counter >= 4){						
													
				if(isprint(fgetc(fp)) != 0) {
					fseek(fp,-1,SEEK_CUR);			
					continue;
				}
				else{
					fseek(fp,-1,SEEK_CUR);			
					for(int n=0;n<counter;n++){	
						printf("%c",BUFF[n] );
					}
					counter = 0;
					printf("\n");
				}
			}
		}
		else{
			counter = 0;
		}
	}
	return 0;
}