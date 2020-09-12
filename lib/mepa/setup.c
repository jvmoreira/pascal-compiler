#include <stdio.h>
#include <stdlib.h>

#include "libstack.h"
#include "setup.h"

FILE* outputFile;
Stack symbolTable;
Stack typesStack;
Stack variablesStack;
Stack subroutinesStack;

Simbolos simbolo, relacao;
char token[TAM_TOKEN];

void iniciaCompilador() {
  outputFile = fopen("MEPA", "w");

  iniciaPilhas();
}

void iniciaPilhas() {
  symbolTable = newStackWithType(SYMBOL);
  typesStack = newStackWithType(VALUE);
  variablesStack = newStackWithType(VALUE);
  subroutinesStack = newStackWithType(VALUE);
}

// ========================================================================================

void geraCodigo(char* comando) {
  fprintf(outputFile, "     %s\n", comando);
  fflush(outputFile);
}

void geraCodigoComRotulo(char* comando, char* rotulo) {
  fprintf(outputFile, "%s: %s \n", rotulo, comando);
  fflush(outputFile);
}

int geraErro(char* erro) {
  extern int nl;

  fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}
