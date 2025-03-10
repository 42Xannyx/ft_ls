#include <dirent.h>
#include <stdint.h>

#include "libft.h"
#include "parse_flags.h"
#include "utils.h"

int32_t compare_entries(char *path, struct dirent *a, struct dirent *b) {
  int32_t result;
  const char *a_name = a->d_name;
  const char *b_name = b->d_name;

  if (a_name[0] == '.')
    a_name++;
  if (b_name[0] == '.')
    b_name++;

  if (g_flags.time == true) {
    struct stat buf_a = {0};
    struct stat buf_b = {0};

    get_stat(&buf_a, path, *a);
    get_stat(&buf_b, path, *b);

    if (buf_a.st_mtim.tv_sec != buf_b.st_mtim.tv_sec) {
      return buf_b.st_mtim.tv_sec - buf_a.st_mtim.tv_sec;
    }

    return buf_b.st_mtim.tv_nsec - buf_a.st_mtim.tv_nsec;
  }

  while (*a_name && *b_name) {
    char a_char = ft_tolower(*a_name);
    char b_char = ft_tolower(*b_name);
    if (a_char != b_char) {
      result = a_char - b_char;

      return g_flags.reverse ? -result : result;
    }
    a_name++;
    b_name++;
  }

  result = ft_tolower(*a_name) - ft_tolower(*b_name);

  return g_flags.reverse ? -result : result;
}

struct dirent **swap_entries(struct dirent **entries, int32_t low,
                             int32_t high) {
  struct dirent *temp = entries[low];
  entries[low] = entries[high];
  entries[high] = temp;

  return entries;
}

int32_t partition(char *path, struct dirent **entries, int32_t low,
                  int32_t high) {
  struct dirent *pivot = entries[high];
  int32_t i = low - 1;

  for (int32_t j = low; j < high; j++) {
    if (compare_entries(path, entries[j], pivot) <= 0) {
      i += 1;
      swap_entries(entries, i, j);
    }
  }

  swap_entries(entries, i + 1, high);
  return i + 1;
}

void quicksort(char *path, struct dirent **entries, int32_t low, int32_t high) {
  if (low < high) {
    int32_t pivot = partition(path, entries, low, high);

    quicksort(path, entries, low, pivot - 1);
    quicksort(path, entries, pivot + 1, high);
  }
}
