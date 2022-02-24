#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex;
#define N 100000
int counter;

void *func(void *x)
{
  for (int i = 0; i < N; i++)
  {
    sem_wait(&mutex);
    counter++;
    sem_post(&mutex);
  }
  pthread_exit(0);
}

int main()
{
  counter = 0;
  sem_init(&mutex, 0, 1);

  printf("Hello world\n");
  pthread_t z0, z1, z2;

  pthread_create(&z0, NULL, func, NULL);
  pthread_create(&z1, NULL, func, NULL);
  pthread_create(&z2, NULL, func, NULL);

  pthread_join(z0, NULL);
  pthread_join(z1, NULL);
  pthread_join(z2, NULL);

  // func(NULL);
  printf("counter: %d\n", counter);
  return 0;
}