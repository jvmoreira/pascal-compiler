#include <stdio.h>
#include <stdlib.h>

#include "libmepa.h"
#include "libstack.h"

FILE* arquivoSaida;
Stack tabelaDeSimbolos;
Stack pilhaTipos;
Stack pilhaVariaveis;
Stack pilhaSubrotinas;

Simbolos simbolo, relacao;
char token[TAM_TOKEN];

void iniciaCompilador() {
  arquivoSaida = fopen("MEPA", "w");

  iniciaPilhas();
}

void iniciaPilhas() {
  tabelaDeSimbolos = newStackWithType(SYMBOL);
  pilhaTipos = newStackWithType(VALUE);
  pilhaVariaveis = newStackWithType(VALUE);
  pilhaSubrotinas = newStackWithType(VALUE);
}

// ========================================================================================

void geraCodigo(char* comando) {
  fprintf(arquivoSaida, "     %s\n", comando);
  fflush(arquivoSaida);
}

void geraCodigoComRotulo(char* comando, char* rotulo) {
  fprintf(arquivoSaida, "%s: %s \n", rotulo, comando);
  fflush(arquivoSaida);
}

int geraErro(char* erro) {
  extern int nl;

  fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}
