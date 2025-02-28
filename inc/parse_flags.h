#ifndef PARSE_FLAGS
#define PARSE_FLAGS

#include <stdbool.h>

typedef struct {
  bool all;       // -a: Do not ignore entries starting with `.`
  bool list;      // -l: Use a long listing format
  bool recursive; // -R: List subdirectories recursively
  bool reverse;   // -r: Reverse order while sorting
  bool time;      // -t: Sort by time, newest first; see --time
} t_flags;

t_flags init_flags(void);

#endif // !PARSE_FLAGS
