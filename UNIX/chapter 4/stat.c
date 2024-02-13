#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filename = "/home/et2023/Documents/SEM2/UNIX/telephone_book.txt";
    struct stat file_info;

    if (stat(filename, &file_info) == 0) {
        // File information successfully obtained, you can access it in the 'file_info' structure.
        printf("Number of Blocks allocated: %lld bytes\n", (long long)file_info.st_blocks);
    } else {
        // An error occurred, check 'errno' for details.
        perror("Error getting file information");
    }

    return 0;
}
