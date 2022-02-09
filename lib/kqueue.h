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

#define BLACKHOLE NULL

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
struct __LinkListHeaders *
initKStack() 
{
  struct __LinkListHeaders *tempK = 
          (struct __LinkListHeaders *)malloc(sizeof(struct __LinkListHeaders));
  assert(tempK != BLACKHOLE);
  tempK->front = tempK->rear = BLACKHOLE;
  return tempK;
}

/**
 * TODO: to be filled
 */
// before forgetting about the pointer
struct __LinkListHeaders *
remKStack(struct __LinkListHeaders* TOPKPTR) 
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
int 
__push_front(struct __LinkListHeaders **TOPKPTR, void *iData) 
{
  struct __LinkList *front = (struct __LinkList *)malloc(sizeof(struct __LinkList));
  assert(front);
  front->data_ptr = iData;
  front->prev = BLACKHOLE;

  front->next = (*TOPKPTR)->front;
  (*TOPKPTR)->front->prev = front;
  (*TOPKPTR)->front = front;

  assert((*TOPKPTR)->front->data_ptr == iData);
  return 1;
}


/**
 * TODO: to be filled
 */
int 
__push_rear(struct __LinkListHeaders **TOPKPTR, void *iData) 
{
  struct __LinkList *rear = (struct __LinkList *)malloc(sizeof(struct __LinkList));
  assert(rear);
  rear->data_ptr = iData;
  
  rear->next = BLACKHOLE;
  (*TOPKPTR)->rear->next = rear;
  rear->prev = (*TOPKPTR)->rear;

  (*TOPKPTR)->rear = rear;

  assert((*TOPKPTR)->rear->data_ptr == iData);   // intregity check
  return 1;
}

/**
 * TODO: to be filled
 */
void * 
__pop_front(struct __LinkListHeaders **TOPKPTR) 
{
  if ((*TOPKPTR)->front == BLACKHOLE)
    return BLACKHOLE;

  if ((*TOPKPTR)->front == (*TOPKPTR)->rear) {
    void *ret = (*TOPKPTR)->front->data_ptr;
    free((*TOPKPTR)->front);

    (*TOPKPTR)->front = (*TOPKPTR)->rear = BLACKHOLE;
    return ret;
  }

  struct __LinkList *freer = (*TOPKPTR)->front;
  (*TOPKPTR)->front = (*TOPKPTR)->front->next;
  (*TOPKPTR)->front->prev = BLACKHOLE;

  void *ret = freer->data_ptr;
  free(freer);
  return ret;
}

/**
 * TODO: to be filled
 */
void * 
__pop_rear(struct __LinkListHeaders **TOPKPTR) 
{

  if ((*TOPKPTR)->rear == BLACKHOLE)
    return BLACKHOLE;

  if ((*TOPKPTR)->front == (*TOPKPTR)->rear) {
    void *ret = (*TOPKPTR)->rear->data_ptr;
    free((*TOPKPTR)->rear);

    (*TOPKPTR)->front = (*TOPKPTR)->rear = BLACKHOLE;
    
    return ret;
  }

  struct __LinkList *freer = (*TOPKPTR)->rear;
  (*TOPKPTR)->rear = (*TOPKPTR)->rear->prev;
  (*TOPKPTR)->rear->next = BLACKHOLE;

  void *ret = freer->data_ptr;
  free(freer);
  return ret;
}