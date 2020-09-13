#include <stdio.h>
#include <stdlib.h>

#include "libmepa.h"

FILE* arquivoSaida;

int linhaAtual = 1;
Simbolos simbolo, relacao;
char token[TAM_TOKEN];

void iniciaCompilador() {
  arquivoSaida = fopen("MEPA", "w");

  iniciaEscopo();
}

void novaLinha() {
  linhaAtual++;
}

void geraInstrucao(char* comando) {
  fprintf(arquivoSaida, "     %s", comando);
}

void geraArgumentoInteiro(int argumento) {
  fprintf(arquivoSaida, " %i", argumento);
}

void geraArgumentoString(char *argumento) {
  fprintf(arquivoSaida, " %s", argumento);
}

void geraInstrucaoComRotulo(char* comando, char* rotulo) {
  fprintf(arquivoSaida, "%s: %s", rotulo, comando);
}

void commitInstrucao() {
  fprintf(arquivoSaida, "\n");
  fflush(arquivoSaida);
}

void finalizaCompilador() {
  fclose(arquivoSaida);

  destroiPilhas();
}

int geraErro(char* erro) {
  fprintf (stderr, "Erro na linha %d - %s\n", linhaAtual, erro);
  exit(-1);
}
