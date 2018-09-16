//
//  queue.c
//  A generic queue class based on a generic circular dynamic array class
//  with corresponding methods to alter the array
//
//  project0
//
//  Created by Chance Tudor on 9/15/18.
//  Copyright © 2018 Chance Tudor. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "cda.h"

typedef void (*FM)(void * ptr); // typedef declaration to store a freeMethod function pointer in queue struct
typedef void (*DM)(void * ptr, FILE *fp); // typedef declaration to store a displayMethod function pointer in queue struct

struct cda {
  void * (*storage);
  int capacity;
  int size;
  int startIndex;
  int endIndex;
  int debugVal;
  FM freeMethod;
  DM displayMethod;
};

struct queue {
  CDA * array;
  int debugVal;
  FM freeMethod;
  DM displayMethod;
};

extern QUEUE *newQUEUE(void) {
  QUEUE * queue  malloc(sizeof(QUEUE));
  assert(queue != 0);
  queue->array = newCDA();
  assert(queue->array != 0);
  queue->debugVal = 0;
  queue->freeMethod = 0;
  queue->displayMethod = 0;

  return queue;
}


extern void setQUEUEdisplay(QUEUE *items, void (*displayMeth)(void * ptr, FILE *fp)) {
  items->displayMethod = displayMeth;
}


extern void setQUEUEfree(QUEUE *items, void (*freeMeth)(void *ptr)) {
  items->freeMethod = freeMeth;
}


extern void enqueue(QUEUE *items, void *value);


extern void *dequeue(QUEUE *items);


extern void *peekQUEUE(QUEUE *items);


extern void displayQUEUE(QUEUE *items,FILE *fp);


extern int debugQUEUE(QUEUE *items, int level);


extern void freeQUEUE(QUEUE *items);


extern int sizeQUEUE(QUEUE *items);
