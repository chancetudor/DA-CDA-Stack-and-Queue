OOPTS = -g3 -std=c99 -Wall -Wextra -c
LOPTS = -g3 -std=c99 -Wall -Wextra
#DAOBJS = da.o da-test2.o integer.o
CDAOBJS = cda.o cda-0-21.o integer.o

all : cda #da

#da : $(DAOBJS)
	#gcc $(LOPTS) $(DAOBJS) -o da
cda : $(CDAOBJS)
	gcc $(LOPTS) $(CDAOBJS) -o cda
integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c
#da.o : da.c da.h
	#gcc $(OOPTS) da.c
cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c
#da-test2.o : da-test2.c da.h
	#gcc $(OOPTS) da-test2.c
cda-0-21.o : cda-0-21.c cda.h
	gcc $(OOPTS) cda-0-21.c
test : cda #da
	#./da
	./cda
valgrind : cda #da
	#valgrind --leak-check=full ./da
	valgrind --leak-check=full ./cda
clean :
	rm -f $(CDAOBJS) cda #$(DAOBJS) da
