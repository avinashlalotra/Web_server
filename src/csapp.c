#include "../include/csapp.h"
#include <string.h> // For memcpy
#include <stdio.h>
#include <time.h>
ssize_t rio_readn(int fd, void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR)  // Interrupted by signal handler; try again
                nread = 0;
            else
                return -1; // Error; errno set by read()
        } else if (nread == 0) {
            break; // EOF
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft); // Return >= 0
}

ssize_t rio_writen(int fd, const void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nwrite;
    const char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nwrite = write(fd, bufp, nleft)) <= 0) {
            if (errno == EINTR)
                nwrite = 0;
            else
                return -1; // Error; errno set by write()
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return n;
}

void rio_readinitb(rio_t *rp, int fd) {
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n) {
    int cnt;
    while (rp->rio_cnt <= 0) {
        // Refill buffer if empty
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if (rp->rio_cnt < 0) {
            if (errno != EINTR) // Interrupted by signal handler
                return -1;
        } else if (rp->rio_cnt == 0) { // EOF
            return 0;
        } else {
            rp->rio_bufptr = rp->rio_buf; // Reset buffer pointer
        }
    }
    // Copy min(n, rp->rio_cnt) bytes from internal buf to user buf
    cnt = (n < rp->rio_cnt) ? n : rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) {
    int n, rc;
    char c, *bufp = usrbuf;

    for (n = 1; n < maxlen; n++) {
        if ((rc = rio_read(rp, &c, 1)) == 1) {
            *bufp++ = c;
            if (c == '\n') {
                n++;
                break;
            }
        } else if (rc == 0) {
            if (n == 1)
                return 0; // EOF, no data read
            else
                break; // EOF, some data read
        } else {
            return -1; // Error
        }
    }
    *bufp = '\0'; // Null terminate
    return n - 1;
}

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nread = rio_read(rp, bufp, nleft)) < 0)
            return -1; // Error; errno set by rio_read()
        else if (nread == 0)
            break; // EOF
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft); // Return >= 0
}


void metadata(const char *filename) {
    struct stat Stat;

    // Retrieve file status
    if (stat(filename, &Stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Print file metadata
    printf("File Metadata for: %s\n", filename);
    printf("===============================\n");
    printf("Device ID             : %lu\n", (unsigned long) Stat.st_dev);
    printf("Inode Number          : %lu\n", (unsigned long) Stat.st_ino);
    printf("File Mode             : %o\n", Stat.st_mode & (S_IFMT | S_IRWXU | S_IRWXG | S_IRWXO));
    printf("Number of Hard Links  : %lu\n", (unsigned long) Stat.st_nlink);
    printf("Owner UID             : %u\n", Stat.st_uid);
    printf("Owner GID             : %u\n", Stat.st_gid);
    printf("Device Type           : %lu\n", (unsigned long) Stat.st_rdev);
    printf("Size                  : %lld bytes\n", (long long) Stat.st_size);
    printf("Block Size            : %lu bytes\n", (unsigned long) Stat.st_blksize);
    printf("Blocks Allocated      : %llu\n", (unsigned long long) Stat.st_blocks);
    printf("Last Access Time      : %s", ctime(&Stat.st_atime));
    printf("Last Modification Time: %s", ctime(&Stat.st_mtime));
    printf("Last Status Change Time: %s", ctime(&Stat.st_ctime));
    printf("===============================\n");
}