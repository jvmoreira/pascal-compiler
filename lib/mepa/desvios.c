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
  return desempilhaIntDaPilha(pilhaRotulos, "#desempilhaRotulo");
}

void handleWhile() {
  int rotuloInicioWhile = novoRotulo();
  int rotuloFimWhile = novoRotulo();

  geraInstrucaoUnicaComRotulo("NADA", rotuloInicioWhile);

  empilhaRotulo(rotuloInicioWhile);
  empilhaRotulo(rotuloFimWhile);
}

void avaliaExpressaoWhile() {
  if(tipoNoTopoDaPilha() != TYPE_BOOL)
    geraErro("Expressao de while deve avaliar para valor booleano");

  int rotuloFimWhile = rotuloNoTopoDaPilha();
  geraInstrucaoDesvio("DSVF", rotuloFimWhile);
}

void handleFimWhile() {
  int rotuloFimWhile = desempilhaRotulo();
  int rotuloInicioWhile = desempilhaRotulo();
  geraInstrucaoDesvio("DSVS", rotuloInicioWhile);
  geraInstrucaoUnicaComRotulo("NADA", rotuloFimWhile);
}

void avaliaExpressaoIf() {
  if(tipoNoTopoDaPilha() != TYPE_BOOL)
    geraErro("Expressao de if deve avaliar para valor booleano");

  int rotuloFimIf = novoRotulo();
  int rotuloElse = novoRotulo();

  geraInstrucaoDesvio("DSVF", rotuloElse);

  empilhaRotulo(rotuloElse);
  empilhaRotulo(rotuloFimIf);
}

void handleSaidaIfThen() {
  int rotuloFimIf = desempilhaRotulo();
  int rotuloElse = rotuloNoTopoDaPilha();

  geraInstrucaoDesvio("DSVS", rotuloFimIf);
  geraInstrucaoUnicaComRotulo("NADA", rotuloElse);

  empilhaRotulo(rotuloFimIf);
}

void handleFimIf() {
  int rotuloFimIf = desempilhaRotulo();
  desempilhaRotulo();
  geraInstrucaoUnicaComRotulo("NADA", rotuloFimIf);
}

void printPilhaRotulos() {
  printPilha(pilhaRotulos, "PILHA DE ROTULOS");
}

void finalizaRotulos() {
  destroyStack(pilhaRotulos);
}
