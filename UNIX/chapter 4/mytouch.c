/*
to run this code:
gcc -o mytouch mytouch.c -I ../include/ -L ../../lib/ -lapue -lm
./touch filename.extension

*/
#include <fcntl.h>
#include <utime.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "apue.h"

void display_time(const char *file) {
    struct stat statbuf;

    if (stat(file, &statbuf) < 0) {
        err_ret("stat error for %s", file);
        exit(1);
    }

    printf("Access time: %s", ctime(&statbuf.st_atime));
    printf("Modification time: %s", ctime(&statbuf.st_mtime));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    const char *file = argv[1];
    struct stat statbuf;

    if (stat(file, &statbuf) < 0) {
        perror("stat error");
        fprintf(stderr, "File %s doesn't exist.\n", file);
        exit(1);
    }

    if (utime(file, NULL) < 0) {
        err_ret("utime error for %s", file);
        exit(1);
    }

    printf("Updated times for file %s:\n", file);
    display_time(file);

    printf("\nListing information using ls -l for %s:\n", file);
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", file);
    
    if (system(command) < 0) {
        perror("system error");
        exit(1);
    }

    exit(0);
}
