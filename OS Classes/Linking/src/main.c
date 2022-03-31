#ifndef STDIO_H
#include <stdio.h>
#endif

#include "../lib/header.h"
#include "../dLib/header.h"

int main() {
  printf("Add(3, 5) = %d\n", adder(3, 5));

  __printer_color("NICE", 1);
  __printer_color("WORLD", 2);
  __printer_color("Dipankar", 3);
  

  char *str = "Dipankar";
  printf("STAT of %s :: %d\n", str, isLower(str));

  return 0;
}