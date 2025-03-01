#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_flags.h"
#include "quicksort.h"

uint32_t count_entries(const char *path) {
  DIR *dir = opendir(path);

  // TODO: Handle error
  if (!dir) {
    exit(1);
  }

  struct dirent *entry;
  uint32_t count = 0;

  while ((entry = readdir(dir)) != NULL) {
    count += 1;
  }

  closedir(dir);
  return count;
}

struct dirent **get_entries(const char *path, uint32_t n) {
  DIR *dir = opendir(path);

  // TODO: Handle error
  if (!dir) {
    exit(1);
  }

  int32_t i = 0;
  struct dirent *entry;
  struct dirent **entries = malloc(n * sizeof(struct dirent *) + 1);
  if (!entries) {
    exit(1);
  }

  while ((entry = readdir(dir)) != NULL) {
    entries[i] = malloc(sizeof(struct dirent));
    entries[i] = entry;

    i += 1;
  }

  entries[i] = NULL;

  closedir(dir);
  return entries;
}

void get_directory(const char *path, const t_flags flags) {
  const uint32_t count = count_entries(path);
  struct dirent **entries = get_entries(path, count);

  quicksort(entries, 0, count - 1);

  for (int32_t i = 0; entries[i]; i++) {

    if (entries[i]->d_name[0] == '.') {

      if (flags.all == true) {
        printf("%s\n", entries[i]->d_name);
      }

    } else {
      printf("%s\n", entries[i]->d_name);
    }
  }
  // TODO: Check errno

  // get_directory(flags);
}

int32_t main(int32_t argc, char *argv[]) {
  t_flags flags = parse_flags(argc, argv);

  get_directory(".", flags);

  return 0;
}
