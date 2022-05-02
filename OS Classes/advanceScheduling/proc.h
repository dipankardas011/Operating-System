#ifndef STDLIB_H
#include <stdlib.h>
#endif

enum state {
  RUNNING,
  RUNNABLE,
  TERMINATED,
  EMBRYO
};


struct proc {
  int pid;
  int arrTime;
  int burstTime;
  enum state currState;
  int initStartTime;
  int finalEndTime;
  int priority;
};

struct proc* Rqueue = NULL;
int *tempStoreBT = NULL;
