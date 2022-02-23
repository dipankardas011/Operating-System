#include "../lib/kqueue.h"
#include "../IO/main.h"
#include <assert.h>
#include <stdio.h>
#define UNDEFINED       0x9999
#define DOWNGRADE_TIME  30
#define UPGRADE_TIME    20
#define NO_PROCESSES    4
/**
 *        ready queue all are Round Robin
 *     ==========================
 *            Q1 (pri) 1
 *  ->  --------------------   Qt = 2 unit
 *      --------------------    >>-------------------->> | CPU |
 *            Q2 (pri) 2                                 |     |
 *      --------------------   Qt = 4 unit >----------------> ^
 *      --------------------                                  |
 *            Q3 (pri) 3                                      |
 *      --------------------   Qt = 8 unit >-------------------
 *      --------------------
 * 
 *     ==========================
 * 
 * NOTE: if the process has exceeded the Qt of that queue and not yet finished 
 *        then: moves to below queue
 *      also then specific time as passed it cannot remain in same queue even if O/P
 *        for o/p within Qt it will remain in the queue
 * 
 *      if the process has been on the lower queue for a long time it 
 *        needs to be upgraded to the first queue after certain time
 */

extern u_int64_t CLOCK_TIME;

struct readyQueue 
{
  struct __LinkListHeaders    *Q1;
  int priQ1;
  int Qt1;

  struct __LinkListHeaders    *Q2;
  int priQ2;
  int Qt2;

  struct __LinkListHeaders    *Q3;
  int priQ3;
  int Qt3;
};

void printOutLoudPatQueue(struct __LinkListHeaders *ptr) {
  struct __LinkList *iter = ptr->front;
  while (iter!=BLACKHOLE) {
    printf("%p -> ", iter->data_ptr);
    iter = iter->next;
  }
  printf("[LAST]\n---\n");
}

void currStateOfQueue(struct readyQueue *rQue) {
  printf("Queue [ 1 ]\npri: %d, Quantum Time: %d\n",rQue->priQ1, rQue->Qt1);
  printOutLoudPatQueue(rQue->Q1);
  printf("Queue [ 2 ]\npri: %d, Quantum Time: %d\n", rQue->priQ2, rQue->Qt2);
  printOutLoudPatQueue(rQue->Q2);
  printf("Queue [ 3 ]\npri: %d, Quantum Time: %d\n",rQue->priQ3, rQue->Qt3);
  printOutLoudPatQueue(rQue->Q3);
}

/////// SETUP for the readyQueue  ///////
int initReadyQueue(struct readyQueue **pTable) {
  *pTable = (struct readyQueue *) malloc(sizeof(struct readyQueue));
  assert(*pTable);

  (*pTable)->Q1 = initKQueue();
  assert((*pTable)->Q1);
  (*pTable)->priQ1 = 1;
  (*pTable)->Qt1 = 2;

  (*pTable)->Q2 = initKQueue();
  assert((*pTable)->Q2);
  (*pTable)->priQ2 = 2;
  (*pTable)->Qt2 = 4;

  (*pTable)->Q3 = initKQueue();
  assert((*pTable)->Q3);
  (*pTable)->priQ3 = 3;
  (*pTable)->Qt3 = 8;

  return 0;
}


int __which_Queue_cpu_will_access(struct readyQueue *queueTable){
  if (isEmpty(queueTable->Q1->front) == True)
    // means that Q1 is empty
    if (isEmpty(queueTable->Q2->front) == True)
      if (isEmpty(queueTable->Q2->front) == True)
        return UNDEFINED;
      else
        return 3;
    else 
      return 2;
  else
    return 1;
}


