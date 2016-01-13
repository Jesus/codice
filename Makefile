CC=gcc
CFLAGS=-g -Wall

SRCS=main.c lista.c util.c comandos/origen.c comandos/diccionario.c comandos/neutro.c comandos/info.c comandos/ranking.c comandos/buscar.c

OBJS=$(SRCS:.c=.o)

MAIN=main

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o comandos/*.o *~ $(MAIN)
