#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#ifndef BALCKHOLE
#define BLACKHOLE NULL
#endif
enum procState
{
  UNUSED,
  EMBRYO,
  SLEEPING,
  RUNNING,
  RUNNABLE,
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
  temp->state = RUNNABLE;
  temp->arrivalTime = 0;

  return temp;
}

void printOutProcessDetails(struct proc *ptr) {
  printf("--------\n");
  printf("PID: %d\n", ptr->PID);
  printf("Name: %s\n", ptr->name);
  printf("arrival time: %d\n", ptr->arrivalTime);
  printf("state: %d\n", ptr->state);
  printf("--------\n");
}