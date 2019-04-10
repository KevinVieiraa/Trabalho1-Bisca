all: trab

trab: trab1.c lib/graficos.h graficos.o 
	gcc -o trab1 trab1.c graficos.o -lm

graficos.o: lib/graficos.c lib/graficos.h
	gcc -c lib/graficos.c

run: trab1
	./trab1
	
valgrind: trab1
	valgrind -v ./trab1

clean: 
	rm -rf *.o trab1

cleanobj: 
	rm -rf *.o
	
add:
	git add .

commit: add
	git commit -m "Auto"

push: commit
	git push




