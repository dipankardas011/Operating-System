/**
 * DONE: 
 * * safe sequence
 * * resource alocation
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int N;
static int noProc;

struct processPool {
  int *max;
  int *need;
  int *allocated;
  bool status;
};
int *available = NULL;

bool isCompatable(int *need, int* avil, int resources) {

  for (int  i = 0; i < resources; i++) {
    if (avil[i] < need[i])
      return false;
  }
  return true;
}

bool safeSequence(struct processPool *ptable, int process, int resources)
{
  bool flag = false;
  bool tempStatus[process];
  for (int i=0; i<process; i++)
    tempStatus[i] = false;
  
  int tempAvailable[resources];
  for (int i=0; i<resources; i++)
    tempAvailable[i] = available[i];
  
  while (1)
  {
    int processIdx = 0;
    flag = false;
    while (processIdx < process)
    {
      if (tempStatus[processIdx] == false && isCompatable(ptable[processIdx].need, tempAvailable, resources)) {
        tempStatus[processIdx] = true;
        flag = true;
        for (int i=0; i<resources; i++)
          tempAvailable[i] += ptable[processIdx].allocated[i];
      }

      processIdx++;
    }
    if (flag == false) {
      for (int i = 0; i < process; i++) {
        if (tempStatus[i] == false)
          return false;
      }
      return true;
    }
  }
}



bool resourceAlloc(struct processPool *ptable, int process, int resources, int* request, int Idxreq) 
{
  for (int i = 0; i < resources; i++) {
    if (request[i] > ptable[Idxreq].need[i] || request[i] > available[i])
      return false;
  }

  if (safeSequence(ptable, process, resources)) {

    for (int i = 0; i < resources; i++) {
      available[i] -= request[i];
      ptable[Idxreq].allocated[i] += request[i];
      ptable[Idxreq].need[i] -= request[i];
    }

    if (safeSequence(ptable, process, resources)) {
      return true;
    }
    
    // revert back
    for (int i = 0; i < resources; i++) {
      available[i] += request[i];
      ptable[Idxreq].allocated[i] -= request[i];
      ptable[Idxreq].need[i] += request[i];
    }
    return false;
    
  }
  
  return false;
  
}



void ps_aux(struct processPool *ptable, int resources, int noProc) 
{
  for (int i = 0; i < noProc; i++) {

    printf("P%d\tSTATUS: %s", i, (ptable[i].status)? "😇" : "☠️");

    printf("\n\t→ Max:");
    for (int j = 0; j < resources; j++)
      printf(" %d", ptable[i].max[j]);
    
    printf("\n\t→ Allocated: ");
    for (int j = 0; j < resources; j++)
      printf(" %d", ptable[i].allocated[j]);
    
    printf("\n\t→ Need: ");
    for (int j = 0; j < resources; j++)
      printf(" %d", ptable[i].need[j]);
    printf("\n");

  }
  printf("Available: { ");
  for (int i = 0; i < resources; i++)
  {
    printf("%d ", available[i]);
  }
  printf("}\n");
}

int main(int argc, char const *argv[])
{
  printf("Enter the number of resources: ");
  scanf("%d", &N);
  printf("Enter the number of processes: ");
  scanf("%d", &noProc);

  struct processPool *proc = (struct processPool*)malloc(sizeof(struct processPool)*noProc);
  available = (int *)malloc(sizeof(int) * N);

  for (int i = 0; i < noProc; i++)
  {
    proc[i].allocated = (int *)malloc(sizeof(int) * N);
    proc[i].max = (int *)malloc(sizeof(int) * N);
    proc[i].need = (int *)malloc(sizeof(int) * N);
    proc[i].status = true;
  }
  printf("Enter the available: ");
  for (int i = 0; i < N; i++)
    scanf("%d", available+i);

  for (int i = 0; i < noProc; i++) {

    printf("Enter the max for P%d: ", i);
    for (int j = 0; j < N; j++)
      scanf("%d", &proc[i].max[j]);
    
    printf("Enter the allocated for P%d: ", i);
    for (int j = 0; j < N; j++) {
      scanf("%d", &proc[i].allocated[j]);
      proc[i].need[j] = proc[i].max[j] - proc[i].allocated[j];
    }
  }

  ps_aux(proc, N, noProc);
  printf("Safe: %s\n", (safeSequence(proc, noProc, N)) ? "✅" : "❌");


  int *request = (int*)malloc(sizeof(int)*N);
  int RR;
  printf("Enter process number [0..N-1]: ");
  scanf("%d", &RR);
  printf("Enter the request values: ");
  for (int i = 0; i < N; i++)
    scanf("%d", request + i);

  (resourceAlloc(proc, noProc, N, request, RR)) ? 
      system("echo \"$(tput setaf 2)$(tput bold)ALLOCATED: $(tput init) Request granted\"") 
      : system("echo \"$(tput setaf 1)$(tput bold)UNALLOCATED: $(tput init) Request is INV\"");

  // ps_aux(proc, N, noProc);

  free(request);
  free(proc);
  free(available);

  remove(argv[0]);
  return 0;
}
