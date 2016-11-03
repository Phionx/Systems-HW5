#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>


long info(char* fp){
	struct stat *ans = (struct stat *)malloc(sizeof(struct stat));
	if(stat(fp, ans) == -1) printf("Error #%d: %s", errno, strerror(errno));
	long s = (long)ans->st_size;
	long fullSize = (long)ans->st_size;
	char *a;

	if (s < 1024){
		strcpy(a, "B");
	} else if ( s > 1024 && s <1024*1024 ){
		strcpy(a, "KB");
		s = s%1024;
	} else if (  s > 1024*1024 && s < 1024*1024*1024){
		strcpy(a, "MB");
		s = s%1024*1024;
	} else {
		strcpy(a, "GB");
		s = s%1024*1024*1024;
	}	
	/**/
	int mode =  ans->st_mode & 0777;
	//printf("File Name: %s\nFile Size: %ld%s\nMode: %d\nTime of last access: %s",fp, s, a ,mode,  ctime(&(ans->st_atime)));

	char perm[10];
	int i = 8;
	while (mode) {
    perm[i] = (mode % 2) ? 'x' : '-'; mode /= 2; i--;
    perm[i] = (mode % 2) ? 'w' : '-'; mode /= 2; i--;
    perm[i] = (mode % 2) ? 'r' : '-'; mode /= 2; i--;
  }
	perm[9] = 0;


	printf("%s  %ld%s  %s", perm, s, a, ctime(&(ans->st_atime)));
	return fullSize;

}

/*
int main(){
	printf("Directory Info: \n");
	long int dirSize = 0;
	DIR *stream = opendir(".");
	struct dirent* file = readdir(stream);
	while(file){
		if(file->d_type == DT_DIR) {
			printf("d");
		} else {
			printf("-");
			long add = info((*file).d_name);
			dirSize += add;
		}
		printf("\n");
		file = readdir(stream);
	}
	closedir(stream);
	printf("FULL SIZE OF ALL REGULAR FILES: %li\n", dirSize);
	return 0;
}
*/

int main() {
    printf("DIRECTORY INFO: \n");
	long int dirSize = 0;
	DIR* stream = opendir(".");
    struct dirent* file = readdir(stream);
    while (file) {
        if (file->d_type == DT_DIR) {
            printf("d");
			printf("- %s", (*file).d_name);
        } else {
            printf("-");
			printf("- %s", (*file).d_name);
			//long size = info((*file).d_name);
            struct stat temp;
			stat((*file).d_name, &temp);
			printf("\t %liB", (long)temp.st_size);
			dirSize += temp.st_size;
        }
        printf("\n");
        file = readdir(stream);
    }
    closedir(stream);
    printf("TOTAL SIZE OF ALL REGULAR FILES: %li bytes\n", dirSize);
    return 0;
}

			



