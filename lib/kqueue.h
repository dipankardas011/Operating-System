/**
 * 
 * @author Dipankar Das
 * @date dd-mm-yyy
 * @version 0.xx.xx
 * 
 */
#include <stdlib.h>
#include <stdlib.h>
#include <assert.h>
#ifndef BLACKHOLE
#define BLACKHOLE NULL
#endif

typedef enum boolean {
  False,
  True
}bool;

/**
 * Double Circular Linklist
 */
/**
 * TODO: to be filled
 */
struct __LinkList
{
  void                *data_ptr;
  struct __LinkList   *next;
  struct __LinkList   *prev;
};

struct __LinkListHeaders 
{
  struct __LinkList     *front;
  struct __LinkList     *rear;
};
/**
 * TODO: to be filled
 */
// Before operating call this function
struct __LinkListHeaders * initKQueue() 
{
  struct __LinkListHeaders *tempK = 
          (struct __LinkListHeaders *)malloc(sizeof(struct __LinkListHeaders));
  assert(tempK != BLACKHOLE);
  tempK->front = tempK->rear = BLACKHOLE;
  return tempK;
}
bool isEmpty(struct __LinkList *ptr) {
  return (ptr == BLACKHOLE) ? True : False;
}
/**
 * TODO: to be filled
 */
// before forgetting about the pointer
struct __LinkListHeaders * remKQueue(struct __LinkListHeaders* TOPKPTR) 
{
  // using traditional loop for removal
  struct __LinkList *temp = TOPKPTR->front;
  struct __LinkList *freer = BLACKHOLE;
  while (temp != BLACKHOLE) {
    freer = temp;
    temp = temp->next;
    free(freer);
  }
  TOPKPTR->front = TOPKPTR->rear = BLACKHOLE;
  temp = BLACKHOLE;
  freer = BLACKHOLE;
  free(TOPKPTR);
  return BLACKHOLE;
}

/**
 * @param TOPKPTR it takes pointer for the head of the stack
 * @param iData it takes the insert data to be inserted
 * @return 1 means success 0 means failure
 */
struct __LinkListHeaders * __push_front(struct __LinkListHeaders *TOPKPTR, void *iData) 
{
  struct __LinkList *front = (struct __LinkList *)malloc(sizeof(struct __LinkList));
  assert(front);
  front->data_ptr = iData;
  front->prev = BLACKHOLE;
  front->next = BLACKHOLE;

  if (isEmpty(TOPKPTR->front) == True) {
    TOPKPTR->front = TOPKPTR->rear = front;
    return TOPKPTR;
  }

  front->next = TOPKPTR->front;
  TOPKPTR->front->prev = front;
  TOPKPTR->front = front;

  assert(TOPKPTR->front->data_ptr == iData);
  return TOPKPTR;
}


/**
 * TODO: to be filled
 */
struct __LinkListHeaders * __push_rear(struct __LinkListHeaders *TOPKPTR, void *iData) 
{
  struct __LinkList *rear = (struct __LinkList *)malloc(sizeof(struct __LinkList));
  assert(rear);
  rear->data_ptr = iData;
  
  rear->next = BLACKHOLE;
  rear->prev = BLACKHOLE;

  if (isEmpty(TOPKPTR->rear) == True) {
    TOPKPTR->front = TOPKPTR->rear = rear;
    return TOPKPTR;
  }

  TOPKPTR->rear->next = rear;
  rear->prev = TOPKPTR->rear;

  TOPKPTR->rear = rear;

  assert(TOPKPTR->rear->data_ptr == iData);   // intregity check
  return TOPKPTR;
}

/**
 * TODO: to be filled
 */
struct __LinkListHeaders * __pop_front(struct __LinkListHeaders *TOPKPTR) 
{
  if (isEmpty(TOPKPTR->front) == True)
    return TOPKPTR;

  if (TOPKPTR->front == TOPKPTR->rear) {
    free(TOPKPTR->front);

    TOPKPTR->front = TOPKPTR->rear = BLACKHOLE;
    return TOPKPTR;
  }

  struct __LinkList *freer = TOPKPTR->front;
  TOPKPTR->front = TOPKPTR->front->next;
  TOPKPTR->front->prev = BLACKHOLE;

  free(freer);
  return TOPKPTR;
}

/**
 * TODO: to be filled
 */
struct __LinkListHeaders * __pop_rear(struct __LinkListHeaders *TOPKPTR) 
{
  if (isEmpty(TOPKPTR->front) == True)
    return TOPKPTR;

  if (TOPKPTR->front == TOPKPTR->rear) {
    free(TOPKPTR->rear);

    TOPKPTR->front = TOPKPTR->rear = BLACKHOLE;
    return TOPKPTR;
  }

  struct __LinkList *freer = TOPKPTR->rear;
  TOPKPTR->rear = TOPKPTR->rear->prev;
  TOPKPTR->rear->next = BLACKHOLE;

  free(freer);
  return TOPKPTR;
}

/**
 * equalvalent to the peek()
 */
void * __front__cpu__load__(struct __LinkListHeaders *TOPKPTR) 
{
  return (isEmpty(TOPKPTR->front) == True) ? BLACKHOLE : TOPKPTR->front->data_ptr;
}