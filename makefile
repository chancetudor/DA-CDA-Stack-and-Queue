OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
DAOBJS = da.o da-test2.o integer.o
#CDAOBJS = cda.o test-cda3.o integer.o
STACKOBJS = stack.o stack-test.0 integer.o

all : da stack #cda

da : $(DAOBJS)
	gcc $(LOPTS) $(DAOBJS) -o da
#cda : $(CDAOBJS)
	#gcc $(LOPTS) $(CDAOBJS) -o cda
stack : $(STACKOBJS)
	gcc $(LOPTS) $(STACKOBJS) -o stack
integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c
da.o : da.c da.h
	gcc $(OOPTS) da.c
stack.o : stack.c stack.h da.h
	gcc $(OOPTS) stack.c
#cda.o : cda.c cda.h
	#gcc $(OOPTS) cda.c
da-test2.o : da-test2.c da.h
	gcc $(OOPTS) da-test2.c
#test-cda3.o : test-cda3.c cda.h
	#gcc $(OOPTS) test-cda3.c
stack-test.o : stack-test.c stack.h da.h
	gcc $(OOPTS) stack-test.c
test : da stack #cda
	./da
	#./cda
	./stack
valgrind : da stack #cda
	valgrind --leak-check=full ./da
	#valgrind --leak-check=full ./cda
	valgrind --leak-check=full ./stack
clean :
	rm -f $(DAOBJS) $(CDAOBJS) $(STACKOBJS) da stack #cda
