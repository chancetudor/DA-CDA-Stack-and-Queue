CC = gcc
OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
DAOBJS = da.o test-da.o integer.o
CDAOBJS = cda.o test-cda.o integer.o

all : test-da test-cda

test-da : $(DAOBJS)
	$(CC) $(LOPTS) $(DAOBJS) -o test-da
test-cda : $(CDAOBJS)
	$(CC) $(LOPTS) $(CDAOBJS) -o test-cda
da.o : da.c da.h
	$(CC) $(OOPTS) da.c
cda.o : cda.c cda.h
	$(CC) $(OOPTS) cda.c
test-da.o : test-da.c da.h
	$(CC) $(OOPTS) test-da.c
test-cda.o : test-cda.c cda.h
	$(CC) $(OOPTS) test-cda.c
test : test-da
	./test-da
valgrind : test-da
	valgrind --leak-check=full ./test-da
clean :
	rm -f $(OBJS) $(CDAOBJS) test-da test-cda
