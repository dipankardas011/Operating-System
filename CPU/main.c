#include "../Memory/VirtualMemo/proc.h"
#include "scheduler.c"
// #include "syscall.c"
#include <string.h>
u_int64_t CLOCK_TIME = 0;

#define SCH_DULE 30
#define INT_RUPT 31

#define PS(processTT)                                                       \
    printf("PID  Name  State  Arri_Time  CPU_TIME1  IO_TIME  CPU_TIME2\n"); \
    for (size_t i = 0; i < NO_PROCESSES; i++)                               \
        printOutProcessDetails(processTT[i]);                               \
    printf("--------\n");

#define READYQUEPS(readyQueueTT)    \
    printf("~~~~~~~~\n");           \
    currStateOfQueue(readyQueueTT); \
    printf("~~~~~~~~\n");

/**
 * @param 1 is the process table containes all the process list which is precomputed
 * @param 2 represents the readyQueue
 */
// int (*__cpu__can__call__[])(struct proc ***, struct readyQueue **, int) = {
//     [SCH_DULE] schedulerRoundRobin};

/**
 * @return NULL when no process has to be added to the ready queue(means its done)
 * otherwise the process which has to be added will be returned
 */
struct proc *__CPU__EXECUTION__AREA__(struct readyQueue **readyQueueRAM,
                                      int *whichQueue,
                                      struct IOQueue **bufferQueue)
{
    int decision = __which_Queue_cpu_will_access(*readyQueueRAM);
    struct proc *processToRun = BLACKHOLE;
    *whichQueue = decision;

    switch (decision)
    {
    case 1:
    {
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q1);
        (*readyQueueRAM)->Q1 = __pop_front((*readyQueueRAM)->Q1);

        processToRun->state = RUNNING;
        u_int64_t startTime = CLOCK_TIME;

        int qt1 = (*readyQueueRAM)->Qt1;

        if (processToRun->burstTime1 > 0)
        {
            while (qt1 > 0 && processToRun->burstTime1 > 0)
            {
                qt1--;
                (processToRun->burstTime1)--;

                /**
                 * @def refresh IOBuffer in same clock cycle 
                 * assuming it is not processed by the processor
                 */
                // ___dis__queue((*bufferQueue)->BUFFER_QUEUE);
                *bufferQueue = refresh(*bufferQueue);
                // ___dis__queue((*bufferQueue)->BUFFER_QUEUE);

                CLOCK_TIME++;
                printf("\n[[[[[ CLK TICK [%ld] ]]]]]\n", CLOCK_TIME);
            }
            printf("~~PROCESS+| %s [%ld - %ld] |+\n", processToRun->name, startTime, CLOCK_TIME);
            if (processToRun->burstTime1 > 0 && qt1 == 0)
            {
                // reinsert it in second Queue
                // as it has crossed its usage time in most pri queue
                // just for now place the removed queue to the same qeue which is here Q1
                // (*readyQueueRAM)->Q2 = __push_rear((*readyQueueRAM)->Q2, processToRun);
                processToRun->state = RUNNABLE;
            }
            if (processToRun->burstTime1 == 0 && qt1 >= 0)
            {
                processToRun->state = WAITING;
                if (processToRun->IOTime == 0)
                    processToRun->state = RUNNABLE;
                /**
                 * IMP: processToRun will send NULL only when all the Activity is done
                 */
            }
        }
        else if (processToRun->IOTime == 0)
        {
            while (qt1 > 0 && processToRun->burstTime2 > 0)
            {
                qt1--;
                (processToRun->burstTime2)--;

                // refresh IOBUffer in same clock cycle assuming it is not processed by the processor
                // ___dis__queue((*bufferQueue)->BUFFER_QUEUE);
                *bufferQueue = refresh(*bufferQueue);
                // ___dis__queue((*bufferQueue)->BUFFER_QUEUE);

                CLOCK_TIME++;
                printf("\n[[[[[ CLK TICK [%ld] ]]]]]\n", CLOCK_TIME);
            }
            printf("~~PROCESS+| %s [%ld - %ld] |+\n", processToRun->name, startTime, CLOCK_TIME);
            if (processToRun->burstTime2 > 0 && qt1 == 0)
            {
                // reinsert it in second Queue
                // as it has crossed its usage time in most pri queue
                // just for now place the removed queue to the same qeue which is here Q1
                // (*readyQueueRAM)->Q2 = __push_rear((*readyQueueRAM)->Q2, processToRun);
                processToRun->state = RUNNABLE;
            }
            if (processToRun->burstTime2 == 0 && qt1 >= 0)
            {
                // free the memory allocated
                // ig the free is having som problems
                processToRun->state = DIED;
                // processToRun->state = WAITING;
                processToRun = BLACKHOLE;
            }
        }
    }
    break;
    case 2:
    {
        /**
         * TODO: write the Queue2
         */
        CLOCK_TIME++;
        printf("\n[[[[[ CLK TICK [%ld] ]]]]]\n", CLOCK_TIME);
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q2);
        (*readyQueueRAM)->Q2 = __pop_front((*readyQueueRAM)->Q2);
    }
    break;
    case 3:
    {
        /**
         * TODO: write the Queue3
         */
        CLOCK_TIME++;
        printf("\n[[[[[ CLK TICK [%ld] ]]]]]\n", CLOCK_TIME);
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q3);
        (*readyQueueRAM)->Q3 = __pop_front((*readyQueueRAM)->Q3);
    }
    break;
    default:
        /**
         * STATUS: DONE
         */
        CLOCK_TIME++;
        *bufferQueue = refresh(*bufferQueue);
        printf("\n[[[[[ CLK TICK [%ld] ]]]]]\n", CLOCK_TIME);
        fprintf(stderr, "UNMANAGEABLE EXCEPTION!!!!!");
    }
    return processToRun;
}

