#include <stdio.h>
#include <stdlib.h>

#include "libmepa.h"
#include "libstack.h"

FILE* arquivoSaida;

void iniciaCompilador() {
  arquivoSaida = fopen("MEPA", "w");

  iniciaPilhas();
}

void finalizaCompilador() {
  fclose(arquivoSaida);

  destroiPilhas();
}

void geraCodigo(char* comando) {
  fprintf(arquivoSaida, "     %s\n", comando);
  fflush(arquivoSaida);
}

void geraCodigoComRotulo(char* comando, char* rotulo) {
  fprintf(arquivoSaida, "%s: %s \n", rotulo, comando);
  fflush(arquivoSaida);
}

int geraErro(char* erro) {
  extern int linhaAtual;

  fprintf (stderr, "Erro na linha %d - %s\n", linhaAtual, erro);
  exit(-1);
}
