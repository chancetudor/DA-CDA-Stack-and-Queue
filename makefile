TESTDIR = testing/
TESTS = $(sort $(basename $(notdir $(wildcard $(TESTDIR)*.c))))
OOPTS = -g -std=c99 -Wall -Wextra -c
LOPTS = -g -std=c99 -Wall -Wextra
DAOBJS = da.o da-0-9.o integer.o real.o string.o
#CDAOBJS = cda.o test-cda.o integer.o

all : da #cda

da : $(DAOBJS)
	gcc $(LOPTS) $(DAOBJS) -o da
#cda : $(CDAOBJS)
	#gcc $(LOPTS) $(CDAOBJS) -o cda
integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c
real.o : real.c real.h
	gcc $(OOPTS) real.c
string.o : string.c string.h
	gcc $(OOPTS) string.c
da.o : da.c da.h
	gcc $(OOPTS) da.c
#cda.o : cda.c cda.h
	#gcc $(OOPTS) cda.c
da-0-9.o : da.c da.h
	gcc $(OOPTS) da-0-9.c
#test-cda.o : test-cda.c cda.h
	#gcc $(OOPTS) test-cda.c
test : da #cda
	./da
	#./cda
valgrind : da cda
	valgrind --leak-check=full ./da
	#valgrind --leak-check=full ./cda
clean :
	rm -f $(DAOBJS) da #cda $(CDAOBJS)
