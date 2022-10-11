#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "sem.h"
#include <unistd.h>
#define n  printf("\n");

void *buffer;
typedef struct SEM *SEM;
SEM SEM_create();
void barrier(SEM SEM);
void pack(char *msg, void *buffer, int get);
void SEM_destroy(SEM SEM);
void *function(void *arg);

struct SEM {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  int count;
};

int main() {

  buffer = malloc(8);
  pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
  SEM sem;
  sem = SEM_create();
  
  pthread_create(&t1, NULL, function, sem);
  pthread_create(&t2, NULL, function, sem);
  pthread_create(&t3, NULL, function, sem);
  pthread_create(&t4, NULL, function, sem);
  pthread_create(&t5, NULL, function, sem);
  pthread_create(&t6, NULL, function, sem);
  pthread_create(&t7, NULL, function, sem);
  pthread_create(&t8, NULL, function, sem);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  pthread_join(t5, NULL);
  pthread_join(t6, NULL);
  pthread_join(t7, NULL);
  pthread_join(t8, NULL);

  sleep(1);
  
  n;
  printf("Important Message: %s\n", msg);
  n;

  SEM_destroy(sem);
  free(sem);//even doing this has no effect!
  n;
  
  if (sem == NULL) {
    puts("the semaphore has been destroyed\n");
  }else {
    puts("oh no!");
  }

  printf("count: %d\n", sem->count);

  free(buffer);
  buffer = NULL;
  
  exit(0);
  
}


SEM SEM_create() {
  SEM sem = calloc(1, sizeof(struct SEM));
  pthread_mutex_init(&sem->mutex, NULL);
  pthread_cond_init(&sem->cond, NULL);
  sem->count = 0;
  return sem;
}

void barrier(SEM SEM) {
  int thread_ID = SEM->count;
  SEM->count++;
  
  if (SEM->count < 8) {
    printf("Thread %d is about to wait\n", thread_ID);
    pthread_cond_wait(&SEM->cond, &SEM->mutex);
  }else {
    n;
    printf("Thread %d is about to broadcast\n", thread_ID);
    n;
    pthread_cond_broadcast(&SEM->cond);
  }

}

void SEM_destroy(SEM SEM) {
  pthread_mutex_destroy(&SEM->mutex);
  pthread_cond_destroy(&SEM->cond);
  free(SEM);
  SEM = NULL;
  if (SEM == NULL) {
    printf("SEM is Null inside destroy\n");
  }
}

void pack(char *msg, void *buffer, int get) {
  *(char *)buffer = msg[get];
}

void *function(void *arg) {
  SEM SEM = arg;
  int thread_ID;
  pthread_mutex_lock(&SEM->mutex);

  thread_ID = SEM->count;
  pack(msg, buffer, SEM->count);

  barrier(SEM);
  
  printf("Thread %d is about to unlock\n", thread_ID);
  
  pthread_mutex_unlock(&SEM->mutex);
    
  return NULL;
}
