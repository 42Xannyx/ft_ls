#ifndef PARSE_PATHS_H
#define PARSE_PATHS_H
#define MAX_PATHS 256

#include <stdint.h>

const char **parse_paths(char **);

uint32_t count_paths(char **);

#endif /* PARSE_PATHS_H */