int schedulerRoundRobinSCH(struct proc *processToAdd, struct readyQueue **queueTable, int whichQueue){
  
  if (whichQueue == 1)
    (*queueTable)->Q1 = __push_rear((*queueTable)->Q1, processToAdd);
  else if (whichQueue == 2)
    (*queueTable)->Q2 = __push_rear((*queueTable)->Q2, processToAdd);
  else if (whichQueue == 3) 
    (*queueTable)->Q3 = __push_rear((*queueTable)->Q3, processToAdd);
  else {
    fprintf(stderr, "UNMANAGEABLE EXCEPTION!!!!!");
    return UNDEFINED;
  }

  return 0;
}


int schedulerRoundRobin(struct proc ***processTT, struct readyQueue **queueTable, int mode){

  // check which can be loaded to the queue
  for (int i = 0; i < NO_PROCESSES; i++) {

    switch((*processTT)[i]->state) {
      case RUNNING:
        if (mode == 1)
          printf("ITS a 'RUNNING' PROC\n");
        break;

      case RUNNABLE:
        if (mode == 1)
          printf("ITS a 'RUNNABLE' PROC\n");
        // (*queueTable)->Q1 = __push_rear((*queueTable)->Q1, (*processTT)[i]);
        break;
      
      case WAITING:
        if (mode == 1)
          printf("ITS a 'WAITING' PROC\n");
        
        break;
      case READY:
        if (mode == 1)
          printf("ITS a 'READY' PROC after wakeup from I/O\n");
        (*processTT)[i]->state = RUNNABLE;
        (*queueTable)->Q1 = __push_rear((*queueTable)->Q1, (*processTT)[i]);
        break;

      /**
       * So we will check all the embryo process from table and push it onto the Ready Queue
       * based on the CLK time
       */
      case EMBRYO:
        if (mode == 1)
          printf("ITS a 'EMBRYO' PROC\n");
        if (CLOCK_TIME >= (*processTT)[i]->arrivalTime) {
          (*processTT)[i]->state = RUNNABLE;
          (*queueTable)->Q1 = __push_rear((*queueTable)->Q1, (*processTT)[i]);
        }
        break;

      case ZOMBIE:
        if (mode == 1)
          printf("ITS a 'ZOMBIE' PROC\n");
        break;

      case SLEEPING:
        if (mode == 1)
          printf("ITS a 'SLEEPING' PROC\n");
        break;
      
      case DIED:
        if (mode == 1)
          printf("ITS a 'DIED' PROC\n");
        break;

      default:
        if (mode == 1)
          fprintf(stderr, "Internal err 0x000\n");
    }
  }

  return 0;
}

bool _ALL_Processes_are_in_readyQueue(struct proc ***x) {
  for (int i = 0; i < NO_PROCESSES; i++) {
    if ((*x)[i]->state == EMBRYO || (*x)[i]->state == WAITING || (*x)[i]->state == READY)
      return False;
  }
  return True;
}

bool __ALL__DONE__(struct readyQueue *ptr) {
  // array of the proc
  return isEmpty(ptr->Q1->front) & isEmpty(ptr->Q2->front) & isEmpty(ptr->Q3->front);
}

////////  TESTING  ////////
void buildProcessTable(struct proc ***processTT){
  for (int i = 0;i <NO_PROCESSES; i++) {
    printf("Enter the {Arrival Time},{Burst time1},{IO time},{Burst time2} for process_[ %d ]\n", i);
    uint xx, yy1, yy2, io;
    scanf("%d %d %d %d", &xx, &yy1, &io, &yy2);
    (*processTT)[i]->arrivalTime = xx;
    (*processTT)[i]->burstTime1 = yy1;
    (*processTT)[i]->burstTime2 = yy2;
    (*processTT)[i]->IOTime = io;
  }
 
}

void turnONQueue(struct proc ***processTT){
  *processTT = (struct proc **)malloc(sizeof(struct proc *) * NO_PROCESSES);
  assert(*processTT);
  char namePP[16] = {'\0'};
  for (int i = 0; i < NO_PROCESSES; i++) {
    // namePP[0] = (char)(65 + i);
    namePP[0] = 'P';
    namePP[1] = (char)('0' + i + 1);
    (*processTT)[i] = initProcess(namePP, i + 1);
  }
  
}