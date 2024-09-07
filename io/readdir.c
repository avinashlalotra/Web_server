#include "../include/csapp.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    DIR *streamp;
    struct dirent *dep;

    streamp = opendir(argv[1]);
    errno = 0;
    while ((dep = readdir(streamp)) != NULL) {
        printf("Found file: %s\n", dep->d_name);
        }
    if (errno != 0)
        perror("readdir error");
        closedir(streamp);
    exit(0);
    }