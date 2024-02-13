#include<stdio.h>
#include "apue.h"
#include<unistd.h>
#include<fcntl.h>

int main(){
	int value;
	char Fname[100];
	printf("Enter the name of the file: ");
	scanf("%s",&Fname);
	int file = open(Fname, O_CREAT | O_SYNC);
	if(file == -1){
		err_sys("Error while opening the file");
		exit(EXIT_FAILURE);
	}
	value = fcntl(file, F_GETFL);
	if(value == -1){
		err_sys("Error while querying");
		close(file);
		exit(EXIT_FAILURE);
	}
	switch(val & O_ACCMODE){
		case O_RDONLY:
			printf("Read Only\n");
			break;
		
		case O_WRONLY:
			printf("Write Only\n");
			break;
		
		case O_RDWR:
			printf("Read Write\n");
			break;
			
		default:
			err_dump("Access mode in not known");
			break;
	}
	
	if (value & O_APPEND)
		printf(", append");
	if (value & O_NONBLOCK)
		printf(", nonblocking");
	if (value & O_SYNC)
		printf(", synchronous writes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (value & O_FSYNC)
		printf(", synchronous writes");
#endif

	putchar('\n');
	close(file);
	return 0;
}

