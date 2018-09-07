//
//  da.c
//  A dynamic, generic array class with corresponding methods to alter the array
//  project0
//
//  Created by Chance Tudor on 8/30/18.
//  Copyright © 2018 Chance Tudor. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "da.h"

static DA * doubleArray(DA * items);
static DA * halveArray(DA * items);
static int capacityDA(DA * items);
typedef void (*FM)(void * ptr); // typedef declaration to store a freeMethod function pointer in DA struct
typedef void (*DM)(void * ptr, FILE *fp); // typedef declaration to store a displayMethod function pointer in DA struct

struct da {
    void * (*storage);
    int capacity;
    int size;
    int index;
    int debugVal;
    FM freeMethod;
    DM displayMethod;
};

// constructor; returns new, initialized dynamic array object
extern DA * newDA(void) {
    DA * array = malloc(sizeof(DA));
    assert(array != 0);
    array->capacity = 1;
    array->storage = malloc(sizeof(void *) * array->capacity);
    assert(array->storage != 0);
    array->size = 0;
    array->index = -1;
    array->debugVal = 0;
    array->freeMethod = 0;
    array->displayMethod = 0;

    return array;
}

// method is passed a function able to display element in generic array slot
extern void setDAdisplay(DA * items, void (*display)(void * ptr, FILE *fp)) { items->displayMethod = display; }

// method is passed a function able to free element in generic array slot
extern void setDAfree(DA * items, void (*free)(void * ptr)) { items->freeMethod = free; }

// method places given item at the slot named by given index
// array doubles if there is no room for insertion
extern void insertDA(DA * items, int index, void * value) {
    assert(index >= 0 && index <= sizeDA(items));
    if ((capacityDA(items) - sizeDA(items)) < 1) {
        items = doubleArray(items);
    }
    if (index == sizeDA(items)) {
        items->storage[index] = value;
        items->size += 1;
    }
    else {
        void * (*temp) = getDA(items, sizeDA(items) - 1);
        for (int i = sizeDA(items) - 1; i >= index; i--) {
            items->storage[i + 1] = temp;
            temp = items->storage[i + 1];
            items->storage[i + 1] = items->storage[i];
        }
        items->storage[index] = value;
        items->size += 1;
    }
}

// method doubles array capacity and reallocates memory for new capacity
static DA * doubleArray(DA * items) {
    /*DA * newArray = newDA();
    newArray->capacity = items->capacity * 2;
    assert(newArray->capacity >= 1);
    newArray->storage = malloc(sizeof(void *) * newArray->capacity);
    assert(newArray->storage != 0);
    unionDA(newArray, items);
    freeDA(items);*/

    items->capacity = (items->capacity) * 2;
    items->storage = realloc(items->storage, sizeof(void *) * items->capacity);
    assert(items->storage != 0);

    return items;
}

// method removes item at the given index
// method shifts each higher element one index down
// if ratio of array size to array capacity < .25, array shrinks by half
extern void * removeDA(DA * items, int index) {
    void * (*val) = getDA(items, index);
    void * (*temp) = val;
    for (int i = index; i < sizeDA(items); i++) { items->storage[i] = items->storage[i + 1]; }
    items->storage[sizeDA(items) - 1] = temp;
    items->size -= 1;
    assert(sizeDA(items) > 0);
    if ((sizeDA(items)/((double)capacityDA(items))) < .25) { items = halveArray(items); }

    return val;
}

// method halves array capacity and reallocates memory for new capacity
static DA * halveArray(DA * items) {
    /*DA * newArray = newDA();
    newArray->capacity = items->capacity / 2;
    assert(newArray->capacity >= 1);
    newArray->storage = malloc(sizeof(void *) * newArray->capacity);
    assert(newArray->storage != 0);
    unionDA(newArray, items);
    freeDA(items);*/

    items->capacity = (items->capacity) / 2;
    assert(items->capacity >= 1);
    items->storage = realloc(items->storage, sizeof(void *) * items->capacity);
    assert(items->storage != 0);

    return items;
}

// method moves all items in donor array to recipient array

// FIX ME: unionDA overwrites old array
extern void unionDA(DA * recipient, DA * donor) {
    for (int i = 0; i < donor->size; i++) {
        insertDA(recipient, i, donor->storage[i]);
    }
}

// method returns the value at the given index
extern void * getDA(DA * items, int index) {
    assert(index >= 0 && index < sizeDA(items));
    return items->storage[index];
}

// method replaces element value at the given index
extern void * setDA(DA * items, int index, void * value) {
    void * (*val) = getDA(items, index);
    if (index == sizeDA(items)) {
        insertDA(items, index, value);
        return val;
    }
    items->storage[index] = value;

    return val;
}

// method returns the number of items stored in the array
extern int sizeDA(DA * items) { return items->size; }

// method returns the capacity of array
static int capacityDA(DA * items) { return items->capacity; }

// method displays filled region of array and unfilled region of array
// if debugVal > zero, the display method prints number of empty slots (in brackets) immediately after the last element
// if no display method is set, the address of each item is printed
// an empty array with capacity 1 displays as [[1]]
extern void displayDA(DA * items, FILE *fp) {
    if ((sizeDA(items) == 0) && (items->debugVal > 0)) { // empty array and method should display num. empty indeces
        fprintf(fp, "[[%d]]", items->capacity);
    }
    else if ((sizeDA(items) == 0) && (items->debugVal == 0)) { // empty array and method should not display num. empty indeces
        fprintf(fp, "[]");
    }
    else if ((items->displayMethod == 0) && (items->debugVal > 0)) { // no display method set and method should display num. empty indeces
        fprintf(fp, "[");
        for (int i = 0; i < sizeDA(items); i++) {
            fprintf(fp, "@%p,", &items->storage[i]); // no set display method forces addresses of each item to be printed
        }
        fprintf(fp, "[%d]]", (capacityDA(items) - sizeDA(items)));
    }
    else if ((items->displayMethod == 0) && (items->debugVal == 0)) { // no display method set and method should not display num. empty indeces
        fprintf(fp, "[");
        for (int i = 0; i < sizeDA(items); i++) {
            fprintf(fp, "@%p,", &items->storage[i]);
        }
        fprintf(fp, "]");
    }
    else if ((items->displayMethod != 0) && (items->debugVal > 0)) { // display method set and method should display num. empty indeces
        fprintf(fp, "[");
        for (int i = 0; i < sizeDA(items); i++) {
            items->displayMethod(items->storage[i], fp);
            if (i != (sizeDA(items) - 1)) { fprintf(fp, ","); }
        }
        fprintf(fp, "[%d]]", (capacityDA(items) - sizeDA(items)));
    }
    else if ((items->displayMethod != 0) && (items->debugVal == 0)) { // display method set and method should not display num. empty indeces
        fprintf(fp, "[");
        for (int i = 0; i < sizeDA(items); i++) {
            items->displayMethod(items->storage[i], fp);
            if (i != (sizeDA(items) - 1)) { fprintf(fp, ","); }
        }
        fprintf(fp, "]");
    }
}

// method sets an internal flag in the object to the given value
extern int debugDA(DA * items, int level) {
    int prevVal = items->debugVal;
    items->debugVal = level;

    return prevVal;
}

// method frees dynamic array
extern void freeDA(DA * items) {
    if (items->freeMethod != 0) { // individual items are only freed if a freeMethod is set
        for (int i = 0; i < sizeDA(items); i++) { items->freeMethod(items->storage[i]); }
    }
    free(items->storage);
    free(items);
}
