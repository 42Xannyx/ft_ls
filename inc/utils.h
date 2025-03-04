#ifndef UTILS_H
#define UTILS_H

#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH_LEN 1024

void get_stat(struct stat *, char *, struct dirent);

#endif /* UTILS_H */
