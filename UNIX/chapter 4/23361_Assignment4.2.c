/*
To run this code:
	gcc 23361_Assignment4.2.c 
	./a.out file1 file2 file3 . . . (should include minimum of 1 file) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void print_stat_info(const char *filename);
void print_time(const char *label, time_t seconds, long nanoseconds);

int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Usage: %s <filename1> <filename2> ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; ++i) {
        print_stat_info(argv[i]);
    }

    return 0;
}

void print_stat_info(const char *filename) {
    struct stat file_info;

    if (stat(filename, &file_info) == -1) {
        perror("Error getting file information");
        return;
    }

    printf("\nFile: %s\n", filename);
    printf("File Type & Mode: %o\n", file_info.st_mode);
    printf("Inode Number: %lu\n", (unsigned long)file_info.st_ino);
    printf("Device Number (File System): %lu\n", (unsigned long)file_info.st_dev);
    printf("Number of Links: %lu\n", (unsigned long)file_info.st_nlink);
    printf("User ID of Owner: %u\n", file_info.st_uid);
    printf("Group ID of Owner: %u\n", file_info.st_gid);
    printf("Size in Bytes: %ld\n", file_info.st_size);

    print_time("Time of Last Access", file_info.st_atim.tv_sec, file_info.st_atim.tv_nsec);
    print_time("Time of Last Modification", file_info.st_mtim.tv_sec, file_info.st_mtim.tv_nsec);
    print_time("Time of Last File Status Change", file_info.st_ctim.tv_sec, file_info.st_ctim.tv_nsec);

    printf("Best I/O Block Size: %lu\n", (unsigned long)file_info.st_blksize);
    printf("Number of Disk Blocks Allocated: %lu\n", (unsigned long)file_info.st_blocks);
}
void print_time(const char *label, time_t seconds, long nanoseconds) {
    printf("%s: %ld seconds, %ld nanoseconds\n", label, seconds, nanoseconds);
}
