#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#ifndef BALCKHOLE
#define BLACKHOLE NULL
#endif
enum procState
{
  WAITING,
  EMBRYO,
  SLEEPING,
  RUNNING,
  RUNNABLE,
  DIED,
  ZOMBIE
};

struct context
{
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

/**
 * As it is simple system the process synchronization is not applyed
 */
struct proc
{
  // uint sz;                        // size of process memory(bytes)
  enum procState state; // state of it
  int PID;              // process ID
  struct proc *parent;  // parent Address
  // struct context *contextSwitch;  // contextSwitch
  char name[16]; // process name
  // struct scheduling sched;
  // struct niceness ni;
  uint arrivalTime;
  uint burstTime1;
  uint burstTime2;
  uint IOTime;
};

struct proc *initProcess(char *name, int id)
{
  struct proc *temp = (struct proc *)malloc(sizeof(struct proc));
  assert(temp);

  for (size_t i = 0; i < 15 && name[i]; i++)
  {
    temp->name[i] = name[i];
  }
  temp->parent = BLACKHOLE;
  temp->PID = id;
  // temp->state = RUNNABLE;
  temp->state = EMBRYO;
  temp->arrivalTime = 0;
  temp->burstTime1 = 0;
  temp->IOTime = 0;
  temp->burstTime2 = 0;

  return temp;
}

char whatIsState(enum procState x) {
  switch(x) {
    case RUNNABLE:
      return 'r';
    case RUNNING:
      return 'R';
    case SLEEPING:
      return 'S';
    case EMBRYO:
      return 'E';
    case WAITING:
      return 'W';
    case DIED:
      return 'T';
    case ZOMBIE:
      return 'Z';
  }
  return '!';
}

void printOutProcessDetails(struct proc *ptr) {
  printf("%d  %5s  %5c  %5d  %5d  %5d  %5d\n", ptr->PID, ptr->name, whatIsState(ptr->state), ptr->arrivalTime, ptr->burstTime1, ptr->IOTime, ptr->burstTime2);
}