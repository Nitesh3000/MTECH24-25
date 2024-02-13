#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>   
#include <sys/stat.h> 

#define TempFile "./temporaryFile.txt"

int main() {
    int fd = open(TempFile, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Temporary file creation error");
        return 1;
    }

    FILE *temp = fdopen(fd, "w");
    if (temp == NULL) {
        perror("File Descriptor opening error");
        close(fd); // Close the file descriptor in case of an error
        return 1;
    }

    fprintf(temp, "Writing some content in the temporary file");

    fclose(temp);
    printf("Waiting for 30 second to check the file in the current directory and see the content in the file.\nSee the file \"temporaryFile.txt\" gets deleted after the execution of the code using unlink");
    sleep(30);

    if (unlink(TempFile) != 0) {
        perror("Temporary file deletion error");
        return 1;
    }

    return 0;
}

