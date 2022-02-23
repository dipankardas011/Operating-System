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
void printOutLoudPatQueue(struct __LinkListHeaders *ptr);
struct IOQueue *refresh(struct IOQueue *que) {
  struct __LinkList *iter = que->BUFFER_QUEUE->front;
  /**
   * if the IOTIME of any becomes == 0 then swap the value with the head of the queue for faster access
   */
  while (isEmpty(iter) == False) {

    (((struct proc *)(iter->data_ptr))->IOTime)--;

    if ((((struct proc *)(iter->data_ptr))->IOTime) == 0) {
      void *x = iter->data_ptr;
      ((struct proc *)(iter->data_ptr))->state = READY;
      iter = iter->next;
      /**
       * TODO: insert the poped process from the BUffer to the ready queue
       */
      que->BUFFER_QUEUE = __removeByGivenData(que->BUFFER_QUEUE, x);
      ___dis__queue(que->BUFFER_QUEUE);
    }
    else
    {
      iter = iter->next;
    }
  }
  return que;
}

void initializeIOQueue(struct IOQueue **qq) {
  *qq = (struct IOQueue *)malloc(sizeof(struct IOQueue));
  (*qq)->BUFFER_QUEUE = initKQueue();
}