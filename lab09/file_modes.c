// Lab09 file_modes
// Zixuan Guo (z5173593)

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define TRUE 1


void print_permission(mode_t mode, char *name);

int main(int argc, char *argv[]) {
	struct stat StateBuf;

	int i = 1;
	while (TRUE) {
		if (argv[i] == NULL) break;
		if (stat(argv[i],&StateBuf)== -1) break;

		stat(argv[i],&StateBuf);
		mode_t mode = StateBuf.st_mode;
		print_permission(mode, argv[i]);

		i++;
	}
	return 0;	


}
void print_permission(mode_t mode, char *name) {
	if((mode & S_IFREG) == S_IFREG){
		printf("-");
	}
	else if((mode & S_IFDIR) == S_IFDIR){
		printf("d");
	}
	
	if((mode & S_IRUSR) == S_IRUSR){
		printf("r");
	}
	else{
		printf("-");
	}
	if((mode & S_IWUSR) == S_IWUSR){
		printf("w");
	}
	else{
		printf("-");
	}

	if((mode & S_IXUSR) == S_IXUSR){
		printf("x");
	}
	else{
		printf("-");
	}

	if((mode & S_IRGRP) == S_IRGRP){
		printf("r");
	}
	else{
		printf("-");
	}

	if((mode & S_IWGRP) == S_IWGRP){
		printf("w");
	}
	else{
		printf("-");
	}

	if((mode & S_IXGRP) == S_IXGRP){
		printf("x");
	}
	else{
		printf("-");
	}	

	if((mode & S_IROTH) == S_IROTH){
		printf("r");
	}
	else{
		printf("-");
	}

	if((mode & S_IWOTH) == S_IWOTH){
		printf("w");
	}
	else{
		printf("-");
	}

	if((mode & S_IXOTH) == S_IXOTH){
		printf("x ");
	}
	else{
		printf("- ");
	}

	printf("%s\n", name);
}