#include <stdio.h>
#include "apue.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int value;

    if (argc != 2)
        err_quit("usage: %s <descriptor#>", argv[0]);

    int file = atoi(argv[1]);

    if ((value = fcntl(file, F_GETFL, 0)) < 0)
        err_sys("fcntl error for fd %d", file);

    switch(value & O_ACCMODE) {
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
            err_dump("Access mode not known");
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
    return 0;
}

