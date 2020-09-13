#include <stdio.h>
#include "libmepa.h"

Stack tabelaDeSimbolos;
Stack pilhaTipos;
Stack pilhaVariaveis;
Stack pilhaSubrotinas;

struct {
  int atual;
  int numeroDeVariaveis;
} escopo;

void iniciaPilhas() {
  tabelaDeSimbolos = newStackWithType(SYMBOL);
  pilhaTipos = newStackWithType(VALUE);
  pilhaVariaveis = newStackWithType(VALUE);
  pilhaSubrotinas = newStackWithType(VALUE);
}

void iniciaEscopo() {
  escopo.atual = 0;
  escopo.numeroDeVariaveis = 0;

  iniciaPilhas();
}

void handleNovaVariavel(char* variavel) {
  escopo.numeroDeVariaveis++;

  Symbol simbolo = newSymbol(variavel);
  simbolo->type = TYPE_UNDEFINED;
  simbolo->category = CAT_VARIABLE;
  simbolo->lexicalLevel = escopo.atual;
  simbolo->shift = escopo.numeroDeVariaveis - 1;
  stackInsertSymbol(tabelaDeSimbolos, simbolo);
}

void adicionaTipoAosSimbolos(VarType tipo) {
  if(tabelaDeSimbolos->length < escopo.numeroDeVariaveis)
    geraErro("#adicionaTipoAosSimbolos");

  StackItem itemAtual = tabelaDeSimbolos->top;
  Symbol simboloAtual = extractSymbol(itemAtual);

  while(simboloAtual && simboloAtual->type == TYPE_UNDEFINED) {
    simboloAtual->type = tipo;

    itemAtual = itemAtual->previous;
    simboloAtual = extractSymbol(itemAtual);
  }
}

void adicionaInstrucaoAMEM() {
  geraInstrucao("AMEM");
  geraArgumentoInteiro(escopo.numeroDeVariaveis);
  commitInstrucao();
}

void adicionaInstrucaoDMEM() {
  geraInstrucao("DMEM");
  geraArgumentoInteiro(escopo.numeroDeVariaveis);
  commitInstrucao();
}

void printTabelaDeSimbolos();
void destroiPilhas() {
  printTabelaDeSimbolos();
  destroyStack(tabelaDeSimbolos);
  destroyStack(pilhaTipos);
  destroyStack(pilhaVariaveis);
  destroyStack(pilhaSubrotinas);
}

void printTabelaDeSimbolos() {
 StackItem itemAtual = tabelaDeSimbolos->top;
 Symbol simboloAtual = extractSymbol(itemAtual);

 printf("TABELA DE SIMBOLOS\n");
 while(simboloAtual) {
   printf("\tNOME\t\tTIPO\t\tNV LEX\t\tDESLOC\n");
   printf("\t%s\t\t%i\t\t%i\t\t%i\n\n", simboloAtual->name, simboloAtual->type, simboloAtual->lexicalLevel, simboloAtual->shift);

   itemAtual = itemAtual->previous;
   simboloAtual = extractSymbol(itemAtual);
 }
}
