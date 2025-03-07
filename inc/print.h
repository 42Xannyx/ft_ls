#ifndef PRINT_H
#define PRINT_H

#include <dirent.h>
#include <stdint.h>
#include <sys/stat.h>

void print_entry(struct dirent *, const char *, int32_t, uint32_t);

void print_file(char *path, struct stat buf, int32_t width,
                uint32_t width_link);

#endif /* PRINT_H */
