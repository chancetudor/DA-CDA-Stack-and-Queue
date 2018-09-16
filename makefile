OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
#DAOBJS = da.o da-test2.o integer.o
CDAOBJS = cda.o test-cda4.o integer.o
#STACKOBJS = stack.o da.o stack-test.o integer.o
QOBJS = queue.o cda.o test-queue.o integer.o

all : cda queue #da stack

#da : $(DAOBJS)
	#gcc $(LOPTS) $(DAOBJS) -o da
cda : $(CDAOBJS)
	gcc $(LOPTS) $(CDAOBJS) -o cda
#stack : $(STACKOBJS)
	#gcc $(LOPTS) $(STACKOBJS) -o stack
queue : $(QOBJS)
	gcc $(LOPTS) $(QOBJS) -o queue
integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c
#da.o : da.c da.h
	#gcc $(OOPTS) da.c
#stack.o : stack.c stack.h da.h
	#gcc $(OOPTS) stack.c
cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c
queue.o : queue.c queue.h cda.h
	gcc $(OOPTS) queue.c
#da-test2.o : da-test2.c da.h
	#gcc $(OOPTS) da-test2.c
test-cda4.o : test-cda4.c cda.h
	gcc $(OOPTS) test-cda4.c
#stack-test.o : stack-test.c stack.h da.h
	#gcc $(OOPTS) stack-test.c
test-queue.o : test-queue.c queue.h cda.h
	gcc $(OOPTS) test-queue.c
test : cda queue #da stack
	#./da
	./cda
	#./stack
	./queue
valgrind : cda queue #da stack
	#valgrind --leak-check=full ./da
	valgrind --leak-check=full ./cda
	#valgrind --leak-check=full ./stack
	valgrind --leak-check=full ./queue
clean :
	rm -f $(DAOBJS) $(STACKOBJS) $(CDAOBJS) $(QOBJS) da stack cda queue
