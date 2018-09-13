OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
DAOBJS = da.o da-test2.o integer.o
CDAOBJS = cda.o test-cda2.o integer.o

all : da cda

da : $(DAOBJS)
	gcc $(LOPTS) $(DAOBJS) -o da
cda : $(CDAOBJS)
	gcc $(LOPTS) $(CDAOBJS) -o cda
da.o : da.c da.h
	gcc $(OOPTS) da.c
cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c
da-test.o : da.c da.h
	gcc $(OOPTS) da-test2.c
test-cda2.o : test-cda2.c cda.h
	gcc $(OOPTS) test-cda2.c
test : da cda
	./da
	./cda
valgrind : da cda
	valgrind --leak-check=full ./da
	valgrind --leak-check=full ./cda
clean :
	rm -f $(OBJS) $(CDAOBJS) da cda
