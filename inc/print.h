#ifndef PRINT_H
#define PRINT_H

#include <dirent.h>

void print_directory(char *);

void print_entry(struct dirent *, const char *);

#endif /* PRINT_H */
