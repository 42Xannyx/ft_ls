#include "parse_flags.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_help(void) {
  printf("Usage: ft_ls [OPTION]... [FILE]...\n");
  printf("List information about the FILEs (the current directory by "
         "default).\n\n");

  printf("Options:\n");
  printf("  -a        do not ignore entries starting with .\n");
  printf("  -l        use a long listing format\n");
  printf("  -R        list subdirectories recursively\n");
  printf("  -r        reverse order while sorting\n");
  printf("  -t        sort by modification time, newest first\n");
  printf("  -h        display this help and exit\n\n");

  exit(0);
}

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
        case 'h':
          print_help();
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
