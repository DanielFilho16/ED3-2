aux_arquivos.o : aux_arquivos.c
	gcc -o aux_arquivos.o -c aux_arquivos.c

aux_funcoes.o : aux_funcoes.c
	gcc -o aux_funcoes.o -c aux_funcoes.c

aux_geral.o : aux_geral.c
	gcc -o aux_geral.o -c aux_geral.c

main.o : main.c
	gcc -o main.o -c main.c

main : main.o aux_geral.o aux_funcoes.o aux_arquivos.o
	gcc -o main main.o aux_geral.o aux_funcoes.o aux_arquivos.o

all: main

run: main
	./main

clean:
	@rm *.o
