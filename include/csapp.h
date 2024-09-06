#ifndef CSAPP_H
#define CSAPP_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Function declarations
int close(int fd); 
// Returns 0 if OK, -1 on error

ssize_t read(int fd, void *buf, size_t n);
// Returns number of bytes read if OK, 0 on EOF, -1 on error

ssize_t write(int fd, const void *buf, size_t n);
// Returns number of bytes written if OK, -1 on error

ssize_t rio_readn(int fd, void *usrbuf, size_t n);
// Read n bytes from a descriptor into usrbuf
// Returns number of bytes read if OK, 0 on EOF, -1 on error

ssize_t rio_writen(int fd, const void *usrbuf, size_t n);
// Write n bytes to a descriptor from usrbuf
// Returns number of bytes written if OK, -1 on error
#define RIO_BUFSIZE 8192

typedef struct {
    int rio_fd; // Descriptor for internal buffer
    int rio_cnt; // Unread bytes in internal buf
    char *rio_bufptr; // Next unread byte in internal buf
    char rio_buf[RIO_BUFSIZE]; // Internal buffer
} rio_t;

void rio_readinitb(rio_t *rp, int fd);
// Initialize a Rio buffer object

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
// Read a line from the Rio buffer object into usrbuf
// Returns number of bytes read if OK, 0 on EOF, -1 on error

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
// Read n bytes from the Rio buffer object into usrbuf
// Returns number of bytes read if OK, 0 on EOF, -1 on error


#endif // CSAPP_H
