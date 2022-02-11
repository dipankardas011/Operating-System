/**
 * TODO: implementation of the multilevel feedback queue scheduling
 */
#include "../lib/kqueue.h"
#include <assert.h>
#include <stdio.h>

#define DOWNGRADE_TIME  30
#define UPGRADE_TIME    20

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

static u_int64_t CLK = 0;

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

struct Process {
  char name[16];      // name
  uint pid;           // pid
  uint ppid;          // parent pid
  uint arrTime;       // arrival time to the process queue
  uint reqCPUTime;    // time for it to exectute
};


int initReadyQueue(struct readyQueue **pTable) {
  CLK = 1;
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

int schedulerRoundRobin(){
  return 0;
}

void buildProcessTable(){}

void turnONQueue(struct readyQueue **pTable){
  struct proc **processTable = BLACKHOLE;
  processTable = (struct proc **)malloc(sizeof(struct proc *) * 5);
  char namePP[16] = {'\0'};
  for (int i = 0; i < 5; i++) {
    namePP[0] = (char)(65 + i);
    namePP[1] = (char)(65 + i + 1);
    processTable[i] = initProcess(namePP, i + 1);
  }

  for (size_t i = 0; i < 5; i++)
  {
    printOutProcessDetails(processTable[i]);
  }
}