/**
 * TODO: Do the same changes and add description
 */
struct proc *__CPU__EXECUTION__AREA_NONDD__(struct readyQueue **readyQueueRAM,
                                            int *whichQueue,
                                            struct IOQueue **bufferQueue)
{
    int decision = __which_Queue_cpu_will_access(*readyQueueRAM);
    struct proc *processToRun = BLACKHOLE;
    *whichQueue = decision;

    switch (decision)
    {
    case 1:
    {
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q1);
        (*readyQueueRAM)->Q1 = __pop_front((*readyQueueRAM)->Q1);

        processToRun->state = RUNNING;
        u_int64_t startTime = CLOCK_TIME;

        int qt1 = (*readyQueueRAM)->Qt1;

        if (processToRun->burstTime1 > 0)
        {
            // first phase is not completed
            while (qt1 > 0 && processToRun->burstTime1 > 0)
            {
                qt1--;
                (processToRun->burstTime1)--;

                // refresh IOBUffer in same clock cycle assuming it is not processed by the processor
                *bufferQueue = refresh(*bufferQueue);

                CLOCK_TIME++;
            }
            printf("~~PROCESS+| %s [%ld - %ld] |+\n", processToRun->name, startTime, CLOCK_TIME);
            if (processToRun->burstTime1 > 0 && qt1 == 0)
            {
                processToRun->state = RUNNABLE;
            }
            if (processToRun->burstTime1 == 0 && qt1 >= 0)
            {
                processToRun->state = WAITING;
                if (processToRun->IOTime == 0)
                    processToRun->state = RUNNABLE;
                /**
                 * IMP: processToRun will send NULL only when all the Activity is done
                 */
            }
        }
        else if (processToRun->IOTime == 0)
        {
            // first phase is completed
            while (qt1 > 0 && processToRun->burstTime2 > 0)
            {
                qt1--;
                (processToRun->burstTime2)--;

                // refresh IOBUffer in same clock cycle assuming it is not processed by the processor
                // ___dis__queue((*bufferQueue)->BUFFER_QUEUE);
                *bufferQueue = refresh(*bufferQueue);
                // ___dis__queue((*bufferQueue)->BUFFER_QUEUE);

                CLOCK_TIME++;
            }
            printf("~~PROCESS+| %s [%ld - %ld] |+\n", processToRun->name, startTime, CLOCK_TIME);
            if (processToRun->burstTime2 > 0 && qt1 == 0)
            {
                // reinsert it in second Queue
                // as it has crossed its usage time in most pri queue
                // just for now place the removed queue to the same qeue which is here Q1
                // (*readyQueueRAM)->Q2 = __push_rear((*readyQueueRAM)->Q2, processToRun);
                processToRun->state = RUNNABLE;
            }
            if (processToRun->burstTime2 == 0 && qt1 >= 0)
            {
                // free the memory allocated
                // ig the free is having som problems
                processToRun->state = DIED;
                processToRun = BLACKHOLE;
            }
        }
    }
    break;
    case 2:
    {
        CLOCK_TIME++;
        printf("\n[[[[[ CLK TICK [%ld] ]]]]]\n", CLOCK_TIME);
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q2);
        (*readyQueueRAM)->Q2 = __pop_front((*readyQueueRAM)->Q2);
    }
    break;
    case 3:
    {
        CLOCK_TIME++;
        processToRun = (struct proc *)__front__cpu__load__((*readyQueueRAM)->Q3);
        (*readyQueueRAM)->Q3 = __pop_front((*readyQueueRAM)->Q3);
    }
    break;
    default:
        CLOCK_TIME++;
        *bufferQueue = refresh(*bufferQueue);
        fprintf(stderr, "UNMANAGEABLE EXCEPTION!!!!!");
    }
    return processToRun;
}

