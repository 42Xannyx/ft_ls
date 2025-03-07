#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ft_printf.h"
#include "libft.h"
#include "parse_flags.h"
#include "parse_paths.h"
#include "print.h"
#include "quicksort.h"
#include "utils.h"

t_flags g_flags = {0};

uint32_t count_entries(const char *path) {
  DIR *dir = opendir(path);

  if (!dir) {
    perror("Error while opening dir");
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

  if (!dir) {
    perror("Error while opening dir");
    exit(1);
  }

  int32_t i = 0;
  struct dirent *entry;
  struct dirent **entries = malloc(n * sizeof(struct dirent *) + 1);
  if (!entries) {
    perror("An error occured in malloc()");
    exit(1);
  }

  while ((entry = readdir(dir)) != NULL) {
    entries[i] = malloc(sizeof(struct dirent));
    if (!entries[i]) {
      perror("Memory allocation failed");
      exit(1);
    }

    ft_memcpy(entries[i], entry, sizeof(struct dirent));

    i += 1;
  }

  entries[i] = NULL;

  closedir(dir);
  return entries;
}

void get_directory(const char *path, uint32_t amount_paths) {
  struct stat buf = {0};
  if (stat(path, &buf) < 0) {
    perror("Error in stat()");
    exit(1);
  }

  if (!S_ISDIR(buf.st_mode)) {
    print_file((char *)path, buf, count_digits(buf.st_size), 1);

    return;
  }

  if (g_flags.recursive == true || amount_paths > 1) {
    ft_printf("\n%s:\n", path);
  }

  const uint32_t count = count_entries(path);
  struct dirent **entries = get_entries(path, count);

  quicksort((char *)path, entries, 0, count - 1);

  int32_t width_size = 0;
  int32_t width_link = 0;
  int32_t blocks = 0;
  for (int32_t i = 0; entries[i]; i++) {
    struct stat buf = {0};

    if (entries[i]->d_name[0] == '.' && g_flags.all == false) {
      continue;
    }

    get_stat(&buf, (char *)path, *entries[i]);

    blocks += buf.st_blocks;
    int32_t buf_size_digits = count_digits(buf.st_size);
    if (width_size < buf_size_digits) {
      width_size = buf_size_digits;
    }

    int32_t buf_link_digits = count_digits(buf.st_nlink);
    if (width_link < buf_link_digits) {
      width_link = buf_link_digits;
    }
  }

  if (g_flags.list == true) {
    ft_printf("total %d\n", blocks / 2);
  }

  for (int32_t i = 0; entries[i]; i++) {
    if (entries[i]->d_name[0] == '.' && g_flags.all == false) {
      continue;
    }

    print_entry(entries[i], path, width_size, width_link);
  }

  if (g_flags.recursive == false) {
    for (int32_t i = 0; entries[i]; i++) {
      free(entries[i]);
    }
    free(entries);

    return;
  }

  for (int32_t i = 0; entries[i]; i++) {
    if (ft_strcmp(entries[i]->d_name, ".") == 0 ||
        ft_strcmp(entries[i]->d_name, "..") == 0) {
      continue;
    }

    if (entries[i]->d_type != DT_DIR) {
      continue;
    }

    if (g_flags.all == false && entries[i]->d_name[0] == '.') {
      continue;
    }

    char *next_path = ft_calloc(sizeof(char), MAX_PATH_LEN);
    if (!next_path) {
      perror("ft_ls: memory allocation failed");
      exit(1);
    }

    ft_strlcpy(next_path, path, MAX_PATH_LEN);
    ft_strlcat(next_path, "/", MAX_PATH_LEN);
    ft_strlcat(next_path, entries[i]->d_name, MAX_PATH_LEN);

    get_directory(next_path, amount_paths);
    free(next_path);
  }

  for (int32_t i = 0; entries[i]; i++) {
    free(entries[i]);
  }

  free(entries);
}

int32_t main(int32_t argc, char *argv[]) {
  if (argc > MAX_PATHS) {
    return 1;
  }

  g_flags = parse_flags(argc, argv);
  const char **paths = parse_paths(argv);
  uint32_t count = count_paths(argv);

  for (int32_t i = 0; paths[i]; i++) {
    get_directory(paths[i], count);
    free((char *)paths[i]);
  }

  free(paths);
  return 0;
}
