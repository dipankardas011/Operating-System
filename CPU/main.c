#include "../Memory/VirtualMemo/proc.h"
#include "scheduler.c"
// #include "syscall.c"
u_int64_t CLOCK_TIME = 0;

#define SCH_DULE  30
#define INT_RUPT  31

int (*__cpu__can__call__[])(struct proc ***, struct readyQueue **) = {
  [SCH_DULE] schedulerRoundRobin
};


/**
 * @return NULL when no process has to be added to the ready queue(means its done)
 * otherwise the process which has to be added will be returned
 */
struct proc* __CPU__EXECUTION__AREA__(struct readyQueue **readyQueueRAM, int* whichQueue)
{
  int decussion = __which_Queue_cpu_will_access(*readyQueueRAM);
  struct proc *processToRun = BLACKHOLE;
  *whichQueue = decussion;

  switch (decussion) {
    case 1:
      {
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q1);
        (*readyQueueRAM)->Q1 = __pop_front((*readyQueueRAM)->Q1);

        printf("+| %s |+", processToRun->name);

        /**
         * TODO: something to do
         */
        processToRun->state = RUNNING;
        /**
         * TODO: Add another processes which have come and place this in scheduling part
         */
        int qt1 = (*readyQueueRAM)->Qt1;
        while (qt1 > 0 && processToRun->burstTime > 0 ) {
          qt1--;
          (processToRun->burstTime)--;
          CLOCK_TIME++;
        }
        if (processToRun->burstTime > 0 && qt1 == 0) {
          // reinsert it in second Queue
          // as it has crossed its usage time in most pri queue
          // just for now place the removed queue to the same qeue which is here Q1
          // (*readyQueueRAM)->Q2 = __push_rear((*readyQueueRAM)->Q2, processToRun);
          processToRun->state = RUNNABLE;
        }
        if (processToRun->burstTime == 0 && qt1 >= 0) {
          // free the memory allocated
          free(processToRun);
          processToRun = BLACKHOLE;
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
  return processToRun;
}
/***
 * ASSUME that all the processes has arrival time to be 0
 */

int Smain()
{
  struct proc **processTT = BLACKHOLE;
  struct readyQueue *readyQueueTT = BLACKHOLE;
  initReadyQueue(&readyQueueTT);
  turnONQueue(&processTT);
  buildProcessTable(&processTT);
  
  // equavalent to $ ps -la
  for (size_t i = 0; i < NO_PROCESSES; i++)
  {
    printOutProcessDetails(processTT[i]);
  }

  /**
   * start the scheduler
   */
  schedulerRoundRobin(&processTT, &readyQueueTT);
  while (True) {
    // if all the queues are empty then stop the computer/shutdown
    if (__ALL__DONE__(readyQueueTT) == True) {
      break;
    }
    int whichQueue = 0;
    struct proc *callBack = __CPU__EXECUTION__AREA__(&readyQueueTT, &whichQueue);
    if (callBack == BLACKHOLE) {
      // that particular process has completed no need to add at the end
      continue;
    }
    // CPU has done its thing how the time interrupt will occur
    // followed by scheduling algo to refresh itself
    // int res = __cpu__can__call__[SCH_DULE](&processTT, &readyQueueTT);
    // printf("+++++++++++++\n");
    // printf("+ Verify is it getting it back\n");
    // ///**, remBurstTime:(%d),*/
    // printf("+ name:(%s) CLOCK TIME:(%ld)\n",callBack->name, CLOCK_TIME);
    // printf("+++++++++++++\n");

    int ret = schedulerRoundRobinSCH(callBack, &readyQueueTT, whichQueue);
    if (ret == UNDEFINED)
      return UNDEFINED;
    // printf("~~~~~~~~\n");
    // currStateOfQueue(readyQueueTT);
    // printf("~~~~~~~~\n");
  }
  printf("\n");

  /**
   * deallocate the memory
   * as all the processes have completed
   */
  return 0;
}
