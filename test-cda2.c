#include <stdio.h>
    #include <stdlib.h>
    #include "integer.h"
    #include "cda.h"

    static void showItems(CDA *items);

    int
    main(void)
        {
        srandom(1);
        CDA *items = newCDA();
        setCDAfree(items,freeINTEGER);
        showItems(items);
        insertCDA(items,0,newINTEGER(3));                 //insert at front
        insertCDA(items,sizeCDA(items),newINTEGER(2));     //insert at back
        insertCDA(items,1,newINTEGER(1));                 //insert at middle
        showItems(items);
        printf("The value ");
        INTEGER *i = removeCDA(items,0);                  //remove from front
        displayINTEGER(i,stdout);
        printf(" was removed.\n");
        freeINTEGER(i);
        showItems(items);
        int x = getINTEGER((INTEGER *) getCDA(items,0));  //get the first item
        printf("The first item is %d.\n",x);
	      CDA *new = newCDA();
	      insertCDA(new, 0, newINTEGER(100));
        insertCDA(new, sizeCDA(new), newINTEGER(50));
	      insertCDA(new, 1, newINTEGER(150));
	      insertCDA(new, 2, newINTEGER(25));
        showItems(new);
	      unionCDA(items, new);
        printf("Items after union:\n");
	      showItems(items);
        printf("New after union:\n");
        showItems(new);
	printf("Freeing the list.\n");
        freeCDA(items);
        return 0;
        }

    static void
    showItems(CDA *items)
        {
        int old;
        setCDAdisplay(items,displayINTEGER);
        printf("The items are ");
        displayCDA(items,stdout);
        printf(".\n");
        printf("The items (debugged) are ");
        old = debugCDA(items,1);
        setCDAdisplay(items,0);
        displayCDA(items,stdout);
        printf(".\n");
        debugCDA(items,old);
        }
