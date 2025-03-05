#include <grp.h>
#include <pwd.h>
#include <stdint.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "ft_printf.h"
#include "libft.h"
#include "parse_flags.h"
#include "print.h"
#include "utils.h"

void set_permission(char *permissions, struct stat buf) {
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
}

void print_entry(struct dirent *entry, const char *path, int32_t width,
                 uint32_t width_link) {
  if (g_flags.list == false) {
    ft_putendl_fd(entry->d_name, STDOUT_FILENO);
    return;
  }

  struct stat buf = {0};
  get_stat(&buf, (char *)path, *entry);

  char formatted_time[13] = {0};
  char *time = ctime(&buf.st_mtim.tv_sec);

  ft_strlcpy(formatted_time, time + 4, 13);

  struct passwd *uid = getpwuid(buf.st_uid);
  struct group *grp = getgrgid(buf.st_gid);

  char permissions[11] = {0};
  set_permission(permissions, buf);

  ft_printf("%s", permissions);

  for (uint32_t i = 0; i <= width_link - count_digits(buf.st_nlink); i++) {
    ft_putchar_fd(' ', STDERR_FILENO);
  }

  ft_printf("%d %s %s", buf.st_nlink, uid->pw_name, grp->gr_name);

  for (int32_t i = 0; i <= width - count_digits(buf.st_size); i++) {
    ft_putchar_fd(' ', STDERR_FILENO);
  }

  ft_printf("%d %s %s\n", buf.st_size, formatted_time, entry->d_name);
}
