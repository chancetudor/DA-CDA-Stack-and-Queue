OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
DAOBJS = da.o test-da.o integer.o
CDAOBJS = cda.o test-cda2.o integer.o

all : da cda

test-da : $(DAOBJS)
	gcc $(LOPTS) $(DAOBJS) -o test-da
cda : $(CDAOBJS)
	gcc $(LOPTS) $(CDAOBJS) -o cda
da.o : da.c da.h
	gcc $(OOPTS) da.c
cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c
test-da.o : test-da.c da.h
	gcc $(OOPTS) test-da.c
test-cda2.o : test-cda2.c cda.h
	gcc $(OOPTS) test-cda2.c
test : da cda
	./da
	./cda
valgrind : da cda
	valgrind --leak-check=full ./da
	valgrind --leak-check=full ./cda
clean :
	rm -f $(DAOBJS) $(CDAOBJS) da cda
