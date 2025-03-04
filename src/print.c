#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "libft.h"
#include "parse_flags.h"
#include "print.h"

#define MAX_PATH_LEN 1024

void print_directory(char *str) {
  if (write(STDOUT_FILENO, "\n", 1) < 0) {
    perror("write error");
  }

  ft_putstr_fd(str, STDOUT_FILENO);

  if (write(STDOUT_FILENO, ":\n", 2) < 0) {
    perror("write error");
  }
}

void print_entry(struct dirent *entry, const char *path) {
  if (g_flags.list == false) {
    ft_putendl_fd(entry->d_name, STDOUT_FILENO);
    return;
  }

  if (ft_strlen(path) + ft_strlen(entry->d_name) + 1 > MAX_PATH_LEN) {
    return;
  }

  char full_path[MAX_PATH_LEN];
  ft_memset(full_path, 0, MAX_PATH_LEN);

  ft_strlcpy(full_path, path, MAX_PATH_LEN);
  ft_strlcat(full_path, "/", MAX_PATH_LEN);
  ft_strlcat(full_path, entry->d_name, MAX_PATH_LEN);

  struct stat buf = {0};
  if (stat(full_path, &buf) != 0) {
    perror("Error in stat");
    exit(1);
  }

  char formatted_time[13] = {0};
  char *time = ctime(&buf.st_mtim.tv_sec);

  ft_strlcpy(formatted_time, time + 4, 13);

  char *size = ft_itoa(buf.st_size);
  struct passwd *uid = getpwuid(buf.st_uid);
  struct group *grp = getgrgid(buf.st_gid);

  char permissions[11] = {0};
  permissions[0] = S_ISDIR(buf.st_mode)    ? 'd'
                   : S_ISLNK(buf.st_mode)  ? 'l'
                   : S_ISFIFO(buf.st_mode) ? 'p'
                   : S_ISSOCK(buf.st_mode) ? 's'
                   : S_ISCHR(buf.st_mode)  ? 'c'
                   : S_ISBLK(buf.st_mode)  ? 'b'
                                           : '-';

  permissions[1] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
  permissions[2] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
  permissions[3] = (buf.st_mode & S_IXUSR) ? 'x' : '-';

  permissions[4] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
  permissions[5] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
  permissions[6] = (buf.st_mode & S_IXGRP) ? 'x' : '-';

  permissions[7] = (buf.st_mode & S_IROTH) ? 'r' : '-';
  permissions[8] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
  permissions[9] = (buf.st_mode & S_IXOTH) ? 'x' : '-';

  permissions[0] = S_ISDIR(buf.st_mode) ? 'd' : '-';

  printf("%s %ld %s %s %5s %s %s\n", permissions, buf.st_nlink, uid->pw_name,
         grp->gr_name, size, formatted_time, entry->d_name);
}
