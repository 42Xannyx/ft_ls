#ifndef PARSE_FLAGS
#define PARSE_FLAGS

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  bool all;       // -a: Do not ignore entries starting with `.`
  bool list;      // -l: Use a long listing format
  bool recursive; // -R: List subdirectories recursively
  bool reverse;   // -r: Reverse order while sorting
  bool time;      // -t: Sort by time, newest first; see --time
} t_flags;

extern t_flags g_flags;

t_flags parse_flags(int32_t, char **);

#endif // !PARSE_FLAGS
