#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void list_directory(const char *directory_path) {
    DIR *dir = opendir(directory_path);

    if (dir == NULL) {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Use file_path as needed (e.g., print it)
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No directory argument provided, list the current directory
        list_directory(".");
    } else {
        // List the specified directory
        list_directory(argv[1]);
    }

    return EXIT_SUCCESS;
}
