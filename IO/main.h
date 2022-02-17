// this is for the Swap in Swap out
// I/O Buffer
/**
 * ready queue  ---> CPU (here when the process CPU burst is completed then added to the 
 * I/O buffer queue) 
 * then for every CLK tick the I/O is also refreshed assuming that the refreshment is 
 * not precessed by the CPU i.e. it not treated as a JOb for cpu
 * and if any one process comes out to be I/O burst be 0 then pop from the i/O buffer and add to the 
 * ready queue assuming that memory is available i.e. ready queue has enough size to 
 * accomodate +1 process
 */

struct IOQueue {
  struct __LinkListHeaders *BUFFER_QUEUE;
};

void refresh(struct IOQueue **que) {
  struct __LinkList *iter = (*que)->BUFFER_QUEUE->front;
  while (isEmpty(iter) == False) {
    
    if (((struct proc*)(iter->data_ptr))->IOTime > 0) {
      (((struct proc *)(iter->data_ptr))->IOTime)--;
    }
    /**
     * TODO: what if the IOTIME <= 0
     */

    iter = iter->next;
  }
}

void initializeIOQueue(struct IOQueue **qq) {
  *qq = (struct IOQueue *)malloc(sizeof(struct IOQueue));
  (*qq)->BUFFER_QUEUE = initKQueue();
}