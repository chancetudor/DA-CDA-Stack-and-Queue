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



extern QUEUE *newQUEUE(void);


extern void setQUEUEdisplay(QUEUE *,void (*)(void *,FILE *));


extern void setQUEUEfree(QUEUE *,void (*)(void *));


extern void enqueue(QUEUE *items,void *value);


extern void *dequeue(QUEUE *items);


extern void *peekQUEUE(QUEUE *items);


extern void displayQUEUE(QUEUE *items,FILE *fp);


extern int debugQUEUE(QUEUE *items,int level);


extern void freeQUEUE(QUEUE *items);


extern int sizeQUEUE(QUEUE *items);
