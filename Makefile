FLEX=flex
BISON=bison
CC=gcc
PROGRAMA = regalloc
LEXICO = lexico.l
SINTATICO = sintatico.y
OBJETOS = Alocador.o Lista.o Pilha.o Grafo.o lexico.yy.o sintatico.tab.o

# $(PROGRAMA): $(LEXICO) $(SINTATICO) $(OBJETOS)
	# $(FLEX) -o sintatico/lex.yy.c $(LEXICO)
	# $(BISON) -d -o sintatico/sintatico.tab.c $(SINTATICO)
	# cp sintatico/sintatico.tab.h ./sintatico.tab.h
	# $(CC) -c sintatico/lex.yy.c sintatico/sintatico.tab.c -I.
	# $(CC) $(OBJETOS) -o principal


regalloc: $(OBJETOS)
	$(CC) -g $(OBJETOS) -o regalloc


Alocador.o: Alocador.c Alocador.h
	gcc -o Alocador.o -c Alocador.c -g

Lista.o: Lista.c Lista.h
	gcc -o Lista.o -c Lista.c -g

Pilha.o: Pilha.c Pilha.h
	gcc -o Pilha.o -c Pilha.c -g

Grafo.o: Grafo.c Grafo.h
	gcc -o Grafo.o -c Grafo.c -g


lexico.yy.o: lexico.yy.h lexico.yy.c sintatico.tab.h
	$(CC) -g -c lexico.yy.c

sintatico.tab.o: sintatico.tab.h sintatico.tab.c lexico.yy.h
	$(CC) -g -c sintatico.tab.c

lexico.yy.h lexico.yy.c: lexico.l
	flex lexico.l

sintatico.tab.h sintatico.tab.c: sintatico.y
	$(BISON) -d -o sintatico.tab.c $(SINTATICO)

clean:
	rm -f *.yy.c
	rm -f *.tab.c
	rm -f *.tab.h
	rm -f *.o
	rm -f regalloc
	rm -f *.tab.h
	rm -f *.tab.o
