#include "../Memory/VirtualMemo/proc.h"
#include "scheduler.c"
// #include "syscall.c"
u_int64_t CLK = 0;

#define SCH_DULE  30
#define INT_RUPT  31

int (*__cpu__can__call__[])(struct proc ***, struct readyQueue **) = {
  [SCH_DULE] schedulerRoundRobin
};

void __CPU__EXECUTION__AREA__(struct readyQueue ** readyQueueRAM) {
  int decussion = __which_Queue_cpu_will_access(*readyQueueRAM);
  struct proc *processToRun = BLACKHOLE;
  switch (decussion) {
    case 1:
      {
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q1);
        (*readyQueueRAM)->Q1 = __pop_front((*readyQueueRAM)->Q1);

        /**
         * TODO: something to do
         */

        /**
         * TODO: Add another processes which have come and place this in scheduling part
         */
        int qt1 = (*readyQueueRAM)->Qt1;
        while (qt1 > 0 && processToRun->burstTime > 0 ) {
          qt1--;
          (processToRun->burstTime)--;
        }
        if (processToRun->burstTime > 0 && qt1 == 0) {
          // reinsert it in second Queue
          // as it has crossed its usage time in most pri queue
          (*readyQueueRAM)->Q2 = __push_rear((*readyQueueRAM)->Q2, processToRun);
        }
        if (processToRun->burstTime == 0 && qt1 >= 0) {
          // free the memory allocated
          free(processToRun);
        }

        /**
         * TODO: I/O operation support to be added
         * TODO: PROMOTION of a process using @param{DOWNGRADE_TIME, UPGRADE_TIME}
         */
      }
      break;
    case 2:
      {
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q2);
        (*readyQueueRAM)->Q2 = __pop_front((*readyQueueRAM)->Q2);
      }
      break;
    case 3:
      {
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q3);
        (*readyQueueRAM)->Q3 = __pop_front((*readyQueueRAM)->Q3);
      }
      break;
    default:
      fprintf(stderr, "UNMANAGEABLE EXCEPTION!!!!!");
  }
}

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
