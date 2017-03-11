#makefile du tp3

#executable
all: execLC

execLC: main.o GenCode.o  pileptr.o ALex.o Dico.o Err.o tds.o asem.o pile.o asynt.o
	gcc -o execLC main.o GenCode.o pileptr.o ALex.o Dico.o Err.o tds.o asem.o pile.o  asynt.o 

pileptr.o:pileptr.c pileptr.h
	gcc pileptr.c -c

main.o: main.c
	gcc main.c -c

ALex.o:ALex.c ALex.h
	gcc ALex.c -c

Err.o: Err.c Err.h
	gcc -c Err.c -o Err.o

Dico.o: Dico.c Dico.h
	gcc -c Dico.c

tds.o: tds.c
	gcc -c tds.c

asem.o: asem.c asem.h
	gcc -c asem.c
asynt.o: asynt.c asynt.h
	gcc -c asynt.c
	
pile.o: pile.c
	gcc -c pile.c

GenCode.o: GenCode.c GenCode.h
	gcc GenCode.c -c

all:execLC
clean:
	rm *.o
