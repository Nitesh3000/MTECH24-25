#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void list_files(const char *path, int show_hidden, int long_format, int show_numeric, int show_directory);

int main(int argc, char *argv[]) {
    int opt;
    int show_hidden = 0;
    int long_format = 0;
    int show_numeric = 0;
    int show_directory = 0;

    while ((opt = getopt(argc, argv, "aldn")) != -1) {
        switch (opt) {
            case 'a':
                show_hidden = 1;
                break;
            case 'l':
                long_format = 1;
                break;
            case 'd':
                show_directory = 1;
                break;
            case 'n':
                show_numeric = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-l] [-n] [-d] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    const char *path = argc > optind ? argv[optind] : ".";

    list_files(path, show_hidden, long_format, show_numeric, show_directory);

    return 0;
}

void list_files(const char *path, int show_hidden, int long_format, int show_numeric, int show_directory) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (!show_hidden && entry->d_name[0] == '.')
            continue;

        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        if (long_format) {
            // Print permissions
            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" ");

            // Print number of links
            if (show_numeric)
                printf("%ld ", (long)file_stat.st_nlink);
            else
                printf("%-2ld ", (long)file_stat.st_nlink);

            // Print owner and group
            struct passwd *pwd = getpwuid(file_stat.st_uid);
            struct group *grp = getgrgid(file_stat.st_gid);
            printf("%-8s %-8s ", pwd->pw_name, grp->gr_name);

            // Print size
            if (show_numeric)
                printf("%ld ", (long)file_stat.st_size);
            else
                printf("%-5ld ", (long)file_stat.st_size);

            // Print last modified time
            char date[20];
            strftime(date, 20, "%b %d %H:%M", localtime(&(file_stat.st_mtime)));
            printf("%s ", date);
        }

        // Print file name
        printf("%s", entry->d_name);

        if (show_directory && S_ISDIR(file_stat.st_mode))
            printf("/");

        printf("\n");
    }

    closedir(dir);
}
