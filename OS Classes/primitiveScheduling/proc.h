#ifndef STDLIB_H
#include <stdlib.h>
#endif

enum state {
  RUNNING,
  RUNNABLE,
  // WAITING,
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
};

struct proc* Rqueue = NULL;
int *tempStoreBT = NULL;
