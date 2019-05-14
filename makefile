CC=gcc
CFLAGS=-I. -Wall  -lm
DEPS = lib/graficos.h lib/carta.h lib/bisca.h
OBJ = trab1.o lib/graficos.o lib/carta.o lib/bisca.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bisca: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: clib
	rm -f *.o

clib:
	rm -f lib/*o
	
valgrind: bisca
	valgrind -v ./bisca 1
	
add:
	git add .

commit: add
	git commit -m "Auto"

push: commit
	git push