#include <stdio.h>
#include <stdlib.h>
#include "libmepa.h"

#define TAM_ROTULO 4

int proximoRotulo;
char rotulo[TAM_ROTULO];
Stack pilhaRotulos;

void iniciaRotulos() {
  proximoRotulo = 0;
  pilhaRotulos = newStackWithType(VALUE);
}

int novoRotulo() {
  return proximoRotulo++;
}

void empilhaRotulo(int rotulo) {
  StackValue value = newStackValue("ROTULO", rotulo);
  stackInsertValue(pilhaRotulos, value);
}

int rotuloNoTopoDaPilha() {
  StackValue rotulo = extractStackValue(pilhaRotulos->top);
  if(!rotulo)
    geraErro("#rotuloNoTopoDaPilha");

  return rotulo->value;
}

int desempilhaRotulo() {
  StackValue conteudo = stackPopValue(pilhaRotulos);
  if(!conteudo)
    geraErro("#desempilhaRotulo");

  int rotulo = conteudo->value;
  destroyStackValue(conteudo);
  return rotulo;
}

void printPilhaRotulos() {
  printPilha(pilhaRotulos, "PILHA DE ROTULOS");
}

void finalizaRotulos() {
  destroyStack(pilhaRotulos);
}
