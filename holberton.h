#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include<signal.h>

/* PATH Shell Functions */

char *_getenv(const char *name);
char **tokenize(char* buffer);
char **PATHtokenize(char* buffer);
int _strcmp(const char *s1, const char *s2);
char *concat(char *av, char *argv);
void sigint_handler(int sig);

/* Other Functions */

int _printPATHmembers(const char *name);

#endif /* HOLBERTON_H */
