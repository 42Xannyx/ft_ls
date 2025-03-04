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
  bool no_path = false;
  const char **paths = ft_calloc(1, MAX_PATHS * sizeof(char *));

  for (int32_t i = 1; argv[i]; i++) {
    if (argv[i][0] == '-') {
      continue;
    }

    paths[i - 1] = ft_strdup(argv[i - 1]);
    if (!paths[i - 1]) {
      perror("Error in malloc()");
      exit(1);
    }

    printf("paths: %s\n", paths[i - 1]);

    no_path = true;
  }

  if (no_path == false) {
    paths[0] = ft_strdup(".");

    if (!paths[0]) {
      perror("Error in malloc()");
      exit(1);
    }
  }

  return (const char **)paths;
}
