#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *file = argv[1];

    // Check if the entered file is a symbolic link
    struct stat fileStat;
    if (lstat(file, &fileStat) == -1) {
        perror("Error checking file status");
        return 1;
    }

    if (S_ISLNK(fileStat.st_mode)) {
        // If it's a symbolic link, read its target
        char linkTarget[PATH_MAX + 1];
        ssize_t linkLength = readlink(file, linkTarget, sizeof(linkTarget) - 1);
        if (linkLength == -1) {
            perror("Error checking for symbolic link");
            return 1;
        }
        // Null-terminate the link target string
        linkTarget[linkLength] = '\0'; 
        printf("The entered file is a symbolic link. Contents of the symbolic link file:\n%s\n", linkTarget);
    } else {
        printf("The entered file is not a symbolic link.\n");
    }

    return 0;
}
