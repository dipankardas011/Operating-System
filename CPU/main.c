#include "../Memory/VirtualMemo/proc.h"
#include "scheduler.c"
// #include "syscall.c"
u_int64_t CLK = 0;
int Smain()
{
  struct proc **processTT = BLACKHOLE;
  struct readyQueue *readyQueueTT = BLACKHOLE;
  initReadyQueue(&readyQueueTT);
  turnONQueue(&processTT);
  buildProcessTable(&processTT);
  for (size_t i = 0; i < NO_PROCESSES; i++)
  {
    printOutProcessDetails(processTT[i]);
  }

  /**
   * start the scheduler
   */
  schedulerRoundRobin(&processTT, &readyQueueTT);
  return 0;
}
