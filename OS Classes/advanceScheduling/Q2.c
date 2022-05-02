#include <stdbool.h>
#include "procRR.h"
#include "timer.h"

#ifndef STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#include <stdlib.h>
#endif

static int Qt = 2; // 3 Qt

int NoOfProcesses;

void enterData() {
  printf("Enter the PID, ArrivialTime & BurstTime for each proc\n");
  int id, bt, at;
  for (int i = 0; i < NoOfProcesses; i++)
  {
    scanf("%d %d %d", &id, &at, &bt);
    Rqueue[i].arrTime = at;
    Rqueue[i].burstTime = bt;
    Rqueue[i].currState = EMBRYO;
    Rqueue[i].pid = id;
    Rqueue[i].initStartTime = Rqueue[i].finalEndTime = 0;
    tempStoreBT[i] = bt;
  }
}

void __PS() {
  printf("PID\tArr\tBurst\n");
  for (int i = 0; i < NoOfProcesses; i++)
    printf("%d\t%d\t%d\n", Rqueue[i].pid, Rqueue[i].arrTime, Rqueue[i].burstTime);
}

void sched() {
  for (int i = 0; i < NoOfProcesses; i++) {
    if (CLK_CYCLE >= Rqueue[i].arrTime 
        && Rqueue[i].currState == EMBRYO) {

      
      Rqueue[i].currState = RUNNABLE;
      int ret = pushRQ(i);
      if (!ret) {
        system("echo \"$(tput setaf 2)$(tput bold)UNKNOWN: $(tput init)Resource leak or INF loop\"");
        while (1){
          printf("1001");
        } // ♾️ loop
      }
    }
  }
}

/**
 * @def in real time OS the process are added as they come
 * be default it comes in inc time order only
 */
void sortAccToArrTime() {
  for (int i = 0; i < NoOfProcesses; i++) {
    for (int j = 0; j < NoOfProcesses - i - 1; j++) {
      if (Rqueue[j].arrTime > Rqueue[j + 1].arrTime) {
        struct proc T;
        int temp;
        T.arrTime       = Rqueue[j].arrTime;
        T.currState     = Rqueue[j].currState;
        T.pid           = Rqueue[j].pid;
        T.initStartTime = Rqueue[j].initStartTime;
        T.finalEndTime  = Rqueue[j].finalEndTime;
        T.burstTime     = Rqueue[j].burstTime;
        temp            = tempStoreBT[j];

        Rqueue[j].arrTime       = Rqueue[j + 1].arrTime;
        Rqueue[j].currState     = Rqueue[j + 1].currState;
        Rqueue[j].pid           = Rqueue[j + 1].pid;
        Rqueue[j].burstTime     = Rqueue[j + 1].burstTime;
        Rqueue[j].initStartTime = Rqueue[j + 1].initStartTime;
        Rqueue[j].finalEndTime  = Rqueue[j + 1].finalEndTime;
        tempStoreBT[j]          = tempStoreBT[j + 1];

        Rqueue[j + 1].arrTime       = T.arrTime;
        Rqueue[j + 1].currState     = T.currState;
        Rqueue[j + 1].pid           = T.pid;
        Rqueue[j + 1].burstTime     = T.burstTime;
        Rqueue[j + 1].initStartTime = T.initStartTime;
        Rqueue[j + 1].finalEndTime  = T.finalEndTime;
        tempStoreBT[j + 1]          = temp;
      }
    }
  }
}

int isAllDone() {
  for (int i = 0; i < NoOfProcesses; i++) {
    if (Rqueue[i].currState != TERMINATED)
      return 0;
  }
  return 1;
}

void __CPU_SCHED(int idx) {
  Rqueue[idx].currState = RUNNING;
  int BT = Rqueue[idx].burstTime;
  // if the process starts its exquition for the first time it saves it
  if (BT == tempStoreBT[idx]) {
    Rqueue[idx].initStartTime = CLK_CYCLE;
  }

  int currJobBT = Qt;
  while (BT > 0 && currJobBT > 0) {
    CLK_CYCLE++;
    BT--;
    currJobBT--;
  }
  Rqueue[idx].burstTime = BT;
  if (BT == 0) {
    Rqueue[idx].finalEndTime = CLK_CYCLE;
    Rqueue[idx].currState = TERMINATED;
    printf("COMPLETED!!\tpid: %d\tCLK: %ld\n", Rqueue[idx].pid, CLK_CYCLE);
    return;
  }
  Rqueue[idx].currState = RUNNABLE;
  // record the Complition time for a process
}

// returns the index for that process to run
void proc() {
  while (1) {
    // check if all have done
    if (isAllDone() == 1)
      return;

    int i;
    i = popRQ();
    if (i == -999) {
      // no process was found
      CLK_CYCLE++;
    } else {
      __CPU_SCHED(i);
    }

    // when a process gets completed the scheduler is called
    sched();
    // reinsertion
    if (i != -999 && Rqueue[i].currState == RUNNABLE) {
      // reinsert else dont reinsert
      pushRQ(i);
    }
  }
}

void ReportDis() {
  int Swt = 0;
  for (int i = 0; i < NoOfProcesses; i++)
  {
    int TT = Rqueue[i].finalEndTime - Rqueue[i].arrTime;
    int RT = Rqueue[i].initStartTime - Rqueue[i].arrTime;
    int WT = TT - tempStoreBT[i];
    Swt += WT;
    printf("Process\tPID: %d\tAT: %d\tBT: %d\tTT: %d\tWT: %d\tRT: %d\n",
           Rqueue[i].pid, Rqueue[i].arrTime, tempStoreBT[i],  TT, WT, RT);
  }
  printf("Avg WT: %f\n", (float)(Swt)/NoOfProcesses);
}

int main() {
  CLK_CYCLE = 0;
  printf("Enter number of processes");
  scanf("%d", &NoOfProcesses);
  if (NoOfProcesses > SIZE) {
    system("echo \"$(tput setaf 1)$(tput bold)ERR: $(tput init)No of processes greater than Ready Queue CAPACITY\"");
    return 1;
  }
  Rqueue = (struct proc *)malloc(sizeof(struct proc) * NoOfProcesses);
  tempStoreBT = (int *)malloc(sizeof(int) * NoOfProcesses);
  initRQ();
  enterData();
  sortAccToArrTime();
  __PS();
  // initial scheduler is called so as to make the process as runnable
  sched();
  proc();

  // all have done display Report
  ReportDis();

  free(Rqueue);
  free(tempStoreBT);
  return 0;
}
