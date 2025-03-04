#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#include "libft.h"
#include "utils.h"

void get_stat(struct stat *buf, char *path, struct dirent entry) {
  char full_path[MAX_PATH_LEN];
  ft_memset(full_path, 0, MAX_PATH_LEN);

  ft_strlcpy(full_path, path, MAX_PATH_LEN);
  ft_strlcat(full_path, "/", MAX_PATH_LEN);
  ft_strlcat(full_path, entry.d_name, MAX_PATH_LEN);

  if (stat(full_path, buf) != 0) {
    perror("Error in stat");
    exit(1);
  }
}
