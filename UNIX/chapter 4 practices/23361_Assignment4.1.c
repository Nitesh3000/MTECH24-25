#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Set the umask to 0 to allow full permissions initially
    mode_t original_umask = umask(0);

    const char* filename = "UNIXassignment.txt";

    // permissions for user, group, and others
    mode_t user_permissions = S_IRUSR | S_IWUSR | S_IXUSR;  
    mode_t group_permissions = S_IRGRP | S_IWGRP | S_IXGRP;  
    mode_t other_permissions = S_IROTH | S_IWOTH | S_IXOTH;  

    mode_t full_permissions = user_permissions | group_permissions | other_permissions;

    int file_descriptor = open(
        filename,        
        O_CREAT | O_RDWR,// Create if not exists, Read-Write mode
        full_permissions  
    );

    if (file_descriptor == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    } else {
        printf("File '%s' created successfully with the following permissions:\n", filename);
        printf("User (Owner):   Read, Write, Execute\n");
        printf("Group:          Read, Write, Execute\n");
        printf("Others:         Read, Write, Execute\n");
        close(file_descriptor);
    }

    // Restore the original umask
    umask(original_umask);

    return 0;
}