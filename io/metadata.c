#include <../include/csapp.h>
#include <time.h>
#include <stdio.h>
void print_file_metadata(const char *filename) {
    struct stat file_stat;

    // Get file metadata
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Print file metadata
    printf("File: %s\n", filename);

    // Device ID
    printf("Device ID: %lu\n", (unsigned long)file_stat.st_dev);

    // Inode number
    printf("Inode number: %lu\n", (unsigned long)file_stat.st_ino);

    // File mode (protection and file type)
    printf("Mode: %o\n", (unsigned int)file_stat.st_mode);

    // Number of hard links
    printf("Number of hard links: %lu\n", (unsigned long)file_stat.st_nlink);

    // User ID of owner
    printf("Owner UID: %u\n", (unsigned int)file_stat.st_uid);

    // Group ID of owner
    printf("Owner GID: %u\n", (unsigned int)file_stat.st_gid);

    // Device type (if inode device)
    printf("Device type: %lu\n", (unsigned long)file_stat.st_rdev);

    // Total size, in bytes
    printf("Size: %lld bytes\n", (long long)file_stat.st_size);

    // Block size for filesystem I/O
    printf("Block size: %lu bytes\n", (unsigned long)file_stat.st_blksize);

    // Number of blocks allocated
    printf("Blocks allocated: %lu\n", (unsigned long)file_stat.st_blocks);

    // Time of last access
    printf("Last access time: %s", ctime(&file_stat.st_atime));

    // Time of last modification
    printf("Last modification time: %s", ctime(&file_stat.st_mtime));

    // Time of last status change
    printf("Last status change time: %s", ctime(&file_stat.st_ctime));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    metadata(argv[1]);

    return 0;
}
