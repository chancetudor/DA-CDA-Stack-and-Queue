//
//  cda.c
//  A generic circular dynamic array class with corresponding methods to alter the array
//  project0
//
//  Created by Chance Tudor on 9/3/18.
//  Copyright © 2018 Chance Tudor. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "cda.h"

typedef void (*FM)(void * ptr); // typedef declaration to store a freeMethod function pointer in DA struct
typedef void (*DM)(void * ptr, FILE *fp); // typedef declaration to store a displayMethod function pointer in DA struct
static int capacityCDA(CDA * items);
static int correctIndex(CDA *items, int oldIndex);
static int getStartCDA(CDA * items);
static int getEndCDA(CDA * items);
static bool isFull(CDA * items);
static void doubleArray(CDA * items);
static void halveArray(CDA * items);

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

// constructor; returns new, initialized CDA object
extern CDA * newCDA(void) {
    CDA * array = malloc(sizeof(CDA));
    assert(array != 0);
    array->capacity = 1;
    array->storage = malloc(sizeof(void *) * array->capacity);
    assert(array->storage != 0);
    array->size = 0;
    array->startIndex = 0;
    array->endIndex = 0;
    array->debugVal = 0;
    array->freeMethod = 0;
    array->displayMethod = 0;

    return array;
}

extern void setCDAdisplay(CDA *items, void (*displayMeth)(void *ptr, FILE *fp)) { items->displayMethod = displayMeth; }

extern void setCDAfree(CDA *items, void (*freeMeth)(void *ptr)) { items->freeMethod = freeMeth; }

static bool isFull(CDA * items) {
  if ( (items->startIndex == 0 && items->endIndex == capacityCDA(items) - 1) || (items->startIndex == items->endIndex + 1)) {
    return true;
  }
  else { return false; }
}

extern void insertCDA(CDA *items, int index, void *value) {
    assert(index >= -1 && index <= sizeCDA(items));
    if (isFull(items) == true) {
      // FIXME: write function that doubles array capacity
    }
    else if (sizeCDA(items) == 0 || index == sizeCDA(items)) { // insert at the back of the CDA
        items->storage[items->endIndex] = value;
        items->endIndex = correctIndex(items, getEndCDA(items) + 1);
        items->size += 1;
    }
    else if (index == -1 || index == 0) { // insert at the front of the CDA
        items->startIndex = correctIndex(items, getStartCDA(items) - 1);
        items->storage[items->startIndex] = value;
        items->size += 1;
    }
    else { // insert in the middle of the CDA
        int decisionPt = sizeCDA(items) / 2; // determines whether array shifts left or right for insertion
        int newIndex = correctIndex(items, index);
        if (newIndex <= decisionPt) {
            void * (*temp) = getCDA(items, newIndex);
            // FIXME: write loop to shift elements left
        }
        else {
          // FIXME: write loop to shift elements right
        }
    }
}

static void doubleArray(CDA * items);

extern void * removeCDA(CDA * items, int index);

static void halveArray(CDA * items);

static int getStartCDA(CDA * items) { return items->startIndex; }

static int getEndCDA(CDA * items) { return items->endIndex; }

extern void *removeCDA(CDA *items, int index);

extern void unionCDA(CDA *recipient, CDA *donor);

static int correctIndex(CDA *items, int oldIndex) {
    int index = (oldIndex + capacityCDA(items)) % capacityCDA(items);
    return index;
}

// method returns the value at the given index
extern void *getCDA(CDA *items, int index) {
    assert(index >= 0 && index < sizeCDA(items));
    int newIndex = correctIndex(items, index + getStartCDA(items));
    return items->storage[newIndex];
}

extern void *setCDA(CDA *items, int index, void *value) {
    assert(index >= -1 && index <= sizeCDA(items));
    int newIndex = correctIndex(items, index); // FIXME: do i have to correctIndex here?
    void * (*val) = getCDA(items, newIndex);
    if (newIndex == sizeCDA(items)) {
        insertCDAback(items, value);
        return val;
    }
    else if (newIndex == -1) {
        insertCDAfront(items, value);
        return val;
    }
    else { items->storage[newIndex] = value; }

    return val;
}

// method returns the size of array
extern int sizeCDA(CDA *items) { return items->size; }

// method returns the capacity of array
static int capacityCDA(CDA * items) { return items->capacity; }

extern void displayCDA(CDA *items, FILE *fp) {
    if ((sizeCDA(items) == 0) && (items->debugVal > 0)) { // empty array and method should display num. empty indeces
        fprintf(fp, "((%d))", items->capacity);
    }
    else if ((sizeCDA(items) == 0) && (items->debugVal == 0)) { // empty array and method should not display num. empty indeces
        fprintf(fp, "()");
    }
    else if ((items->displayMethod == 0) && (items->debugVal > 0)) { // no display method set and method should display num. empty indeces
        fprintf(fp, "(");
        for (int i = 0; i < sizeCDA(items); i++) {
            //FIXME: figure out a way to use getCDA() to print CDA
            fprintf(fp, "@%p,", &items->storage[i]); // no set display method forces addresses of each item to be printed
        }
        fprintf(fp, "(%d))", (capacityCDA(items) - sizeCDA(items)));
    }
    else if ((items->displayMethod == 0) && (items->debugVal == 0)) { // no display method set and method should not display num. empty indeces
        fprintf(fp, "(");
        for (int i = 0; i < sizeCDA(items); i++) {
            //FIXME: figure out a way to use getCDA() to print CDA
            fprintf(fp, "@%p,", &items->storage[i]);
        }
        fprintf(fp, ")");
    }
    else if ((items->displayMethod != 0) && (items->debugVal > 0)) { // display method set and method should display num. empty indeces
        fprintf(fp, "(");
        for (int i = 0; i < sizeCDA(items); i++) {
            //FIXME: figure out a way to use getCDA() to print CDA
            items->displayMethod(items->storage[i], fp);
            if (i != (sizeCDA(items) - 1)) { fprintf(fp, ","); }
        }
        fprintf(fp, "(%d))", (capacityCDA(items) - sizeCDA(items)));
    }
    else if ((items->displayMethod != 0) && (items->debugVal == 0)) { // display method set and method should not display num. empty indeces
        fprintf(fp, "(");
        for (int i = 0; i < sizeCDA(items); i++) {
            //FIXME: figure out a way to use getCDA() to print CDA
            items->displayMethod(items->storage[i], fp);
            if (i != (sizeCDA(items) - 1)) { fprintf(fp, ","); }
        }
        fprintf(fp, ")");
    }
}

extern int debugCDA(CDA *items, int level) {
    int prevVal = items->debugVal;
    items->debugVal = level;

    return prevVal;
}

extern void freeCDA(CDA *items) {
    if (items->freeMethod != 0) { // individual items are only freed if a freeMethod is set
        for (int i = 0; i < sizeCDA(items); i++) { items->freeMethod(getCDA(items, i)); }
    }
    free(items->storage);
    free(items);
}
