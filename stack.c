//
//  stack.c
//  A generic stack class based upon a generic dynamic array
//  with corresponding methods to alter the array
//
//  project0
//
//  Created by Chance Tudor on 9/14/18.
//  Copyright © 2018 Chance Tudor. All rights reserved.
//

typedef void (*FM)(void * ptr); // typedef declaration to store a freeMethod function pointer in stack struct
typedef void (*DM)(void * ptr, FILE *fp); // typedef declaration to store a displayMethod function pointer in stack struct

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"
#include "da.h"

struct stack {
  void * (*storage);
  int capacity;
  int size;
  int debugVal;
  FM freeMethod;
  DM displayMethod;
}

extern STACK * newStack(void) {
  STACK * stack = malloc(sizeof(STACK));
  assert(stack != 0);
  stack->capacity = 1;
  stack->storage = newDA();
  assert(stack->storage != 0);
  stack->size = 0;
  stack->debugVal = 0;
  stack->freeMethod = 0;
  stack->displayMethod = 0;

  return stack;
}

extern void setSTACKdisplay(STACK *items, void (*displayMeth)(void * ptr, FILE *fp)) {
  items->displayMethod = displayMeth;
}

extern void setSTACKfree(STACK * items, void (*freeMeth)(void * ptr)) {
  items->freeMethod = freeMeth;
}

// The push method runs in constant or amortized constant time
// The value to be pushed is stored in the underlying data structure
extern void push(STACK *items, void *value) {
  insertDA(items, 0, value);
}

// The pop method runs in constant or amortized constant time
// The value to be popped is removed in the underlying data structure.
extern void *pop(STACK *items) {
  void * temp = removeDA(items, 0);
  return temp;
}

// The peek method returns the value ready to come off the stack, but leaves the stack unchanged
extern void *peekSTACK(STACK *items) {
  void * temp = getDA(items, 0);
  return temp;
}

// prints the items stored in the stack
// An empty stack displays as ||
extern void displaySTACK(STACK *items, FILE *fp);

// If the debug method is set to 0, the display method uses STACK display
// if the debug level is set to one, the display method uses the underlying data structure's display method
// If the debug method is set to two, the display method uses the underlying data structure's debugged display method
extern int debugSTACK(STACK *items, int level);


extern void freeSTACK(STACK *items) {
  if (items->freeMethod != 0) { // individual items are only freed if a freeMethod is set
    for (int i = 0; i < sizeSTACK(items); i++) { items->freeMethod(items->storage[i]); }
  }
  free(items->storage);
  free(items);
}

// returns the number of items stored in the stack
extern int sizeSTACK(STACK *items) { return items->size; }
