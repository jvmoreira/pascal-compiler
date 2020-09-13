#include <stdio.h>
#include "libmepa.h"

Symbol LValue;
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

void empilhaTipo(char* nome, int tipo) {
  stackInsertValue(pilhaTipos, newStackValue(nome, tipo));
}

int desempilhaTipo() {
  StackValue value = stackPopValue(pilhaTipos);
  int tipo = value->value;
  destroyStackValue(value);
  return tipo;
}

void salvaLValue(char* nomeSimbolo) {
  LValue = stackSearchSymbol(tabelaDeSimbolos, nomeSimbolo);
  if(!simbolo)
    geraErro("Variavel não declarada");
}

int atribuicaoIndireta() {
  return LValue->category == CAT_PARAM_REF;
}

void geraInstrucaoArmazena() {
  char *instrucao = atribuicaoIndireta() ? "ARMI" : "ARMZ";
  geraInstrucao(instrucao);
  geraArgumentoInteiro(LValue->lexicalLevel);
  geraArgumentoInteiro(LValue->shift);
  commitInstrucao();
}

void armazenaResultadoEmLValue() {
  int tipoResultado = desempilhaTipo();
  if(tipoResultado != (int)LValue->type)
    geraErro("Atribuicao com tipos incompativeis");

  geraInstrucaoArmazena();
}

int validaTipoOperacao() {
  int tipo1 = desempilhaTipo();
  int tipo2 = desempilhaTipo();
  return tipo1 == tipo2;
}

void validaTipoAplicaOperacao(char* operacao, VarType tipoOperacao) {
  if(!validaTipoOperacao())
    geraErro("Operacao com tipos incompativeis");

  geraInstrucaoUnica(operacao);
  empilhaTipo(operacao, tipoOperacao);
}

void carregaValor(Symbol simbolo) {
  geraInstrucao("CRVL");
  geraArgumentoInteiro(simbolo->lexicalLevel);
  geraArgumentoInteiro(simbolo->shift);
  commitInstrucao();
}

void carregaValorEmpilhaTipo(char* nomeSimbolo) {
  Symbol simbolo = stackSearchSymbol(tabelaDeSimbolos, nomeSimbolo);
  if(!simbolo)
    geraErro("Variavel não declarada");

  carregaValor(simbolo);
  empilhaTipo(simbolo->name, simbolo->type);
}

void carregaConstante(char* constante) {
  geraInstrucao("CRCT");
  geraArgumentoString(constante);
  commitInstrucao();
}

void carregaConstanteEmpilhaTipo(char* constante, VarType tipo) {
  carregaConstante(constante);
  empilhaTipo(constante, tipo);
}

void destroiPilhas() {
  // printTabelaDeSimbolos();
  destroyStack(tabelaDeSimbolos);
  destroyStack(pilhaTipos);
  destroyStack(pilhaVariaveis);
  destroyStack(pilhaSubrotinas);
}

void printPilha(Stack pilha, char* nomePilha) {
  StackItem itemAtual = pilha->top;
  StackValue conteudo = extractStackValue(itemAtual);

  printf("%s\n", nomePilha);
  while(conteudo) {
    printf("\tNOME\t\tVALOR\n");
    printf("\t%s\t\t%i\n\n", conteudo->name, conteudo->value);

    itemAtual = itemAtual->previous;
    conteudo = extractStackValue(itemAtual);
  }
}

void printPilhaTipos() {
  printPilha(pilhaTipos, "PILHA DE TIPOS");
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
