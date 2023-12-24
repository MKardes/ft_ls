#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "./old";  // Change this to the path of your symbolic link

    struct stat fileStat;  // Structure to store file information
    struct stat linkStat;  // Structure to store symbolic link information

    // Use stat to get information about the target file (follows symbolic link)
    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    // Use lstat to get information about the symbolic link itself (does not follow symbolic link)
    if (lstat(filename, &linkStat) == -1) {
        perror("lstat");
        return 1;
    }

    // Display information obtained using stat
    printf("Information about the target file (follows symbolic link):\n");
    printf("Size: %lld bytes\n", fileStat.st_size);
    // Add more fields as needed...

    // Display information obtained using lstat
    printf("\nInformation about the symbolic link itself (does not follow symbolic link):\n");
    printf("Size: %lld bytes\n", linkStat.st_size);
    // Add more fields as needed...

    return 0;
}
