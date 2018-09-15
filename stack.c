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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"
#include "da.h"

typedef void (*FM)(void * ptr); // typedef declaration to store a freeMethod function pointer in stack struct
typedef void (*DM)(void * ptr, FILE *fp); // typedef declaration to store a displayMethod function pointer in stack struct

struct da {
  void * (*storage);
  int capacity;
  int size;
  int debugVal;
  FM freeMethod;
  DM displayMethod;
};

struct stack {
  DA * array;
  int debugVal;
  FM freeMethod;
  DM displayMethod;
};

extern STACK * newSTACK(void) {
  STACK * stack = malloc(sizeof(STACK));
  assert(stack != 0);
  stack->array = newDA();
  assert(stack->array != 0);
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
  insertDA(items->array, 0, value);
}

// The pop method runs in constant or amortized constant time
// The value to be popped is removed in the underlying data structure.
extern void *pop(STACK *items) {
  void * temp = removeDA(items->array, 0);
  return temp;
}

// returns value ready to come off the stack, but leaves stack unchanged
extern void *peekSTACK(STACK *items) {
  void * temp = getDA(items->array, 0);
  return temp;
}

// prints the items stored in the stack
// An empty stack displays as ||
extern void displaySTACK(STACK *items, FILE *fp) {
  if (items->debugVal == 0) {
    fprintf(fp, "|");
    for (int i = 0; i < sizeSTACK(items); i++) {
      items->displayMethod(getDA(items->array, i), fp);
      if (i != (sizeSTACK(items) - 1)) { fprintf(fp, ","); }
    }
    fprintf(fp, "|");
  }

  else if (items->debugVal == 1) {
    debugDA(items->array, 0);
    displayDA(items->array, fp);
  }
  else {
    debugDA(items->array, 1);
    displayDA(items->array, fp);
  }
}

// If the debug level == 0, display method uses STACK display
// if debug level == one, display method uses underlying data structure's display method
// If debug level == two, display method uses underlying data structure's debugged display method
extern int debugSTACK(STACK *items, int level) {
  int prevVal = items->debugVal;
  items->debugVal = level;

  return prevVal;
}


extern void freeSTACK(STACK *items) {
  if (items->freeMethod != 0) { // individual items are only freed if a freeMethod is set
    for (int i = 0; i < sizeSTACK(items); i++) { items->freeMethod(items->array->storage[i]); }
  }
  free(items->array);
  free(items);
}

// returns the number of items stored in the stack
extern int sizeSTACK(STACK *items) { return sizeDA(items->array); }
