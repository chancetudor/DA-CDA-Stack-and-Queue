CC = gcc
OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
#DAOBJS = da.o test-da.o integer.o
CDAOBJS = cda.o test-cda.o integer.o

all : cda

#test-da : $(DAOBJS)
	#$(CC) $(LOPTS) $(DAOBJS) -o test-da
cda : $(CDAOBJS)
	$(CC) $(LOPTS) $(CDAOBJS) -o cda
#da.o : da.c da.h
	#$(CC) $(OOPTS) da.c
cda.o : cda.c cda.h
	$(CC) $(OOPTS) cda.c
#test-da.o : test-da.c da.h
	$(CC) $(OOPTS) test-da.c
test-cda.o : test-cda.c cda.h
	$(CC) $(OOPTS) test-cda.c
test : cda
	./cda
valgrind : cda
	valgrind --leak-check=full ./cda
clean :
	rm -f $(OBJS) $(CDAOBJS) cda #test-da
