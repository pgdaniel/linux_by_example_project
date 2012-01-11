CC=	gcc
STD=	_GNU_SOURCE
WARN=	-Wall
CFLAGS=	-g

.c.o:
	$(CC) -c $(CFLAGS) -D$(STD) $(WARN) $<

all:   mcdcli 

mcdcli: mcdcli.o mcddb.o
	$(CC) -ldb mcdcli.o mcddb.o -o mcdcli

clean:
	rm -f *.o core a.out

clobber: clean
	rm -f mcdcli
