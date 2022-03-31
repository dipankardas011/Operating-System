#ifndef STDIO_H
#include <stdio.h>
#endif

/**
 * print a string in color
 * @param str input string
 * @param mode 1 for green, 2 for red 3 for yellow
 * @return void
 */
void __printer_color(char *str, int mode) {
  switch(mode) {
    case 1:
      printf("\033[1;32m %s \033[0m\n",str);
      break;
    case 2:
      printf("\033[1;31m %s \033[0m\n",str);
      break;
    case 3:
      printf("\033[1;33m %s \033[0m\n",str);
      break;
    default:
      return;
  }
}