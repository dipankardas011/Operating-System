#include "scheduler.c"

int Smain()
{
  struct readyQueue *pTable = BLACKHOLE;
  initReadyQueue(&pTable);
  return 0;
}
