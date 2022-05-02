#ifndef STDLIB_H
#include <stdlib.h>
#endif
#define SIZE 10

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
};

struct proc* Rqueue = NULL;
int *tempStoreBT = NULL;

struct readyQueue {
  int frontIdx;
  int rearIdx;
  int arr[SIZE];
};

struct readyQueue RQ;

void initRQ() {
  RQ.frontIdx = RQ.rearIdx = -1;
}

int isEmptyRQ() {
  if (RQ.frontIdx == -1 && RQ.rearIdx == -1)
    return 1;
  return 0;
}

/**
 * @return status if 1 successful otherwise failure
 */
int pushRQ(int pid) {
  if (isEmptyRQ()) {
    RQ.frontIdx = 0;
    RQ.arr[(RQ.rearIdx + 1) % SIZE] = pid;
    RQ.rearIdx = (RQ.rearIdx + 1) % SIZE;
    return 1;
  }
  if ((RQ.rearIdx + 1)%SIZE == RQ.frontIdx)
    return 0;
  else {
    RQ.arr[(RQ.rearIdx + 1) % SIZE] = pid;
    RQ.rearIdx = (RQ.rearIdx + 1) % SIZE;
    return 1;
  }
}

/**
 * @return will return process PID to be worked on
 */
int popRQ() {
  if (isEmptyRQ()) {
    return -999;
  }
  int pid = RQ.arr[RQ.frontIdx];
  if (RQ.frontIdx == RQ.rearIdx) {
    // only one element
    RQ.frontIdx = RQ.rearIdx = -1;
  } else {
    RQ.frontIdx = (RQ.frontIdx + 1) % SIZE;
  }
  return pid;
}
