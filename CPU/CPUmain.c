#include "main.c"

void helper() {
  printf("This is the main program from which all the cpu related task are called\n");
  printf("--d\tfor debug mode\n");
  printf("--n\tfor normal mode\n\nEXITING CODE 0xaf4\n");
}

int main(int argc, char const *argv[])
{
  if (argc == 1) {
    helper();
    exit(0);
  }
  printf("\n$$$$ BOOTING $$$$\n\n");
  printf("%s\n\n", argv[1]);
  if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'd') {
    int ert = SMain(1);
    assert(ert == 0);
  } else if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'n') {
    int ert = SMain(2);     
    assert(ert == 0);
  }
  return 0;
}
