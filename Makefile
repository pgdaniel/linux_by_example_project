CC=	gcc
STD=	_GNU_SOURCE
WARN=	-Wall

.c.o:
	$(CC) -c $(CFLAGS) -g -D$(STD) -ldb $(WARN) $<

all:   mcdcli 

mcdcli: mcdcli.o mcddb.o
	$(CC) mcdcli.o mcddb.o -o mcdcli

clean:
	rm -f *.o core a.out

clobber: clean
	rm -f mcdcli
