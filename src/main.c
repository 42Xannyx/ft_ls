#include <stdint.h>

#include "parse_flags.h"

int32_t main(int32_t argc, char *argv[]) {
  t_flags flags = parse_flags(argc, argv);

  print_flags(&flags);

  return 0;
}
