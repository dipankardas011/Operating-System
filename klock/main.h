
#include "../lib/kqueue.h"

typedef struct Locking {
  int value;
  struct __LinkListHeaders *waitingQue;
}sem_t;

void sem_init(sem_t *lock, int mutexValue) {
  lock->value = mutexValue;
  lock->waitingQue = initKQueue();
}

void sem_lock(sem_t *lock) {
  (lock->value)--;
  if (lock->value < 0) {
    // waiting queue
    // sleep the process
  }
}

void sem_release(sem_t *lock) {
  (lock->value)++;
  if (lock->value <= 0) {
    // pop_front
    // wakeup the process
  }
}