/**
 * REQUIREMENT: as the user's dat provided is not sorted according 
 * to the arrival time of each process.
 * 
 * COMPLEXITY: O(N^2) BUBBLE SORT as the NO_PROCESSES are < 10 so its *GOOD*
 */
void sortIt(struct proc ***arrayOfProcAssigned)
{
    for (int i = 0; i < NO_PROCESSES; i++)
    {
        for (int j = 0; j < NO_PROCESSES - i - 1; j++)
        {
            if ((*arrayOfProcAssigned)[j]->arrivalTime > (*arrayOfProcAssigned)[j + 1]->arrivalTime)
            {
                struct proc *T = (struct proc *)malloc(sizeof(struct proc));
                T->arrivalTime = (*arrayOfProcAssigned)[j]->arrivalTime;
                T->state = (*arrayOfProcAssigned)[j]->state;
                T->PID = (*arrayOfProcAssigned)[j]->PID;
                T->parent = (*arrayOfProcAssigned)[j]->parent;
                T->burstTime1 = (*arrayOfProcAssigned)[j]->burstTime1;
                T->burstTime2 = (*arrayOfProcAssigned)[j]->burstTime2;
                T->IOTime = (*arrayOfProcAssigned)[j]->IOTime;
                strcpy(T->name, (*arrayOfProcAssigned)[j]->name);
                (*arrayOfProcAssigned)[j]->arrivalTime = (*arrayOfProcAssigned)[j + 1]->arrivalTime;
                (*arrayOfProcAssigned)[j]->state = (*arrayOfProcAssigned)[j + 1]->state;
                (*arrayOfProcAssigned)[j]->PID = (*arrayOfProcAssigned)[j + 1]->PID;
                (*arrayOfProcAssigned)[j]->parent = (*arrayOfProcAssigned)[j + 1]->parent;
                (*arrayOfProcAssigned)[j]->burstTime1 = (*arrayOfProcAssigned)[j + 1]->burstTime1;
                (*arrayOfProcAssigned)[j]->burstTime2 = (*arrayOfProcAssigned)[j + 1]->burstTime2;
                (*arrayOfProcAssigned)[j]->IOTime = (*arrayOfProcAssigned)[j + 1]->IOTime;
                strcpy((*arrayOfProcAssigned)[j]->name, (*arrayOfProcAssigned)[j + 1]->name);
                (*arrayOfProcAssigned)[j + 1]->arrivalTime = T->arrivalTime;
                (*arrayOfProcAssigned)[j + 1]->state = T->state;
                (*arrayOfProcAssigned)[j + 1]->PID = T->PID;
                (*arrayOfProcAssigned)[j + 1]->parent = T->parent;
                (*arrayOfProcAssigned)[j + 1]->burstTime1 = T->burstTime1;
                (*arrayOfProcAssigned)[j + 1]->burstTime2 = T->burstTime2;
                (*arrayOfProcAssigned)[j + 1]->IOTime = T->IOTime;
                strcpy((*arrayOfProcAssigned)[j + 1]->name, T->name);
                free(T);
            }
        }
    }
}

