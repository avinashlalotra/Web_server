#ifndef CSAPP_H
#define CSAPP_H

#include "headers.h"

ssize_t rio_readn(int fd, void *usrbuf, size_t n);

/**
 * rio_writen - Write n bytes to a file descriptor from a buffer.
 *
 * @fd: The file descriptor to which data will be written.
 * @usrbuf: A pointer to the buffer containing the data to be written.
 * @n: The number of bytes to write to the file descriptor.
 *
 * Return: The number of bytes written on success.
 *         -1 on error, with errno set to indicate the error.
 */
ssize_t rio_writen(int fd, const void *usrbuf, size_t n);

#define RIO_BUFSIZE 8192

typedef struct {
    int rio_fd;         // File descriptor associated with this buffer
    int rio_cnt;        // Number of unread bytes in the buffer
    char *rio_bufptr;   // Pointer to the next unread byte in the buffer
    char rio_buf[RIO_BUFSIZE]; // Internal buffer to hold data
} rio_t;

/**
 * rio_readinitb - Initialize a Rio buffer object.
 *
 * @rp: A pointer to the Rio buffer object to be initialized.
 * @fd: The file descriptor to be associated with the buffer.
 *
 * This function initializes the Rio buffer object to use the specified file descriptor.
 */
void rio_readinitb(rio_t *rp, int fd);

/**
 * rio_readlineb - Read a line from a Rio buffer object.
 *
 * @rp: A pointer to the Rio buffer object from which data will be read.
 * @usrbuf: A pointer to the buffer where the read line will be stored.
 * @maxlen: The maximum number of bytes to read, including the terminating null byte.
 *
 * Return: The number of bytes read on success.
 *         0 if end-of-file is reached.
 *         -1 on error, with errno set to indicate the error.
 */
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

/**
 * rio_readnb - Read n bytes from a Rio buffer object.
 *
 * @rp: A pointer to the Rio buffer object from which data will be read.
 * @usrbuf: A pointer to the buffer where the data will be stored.
 * @n: The number of bytes to read from the buffer.
 *
 * Return: The number of bytes read on success.
 *         0 if end-of-file is reached.
 *         -1 on error, with errno set to indicate the error.
 */
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);


/**
 * metadata - displays all the file Metadata using stat function
 * @filename - A pointer to the filename
 * 
 */
void metadata(const char *filename);


#endif // CSAPP_H
