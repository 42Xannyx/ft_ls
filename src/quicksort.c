#include <ctype.h>
#include <dirent.h>
#include <stdint.h>

int compare_entries(struct dirent *a, struct dirent *b) {
  const char *a_name = a->d_name;
  const char *b_name = b->d_name;

  if (a_name[0] == '.')
    a_name++;
  if (b_name[0] == '.')
    b_name++;

  while (*a_name && *b_name) {
    char a_char = tolower(*a_name);
    char b_char = tolower(*b_name);

    if (a_char != b_char)
      return a_char - b_char;

    a_name++;
    b_name++;
  }

  return tolower(*a_name) - tolower(*b_name);
}

struct dirent **swap_entries(struct dirent **entries, int32_t low,
                             int32_t high) {
  struct dirent *temp = entries[low];
  entries[low] = entries[high];
  entries[high] = temp;

  return entries;
}

int32_t partition(struct dirent **entries, int32_t low, int32_t high) {
  struct dirent *pivot = entries[high];
  int32_t i = low - 1;

  for (int32_t j = low; j < high; j++) {
    if (compare_entries(entries[j], pivot) <= 0) {
      i += 1;
      swap_entries(entries, i, j);
    }
  }

  swap_entries(entries, i + 1, high);
  return i + 1;
}

void quicksort(struct dirent **entries, int32_t low, int32_t high) {
  if (low < high) {
    int32_t pivot = partition(entries, low, high);

    quicksort(entries, low, pivot - 1);
    quicksort(entries, pivot + 1, high);
  }
}