int SmainDebug()
{
    printf("\t\t\t\t{{{{ Devlopment mode }}}}\n\n");
    struct proc **processTT = BLACKHOLE;
    struct readyQueue *readyQueueTT = BLACKHOLE;
    struct IOQueue *ioBuffer = BLACKHOLE;
    initReadyQueue(&readyQueueTT);
    initializeIOQueue(&ioBuffer);
    turnONQueue(&processTT);
    buildProcessTable(&processTT);

    sortIt(&processTT);

    PS(processTT)

    schedulerRoundRobin(&processTT, &readyQueueTT, 1);
    while (True)
    {
        if (__ALL__DONE__(readyQueueTT) == True && _ALL_Processes_are_in_readyQueue(&processTT) == True)
        {
            break;
        }
        int whichQueue = 0;
        struct proc *callBack = __CPU__EXECUTION__AREA__(&readyQueueTT, &whichQueue, &ioBuffer);
        PS(processTT)

        if (callBack == BLACKHOLE)
        {
            // that particular process has completed no need to add at the end
            schedulerRoundRobin(&processTT, &readyQueueTT, 1);
            continue;
        }
        else if (callBack->state == WAITING)
        {
            // add it to the IOBUFFER
            ioBuffer->BUFFER_QUEUE = __push_rear(ioBuffer->BUFFER_QUEUE, callBack);
            schedulerRoundRobin(&processTT, &readyQueueTT, 1);
            continue;
        }

        schedulerRoundRobin(&processTT, &readyQueueTT, 1);

        // now insert the poped process which is incomplete
        int ret = schedulerRoundRobinSCH(callBack, &readyQueueTT, whichQueue);
        if (ret == UNDEFINED)
            return UNDEFINED;

        // READYQUEPS(readyQueueTT)
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int SmainRun()
{
    printf("\t\t\t\t{{{{ Runner mode }}}}\n\n");
    struct proc **processTT = BLACKHOLE;
    struct readyQueue *readyQueueTT = BLACKHOLE;
    struct IOQueue *ioBuffer = BLACKHOLE;
    initReadyQueue(&readyQueueTT);
    initializeIOQueue(&ioBuffer);
    turnONQueue(&processTT);
    buildProcessTable(&processTT);

    sortIt(&processTT);

    PS(processTT)

    schedulerRoundRobin(&processTT, &readyQueueTT, 0);
    while (True)
    {
        // READYQUEPS(readyQueueTT)
        // if all the queues are empty then stop the computer/shutdown
        /**
         * TODO: Added the check for the whether the IOBUFFER IS empty or not
         * * ig it is DONE
         * a case can be that ready queue is over and all the processes are inside the buffer
         */
        if (__ALL__DONE__(readyQueueTT) == True && _ALL_Processes_are_in_readyQueue(&processTT) == True)
        {
            break;
        }
        int whichQueue = 0;
        struct proc *callBack = __CPU__EXECUTION__AREA__(&readyQueueTT, &whichQueue, &ioBuffer);
        // PS(processTT)

        if (callBack == BLACKHOLE)
        {
            // that particular process has completed no need to add at the end
            schedulerRoundRobin(&processTT, &readyQueueTT, 0);
            continue;
        }
        else if (callBack->state == WAITING)
        {
            // add it to the IOBUFFER
            ioBuffer->BUFFER_QUEUE = __push_rear(ioBuffer->BUFFER_QUEUE, callBack);
            schedulerRoundRobin(&processTT, &readyQueueTT, 0);
            continue;
        }

        schedulerRoundRobin(&processTT, &readyQueueTT, 0);

        // now insert the poped process which is incomplete
        int ret = schedulerRoundRobinSCH(callBack, &readyQueueTT, whichQueue);
        if (ret == UNDEFINED)
            return UNDEFINED;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int SMain(int param)
{
    // this will call which main function
    int ret = 0;
    if (param == 1)
    {
        ret = SmainDebug();
    }
    else if (param == 2)
    {
        ret = SmainRun();
    }
    else
    {
        return EXIT_FAILURE;
    }
    return ret;
}