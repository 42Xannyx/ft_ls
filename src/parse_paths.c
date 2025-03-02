#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "libft.h"

#define MAX_PATHS 1024

uint32_t count_paths(char **argv) {
  uint32_t len = 0;

  for (int32_t i = 1; argv[i]; i++) {
    if (argv[i][0] == '-') {
      continue;
    }

    len += 1;
  }

  return len;
}

const char **parse_paths(char **argv) {
  bool no_path = false;
  const char **paths = malloc(MAX_PATHS * sizeof(char *));

  for (int32_t i = 1; argv[i]; i++) {
    if (argv[i][0] == '-') {
      continue;
    }

    paths[i - 1] = ft_strdup(argv[i]);

    no_path = true;
  }

  if (no_path == false) {
    paths[0] = ft_strdup(".");
  }

  return (const char **)paths;
}
