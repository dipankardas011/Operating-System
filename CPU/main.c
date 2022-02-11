#include "../Memory/VirtualMemo/proc.h"
#include "scheduler.c"
// #include "syscall.c"

int Smain()
{
  struct readyQueue *pTable = BLACKHOLE;
  initReadyQueue(&pTable);
  turnONQueue(&pTable);
  return 0;
}
