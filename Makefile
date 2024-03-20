CC=clang
CFLAGS=-g -Wall -Wextra -Werror -gdwarf-4

EXEC=client-introduction client-tutoriel client-interactif client-tutorielFORT ProjetX client-projetX cryptemove BayofPigs crypteSeq planB

all: $(EXEC)

client-interactif: client-interactif.o client.o

client-tutoriel: client-tutoriel.o client.o

ProjetX: ProjetX.o client.o

cryptemove: cryptemove.o client.o

BayofPigs: BayofPigs.o client.o

crypteSeq: crypteSeq.o client.o

planB: planB.o client.o

client-projetX: client-projetX.o client.o

client-tutorielFORT : client-tutorielFORT.o client.o

client-introduction: client-introduction.o client.o

client.o: client.c client.h

clean:
	rm -f *.o

clear:
	rm -f $(EXEC)
