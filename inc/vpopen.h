#ifndef __VPOPEN_H
#define __VPOPEN_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

long open_max(void);
FILE *vpopen(const char* cmdstring, const char *type);
int vpclose(FILE *fp);


#endif