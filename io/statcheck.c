#include "../include/csapp.h"
#include<stdio.h>
int main( int argc , char **argv) {

    struct stat Stat ;
    char *type , *readok ;

    stat(argv[1],&Stat) ;
    if (S_ISREG(Stat.st_mode))  /* Determine file type */
        type = "regular";
    else if (S_ISDIR(Stat.st_mode))
        type = "directory";
    else
        type = "other";
    if ((Stat.st_mode & S_IRUSR)) /* Check read access */
        readok = "yes";
    else
        readok = "no";
    printf("type: %s, read: %s\n", type, readok);
    return 0;
}