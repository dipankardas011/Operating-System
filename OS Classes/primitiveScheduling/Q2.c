#include "proc.h"
#include "timer.h"

#ifndef STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#include <stdlib.h>
#endif


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

      int minArr = i;
      for (int j = 0; j < NoOfProcesses; j++) {

        if (Rqueue[j].currState == EMBRYO
            && CLK_CYCLE >= Rqueue[j].arrTime 
            && Rqueue[j].arrTime < Rqueue[minArr].arrTime)

              minArr = j;
      }
      i = minArr;
      Rqueue[i].currState = RUNNABLE;
      Rqueue[i].initStartTime = CLK_CYCLE;
      return;
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
  while (BT > 0) {
    CLK_CYCLE++;
    BT--;
  }
  Rqueue[idx].burstTime = 0;
  if (BT == 0) {
    Rqueue[idx].finalEndTime = CLK_CYCLE;
    Rqueue[idx].currState = TERMINATED;
    printf("COMPLETED!!\tpid: %d\tCLK: %ld\n", Rqueue[idx].pid, CLK_CYCLE);
  }
  // record the Complition time for a process
}

// returns the index for that process to run
void proc() {
  while (1) {
    // check if all have done
    if (isAllDone() == 1)
      return;

    int i;

    for (i = 0; i < NoOfProcesses; i++) {
      if (Rqueue[i].currState == RUNNABLE) {

        // find the minBT process
        int minBT = i;
        for (int j = 0; j < NoOfProcesses; j++) {
          if (Rqueue[j].currState == RUNNABLE && 
                Rqueue[minBT].arrTime > Rqueue[j].arrTime)
              minBT = j;
        }

        i = minBT;
        __CPU_SCHED(i);

        break;
      }
      
    }
    if (i == NoOfProcesses) {
      // no process was found
      CLK_CYCLE++;
    }
    // when a process gets completed the scheduler is called
    sched();
  }
}

void ReportDis() {
  int totalBT = 0;
  for (int i = 0; i < NoOfProcesses; i++)
  {
    int TT = Rqueue[i].finalEndTime - Rqueue[i].arrTime;
    int RT = Rqueue[i].initStartTime - Rqueue[i].arrTime;
    int WT = TT - tempStoreBT[i];
    printf("Process\tPID: %d\tBT: %d\tAT: %d\tTT: %d\tWT: %d\tRT: %d\n",
           Rqueue[i].pid, tempStoreBT[i], Rqueue[i].arrTime, TT, WT, RT);
    totalBT += tempStoreBT[i];
  }
  printf("TOTAL TIME: %ld\n", CLK_CYCLE);
  size_t idleTime = CLK_CYCLE - totalBT;
  printf("TOTAL IDLE Time: %ld\n", idleTime);
  printf("CPU UTIT: %d\tCPU UTIL PER: %f\n", totalBT, (float)(totalBT) / (CLK_CYCLE));
}

int main() {
  CLK_CYCLE = 0;
  printf("Enter number of processes");
  scanf("%d", &NoOfProcesses);
  Rqueue = (struct proc *)malloc(sizeof(struct proc) * NoOfProcesses);
  tempStoreBT = (int *)malloc(sizeof(int) * NoOfProcesses);
  enterData();
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