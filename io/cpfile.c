#include "../include/csapp.h"
#define MAXLINE 20
int main(int argc, char **argv){
    int n;
    rio_t rio;
    char buf[MAXLINE];
    rio_readinitb(&rio, STDIN_FILENO);
    while((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
        rio_writen(STDOUT_FILENO, buf, n);
}