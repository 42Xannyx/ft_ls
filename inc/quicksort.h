#ifndef QUICKSORT
#define QUICKSORT

#include <dirent.h>
#include <stdint.h>

void partition(struct dirent **, int32_t, int32_t);

void quicksort(struct dirent **, int32_t, int32_t);

#endif // !QUICKSORT
