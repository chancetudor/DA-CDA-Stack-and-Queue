#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "da.h"

void srandom(unsigned int);
long int random(void);

static void
display(DA *p,char *intro)
    {
    printf("%s",intro);
    if (sizeDA(p) < 200)
        {
        displayDA(p,stdout);
        }
    else
        {
        int k = 100;
        int j;
        printf("(displaying first and last %d elements)\n",k);
        for (j = 0; j < k; ++j)
            {
            displayINTEGER(getDA(p,j),stdout);
            printf(" ");
            }
        printf("... ");
        for (j = 0; j < k; ++j)
            {
            displayINTEGER(getDA(p,sizeDA(p)-k+j),stdout);
            if (j < k - 1) printf(" ");
            }
        printf("\n");
        }
    printf("\n");
    }

int
main(void)
    {
    srandom(5);
    int i,r,rounds=2,size=20;
    printf("INTEGER test 1 of DA, insertions at the tail\n");
    DA *p = newDA();
    setDAdisplay(p,displayINTEGER);
    setDAfree(p,freeINTEGER);
    debugDA(p,1);
    display(p,"items: ");
    for (r = 0; r < rounds; ++r)
        {
        for (i = 0; i < size; ++i)
            {
            int j = random() % size;
            if (random() % 2 == 0) {
                insertDA(p,sizeDA(p),newINTEGER(j));
              }
            else {
                assert(setDA(p,sizeDA(p),newINTEGER(j)) == 0);
              }
        }
        display(p,"items: ");
        printf("size is %d\n",sizeDA(p));
        }
    assert(debugDA(p,0) == 1);
    freeDA(p);
// -----------------------------------------------------------------------------
    srandom(10);
    rounds=2;
    size=1993;
    printf("INTEGER test 2 of DA, insertions at the tail\n");
    DA *y = newDA();
    setDAdisplay(p,displayINTEGER);
    setDAfree(p,freeINTEGER);
    debugDA(y,1);
    display(y,"items: ");
    for (r = 0; r < rounds; ++r)
        {
        for (i = 0; i < size; ++i)
            {
            int j = random() % size;
            if (random() % 2 == 0)
                insertDA(y,sizeDA(y),newINTEGER(j));
            else
                assert(setDA(y,sizeDA(y),newINTEGER(j)) == 0);
            }
        display(p,"items: ");
        printf("size is %d\n",sizeDA(y));
        }
    assert(debugDA(y,0) == 1);
    freeDA(y);
// -----------------------------------------------------------------------------
    srandom(15);
    rounds=2;
    size=148836;
    printf("INTEGER test 3 of DA, insertions at the tail\n");
    DA *z = newDA();
    setDAdisplay(z,displayINTEGER);
    setDAfree(z,freeINTEGER);
    debugDA(z,1);
    display(z,"items: ");
    for (r = 0; r < rounds; ++r)
        {
        for (i = 0; i < size; ++i)
            {
            int j = random() % size;
            if (random() % 2 == 0)
                insertDA(z,sizeDA(z),newINTEGER(j));
            else
                assert(setDA(z,sizeDA(z),newINTEGER(j)) == 0);
            }
        display(z,"items: ");
        printf("size is %d\n",sizeDA(z));
        }
    assert(debugDA(z,0) == 1);
    freeDA(z);
    return 0;
    }
