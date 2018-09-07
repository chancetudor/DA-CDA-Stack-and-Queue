#include <stdio.h>
    #include <stdlib.h>
    #include "integer.h"
    #include "da.h"

    static void showItems(DA *items);

    int
    main(void)
        {
        srandom(1);
        DA *items = newDA();
        setDAfree(items,freeINTEGER);
        showItems(items);
        insertDA(items,0,newINTEGER(3));                 //insert at front
        insertDA(items,sizeDA(items),newINTEGER(2));     //insert at back
        insertDA(items,1,newINTEGER(1));                 //insert at middle
        showItems(items);
        printf("The value ");
        INTEGER *i = removeDA(items,0);                  //remove from front
        displayINTEGER(i,stdout);
        printf(" was removed.\n");
        freeINTEGER(i);
        showItems(items);
        int x = getINTEGER((INTEGER *) getDA(items,0));  //get the first item
        printf("The first item is %d.\n",x);
        printf("Freeing the list.\n");
        freeDA(items);
        return 0;
        }

    static void
    showItems(DA *items)
        {
        int old;
        setDAdisplay(items,displayINTEGER);
        printf("The items are ");
        displayDA(items,stdout);
        printf(".\n");
        printf("The items (debugged) are ");
        old = debugDA(items,1);
        setDAdisplay(items,0);
        displayDA(items,stdout);
        printf(".\n");
        debugDA(items,old);
        }
