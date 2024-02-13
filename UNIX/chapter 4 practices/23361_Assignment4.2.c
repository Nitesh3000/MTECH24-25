#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Function prototypes
void print_stat_info(const char *filename);
void print_time(const char *label, time_t seconds, long nanoseconds);

int main(int argc, char *argv[]) {
    // Check if filenames are provided
    if (argc < 1) {
        fprintf(stderr, "Usage: %s <filename1> <filename2> ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Iterate through each filename passed as a command-line argument
    for (int i = 1; i < argc; ++i) {
        print_stat_info(argv[i]);
    }

    return 0;
}

// Function to print stat information for a file
void print_stat_info(const char *filename) {
    // Create a struct stat to hold file information
    struct stat file_info;

    // Use stat to get information about the file
    if (stat(filename, &file_info) == -1) {
        perror("Error getting file information");
        return;
    }

    // Print various details from the struct stat
    printf("\nFile: %s\n", filename);
    printf("File Type & Mode: %o\n", file_info.st_mode);
    printf("Inode Number: %lu\n", (unsigned long)file_info.st_ino);
    printf("Device Number (File System): %lu\n", (unsigned long)file_info.st_dev);
    printf("Number of Links: %lu\n", (unsigned long)file_info.st_nlink);
    printf("User ID of Owner: %u\n", file_info.st_uid);
    printf("Group ID of Owner: %u\n", file_info.st_gid);
    printf("Size in Bytes: %ld\n", file_info.st_size);

    // Print times using a separate function for clarity
    print_time("Time of Last Access", file_info.st_atim.tv_sec, file_info.st_atim.tv_nsec);
    print_time("Time of Last Modification", file_info.st_mtim.tv_sec, file_info.st_mtim.tv_nsec);
    print_time("Time of Last File Status Change", file_info.st_ctim.tv_sec, file_info.st_ctim.tv_nsec);

    printf("Best I/O Block Size: %lu\n", (unsigned long)file_info.st_blksize);
    printf("Number of Disk Blocks Allocated: %lu\n", (unsigned long)file_info.st_blocks);
}

// Function to print time information
void print_time(const char *label, time_t seconds, long nanoseconds) {
    printf("%s: %ld seconds, %ld nanoseconds\n", label, seconds, nanoseconds);
}