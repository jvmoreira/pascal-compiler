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
  iniciaRotulos();
}

void novaLinha() {
  linhaAtual++;
}

int argumentos = 0;

void geraInstrucao(char* comando) {
  fprintf(arquivoSaida, "     %s", comando);
}

void geraInstrucaoUnica(char* comando) {
  geraInstrucao(comando);
  commitInstrucao();
}

void adicionaVirgulaAntesArgumento() {
  if(argumentos > 0)
    fprintf(arquivoSaida, ",");
}

void geraArgumentoInteiro(int argumento) {
  adicionaVirgulaAntesArgumento();
  fprintf(arquivoSaida, " %i", argumento);
  argumentos++;
}

void geraArgumentoString(char *argumento) {
  adicionaVirgulaAntesArgumento();
  fprintf(arquivoSaida, " %s", argumento);
  argumentos++;
}

void geraInstrucaoDesvio(char* desvio, int rotulo) {
  geraInstrucao(desvio);
  fprintf(arquivoSaida, " R%02i", rotulo);
  commitInstrucao();
}

void geraInstrucaoComRotulo(char* comando, int rotulo) {
  fprintf(arquivoSaida, "R%02i: %s", rotulo, comando);
}

void geraInstrucaoUnicaComRotulo(char* comando, int rotulo) {
  geraInstrucaoComRotulo(comando, rotulo);
  commitInstrucao();
}

void commitInstrucao() {
  fprintf(arquivoSaida, "\n");
  fflush(arquivoSaida);
  argumentos = 0;
}

void finalizaCompilador() {
  fclose(arquivoSaida);

  destroiPilhas();
  finalizaRotulos();
}

int geraErro(char* erro) {
  fprintf (stderr, "Erro na linha %d - %s\n", linhaAtual, erro);
  finalizaCompilador();
  exit(-1);
}
