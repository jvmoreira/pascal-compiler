#include <stdio.h>
#include <stdlib.h>
#include "libmepa.h"


int proximoRotulo;
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
  return desempilhaIntDaPilha(pilhaRotulos);
}

void printPilhaRotulos() {
  printPilha(pilhaRotulos, "PILHA DE ROTULOS");
}

void finalizaRotulos() {
  destroyStack(pilhaRotulos);
}
