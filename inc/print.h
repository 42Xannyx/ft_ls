#ifndef PRINT_H
#define PRINT_H

#include <dirent.h>
#include <stdint.h>

void print_directory(char *);

void print_entry(struct dirent *, const char *, int32_t, uint32_t);

#endif /* PRINT_H */
