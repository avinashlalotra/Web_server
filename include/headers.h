#ifndef HEADERS_H
#define HEADERS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>

/* Function Declarations */

/**
 * close - Close a file descriptor.
 *
 * @fd: The file descriptor to be closed.
 *
 * Return: 0 on success. -1 on error, with errno set to indicate the error.
 */
int close(int fd); 

/**
 * read - Read data from a file descriptor.
 *
 * @fd: The file descriptor from which data is to be read.
 * @buf: A pointer to the buffer where the read data will be stored.
 * @n: The number of bytes to read from the file descriptor.
 *
 * Return: The number of bytes read on success. 
 *         0 if end-of-file is reached.
 *         -1 on error, with errno set to indicate the error.
 */
ssize_t read(int fd, void *buf, size_t n);

/**
 * write - Write data to a file descriptor.
 *
 * @fd: The file descriptor to which data will be written.
 * @buf: A pointer to the buffer containing the data to be written.
 * @n: The number of bytes to write to the file descriptor.
 *
 * Return: The number of bytes written on success.
 *         -1 on error, with errno set to indicate the error.
 */
ssize_t write(int fd, const void *buf, size_t n);

/**
 * rio_readn - Read n bytes from a file descriptor into a buffer.
 *
 * @fd: The file descriptor from which data is to be read.
 * @usrbuf: A pointer to the buffer where the read data will be stored.
 * @n: The number of bytes to read from the file descriptor.
 *
 * Return: The number of bytes read on success.
 *         0 if end-of-file is reached.
 *         -1 on error, with errno set to indicate the error.
 */


/* 
 * struct stat - Structure that holds information about a file or directory.
 *
 * This structure is used to retrieve and store information about a file or 
 * directory, including its size, permissions, and timestamps. It is typically
 * populated using the `stat`, `fstat`, or `lstat` system calls.

* struct stat {
*    dev_t st_dev;     Device ID: Identifier for the device containing the file 
*    
*    ino_t st_ino;      Inode number: Unique identifier for the file within the device 
*    
*    mode_t st_mode;    File mode: Contains file type and protection (permissions) information.
*                       For example, `S_IFREG` indicates a regular file, `S_IFDIR` indicates a directory,
*                       and the permission bits indicate read, write, and execute permissions for the owner, group, and others. 
*    
*    nlink_t st_nlink;  Number of hard links: Count of directory entries referring to this file 
*    
*    uid_t st_uid;      User ID of owner: ID of the user who owns the file 
*    
*    gid_t st_gid;      Group ID of owner: ID of the group that owns the file 
*    
*    dev_t st_rdev;     Device type (if inode is a device file): For character or block devices, this field contains the device type.
*                       For regular files, this is typically `0`. 
*    
*    off_t st_size;     Total size in bytes: Size of the file in bytes 
*    
*    unsigned long st_blksize;  Block size for filesystem I/O: Optimal block size for file system operations. 
*    
*    unsigned long st_blocks;   Number of blocks allocated: Number of blocks allocated to the file. Each block is typically 512 or 4096 bytes. 
*    
*    time_t st_atime;  Time of last access: The time when the file was last accessed (read or executed). 
*    
*    time_t st_mtime;  Time of last modification: The time when the file content was last modified. 
*    
*   time_t st_ctime;  Time of last status change: The time when the file's metadata (permissions or ownership) was last changed. 
* } ;
*/



/**
 * stat - Get file status.
 *
 * @filename: The name of the file whose status is to be retrieved.
 * @buf: A pointer to a stat structure where the file status information will be stored.
 *
 * Return: 0 on success. -1 on error, with errno set to indicate the error.
 */
int stat(const char *filename, struct stat *buf);

/**
 * fstat - Get file status from a file descriptor.
 *
 * @fd: The file descriptor of the file whose status is to be retrieved.
 * @buf: A pointer to a stat structure where the file status information will be stored.
 *
 * Return: 0 on success. -1 on error, with errno set to indicate the error.
 */
int fstat(int fd, struct stat *buf);




/**
 * opendir - Open a directory stream.
 *
 * @name: The name of the directory to open.
 *
 * Return: A pointer to a DIR structure representing the directory stream on success.
 *         NULL on error, with errno set to indicate the error.
 */
DIR *opendir(const char *name);

/**
 * readdir - Read a directory entry.
 *
 * @dirp: A pointer to a DIR structure representing the directory stream.
 *
 * Return: A pointer to a dirent structure representing the directory entry on success.
 *         NULL on error or end-of-directory, with errno set to indicate the error.
 */
struct dirent *readdir(DIR *dirp);

/**
 * closedir - Close a directory stream.
 *
 * @dirp: A pointer to a DIR structure representing the directory stream to close.
 *
 * Return: 0 on success. -1 on error, with errno set to indicate the error.
 */
int closedir(DIR *dirp);

/**
 * exit - exits the program
 * @status - 0 for succes and other for failure
 */
void exit(int status);

#endif // HEADERS_H
