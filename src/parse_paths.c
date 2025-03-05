#include "parse_paths.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

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
  int32_t len = 0;
  bool no_path = true;
  const char **paths = ft_calloc(sizeof(char *), MAX_PATHS);
  if (!paths) {
    perror("Error in calloc()");
    exit(1);
  }

  for (int32_t i = 1; argv[i]; i++) {
    if (argv[i][0] == '-') {
      continue;
    }

    paths[len] = ft_strdup(argv[i]);
    if (!paths[len]) {
      perror("Error in malloc()");
      exit(1);
    }

    no_path = false;
    len += 1;
  }

  if (no_path == true) {
    paths[0] = ft_strdup(".");
    if (!paths[0]) {
      perror("Error in malloc()");
      exit(1);
    }
    len += 1;
  }

  paths[len] = NULL;

  return (const char **)paths;
}
