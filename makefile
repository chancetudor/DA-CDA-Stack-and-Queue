CC = gcc
OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
DAOBJS = da.o da-test2.o integer.o
#CDAOBJS = cda.o test-cda.o integer.o

all : da #cda

da : $(DAOBJS)
	$(CC) $(LOPTS) $(DAOBJS) -o da
#cda : $(CDAOBJS)
	#$(CC) $(LOPTS) $(CDAOBJS) -o cda
da.o : da.c da.h
	$(CC) $(OOPTS) da.c
#cda.o : cda.c cda.h
	#$(CC) $(OOPTS) cda.c
da-test.o : da.c da.h
	$(CC) $(OOPTS) da-test2.c
#test-cda.o : test-cda.c cda.h
	#$(CC) $(OOPTS) test-cda.c
test : da
	./da
valgrind : da
	valgrind --leak-check=full ./da
clean :
	rm -f $(OBJS) $(CDAOBJS) da #cda
