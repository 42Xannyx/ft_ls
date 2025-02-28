#include "parse_flags.h"

#include <stdint.h>
#include <stdio.h>

t_flags parse_flags(int32_t argc, char *argv[]) {
  t_flags flags = {0};

  if (argc <= 1) {
    return flags;
  }

  for (int32_t i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {

      for (int32_t j = 1; argv[i][j]; j++) {
        char c = argv[i][j];

        switch (c) {
        case 'R':
          flags.recursive = true;
          break;
        case 'r':
          flags.reverse = true;
          break;
        case 'a':
          flags.all = true;
          break;
        case 'l':
          flags.list = true;
          break;
        case 't':
          flags.time = true;
          break;
        default:
          fprintf(stderr, "Unknown option: -%c\n", c);
          break;
        }
      }
    }
  }

  return flags;
}

void print_flags(const t_flags *flags) {
  if (!flags) {
    printf("Error: NULL flags pointer\n");
    return;
  }

  printf("Flags status:\n");
  printf("  -a (all):       %s\n", flags->all ? "true" : "false");
  printf("  -l (list):      %s\n", flags->list ? "true" : "false");
  printf("  -R (recursive): %s\n", flags->recursive ? "true" : "false");
  printf("  -r (reverse):   %s\n", flags->reverse ? "true" : "false");
  printf("  -t (time):      %s\n", flags->time ? "true" : "false");
}
