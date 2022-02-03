#include <stdlib.h>
#include <stdlib.h>
#include <assert.h>

#define EMPTY NULL    // for readable purpose

/**
 * For the header
 */
struct __Stack{
  void          *data_ptr;
  struct __Stack  *next;
};

struct __StackHeaders {
  struct __Stack *topPtr;
};

// Before operating call this function
struct __StackHeaders *initKStack() {
  struct __StackHeaders *tempK = 
          (struct __StackHeaders *)malloc(sizeof(struct __StackHeaders));
  assert(tempK != EMPTY);
  tempK->topPtr = EMPTY;
  return tempK;
}

// before forgetting about the pointer
struct __StackHeaders *remKStack(struct __StackHeaders* TOPKPTR) {
  // using traditional loop for removal
  struct __Stack *temp = TOPKPTR->topPtr;
  struct __Stack *freer = EMPTY;
  while (temp != EMPTY) {
    freer = temp;
    temp = temp->next;
    free(freer);
  }
  TOPKPTR->topPtr = EMPTY;
  temp = EMPTY;
  freer = EMPTY;
  free(TOPKPTR);
  return EMPTY;
}

/**
 * @param TOPKPTR it takes pointer for the head of the stack
 * @param iData it takes the insert data to be inserted
 * @return 1 means success 0 means failure
 */
int __push_top(struct __StackHeaders **TOPKPTR, void *iData) {
  struct __Stack *front = (struct __Stack *)malloc(sizeof(struct __Stack));
  assert(front);
  front->data_ptr = iData;
  // front->next = EMPTY;
  front->next = (*TOPKPTR)->topPtr;
  (*TOPKPTR)->topPtr = front;

  assert((*TOPKPTR)->topPtr->data_ptr == iData);
  return 1;
}

void * __pop_top(struct __StackHeaders **TOPKPTR) {

  if ((*TOPKPTR)->topPtr == EMPTY) {
    return EMPTY;
  }

  struct __Stack *freer = (*TOPKPTR)->topPtr;
  (*TOPKPTR)->topPtr = (*TOPKPTR)->topPtr->next;

  void *ret = freer->data_ptr;
  free(freer);
  return ret;
}

inline void * __peek_top(struct __StackHeaders **TOPKPTR) {

  if ((*TOPKPTR)->topPtr == EMPTY) {
    return EMPTY;
  }

  return ((*TOPKPTR)->topPtr->data_ptr);
}