#include "main.c"

int main(int argc, char const *argv[])
{
  printf("Welcome to the BOOT-UP\n");
  int ert = Smain();
  assert(ert == 0);
  return 0;
}
