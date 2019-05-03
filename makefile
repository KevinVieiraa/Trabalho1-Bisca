CC=gcc
CFLAGS=-I. -Wall  -lm
DEPS = lib/graficos.h lib/carta.h lib/bisca.h
OBJ = trab1.o lib/graficos.o lib/carta.o lib/bisca.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

trab1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: clib
	rm -f *.o

clib:
	rm -f lib/*o
	
valgrind: trab1
	valgrind ./trab1 1
	
add:
	git add .

commit: add
	git commit -m "Auto"

push: commit
	git push