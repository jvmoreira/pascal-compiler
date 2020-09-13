#include "libmepa.h"

void handleWhile() {
  int rotuloInicioWhile = novoRotulo();
  int rotuloFimWhile = novoRotulo();

  geraInstrucaoUnicaComRotulo("NADA", rotuloInicioWhile);

  empilhaRotulo(rotuloInicioWhile);
  empilhaRotulo(rotuloFimWhile);
}

void avaliaExpressaoWhile() {
  int rotuloFimWhile = rotuloNoTopoDaPilha();
  geraInstrucaoDesvio("DSVF", rotuloFimWhile);
}

void handleFimWhile() {
  int rotuloFimWhile = desempilhaRotulo();
  int rotuloInicioWhile = desempilhaRotulo();
  geraInstrucaoDesvio("DSVS", rotuloInicioWhile);
  geraInstrucaoUnicaComRotulo("NADA", rotuloFimWhile);
}
