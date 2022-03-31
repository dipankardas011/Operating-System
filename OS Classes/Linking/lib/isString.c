/**
 * isLower it checks whether given input is in lowercase or not
 * @param str input string pointer
 * @return 1 for true 0 for false
 */
int isLower(char *str) {
  for (int i = 0; str[i]; i++) {
    if (str[i] < 'a' || str[i] > 'z')
      return 0;
  }
  return 1;
}

