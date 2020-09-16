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

int argumentos = 0;

void geraInstrucao(char* comando) {
  fprintf(arquivoSaida, "     %s", comando);
}

void geraInstrucaoUnica(char* comando) {
  geraInstrucao(comando);
  commitInstrucao();
}

void adicionaVirgulaAntesDeArgumento() {
  if(argumentos > 0)
    fprintf(arquivoSaida, ",");
}

void geraArgumentoInteiro(int argumento) {
  adicionaVirgulaAntesDeArgumento();
  fprintf(arquivoSaida, " %i", argumento);
  argumentos++;
}

void geraArgumentoString(char *argumento) {
  adicionaVirgulaAntesDeArgumento();
  fprintf(arquivoSaida, " %s", argumento);
  argumentos++;
}

void geraArgumentoRotulo(int rotulo) {
  adicionaVirgulaAntesDeArgumento();
  fprintf(arquivoSaida, " R%02i", rotulo);
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

void adicionaInstrucaoAMEM(int numeroDeVariaveis) {
  geraInstrucao("AMEM");
  geraArgumentoInteiro(numeroDeVariaveis);
  commitInstrucao();
}

int desempilhaIntDaPilha(Stack stack) {
  StackValue valueWrapper = stackPopValue(stack);
  if(!valueWrapper)
    geraErro("#desempilhaValorDaPilha");

  int value = valueWrapper->value;
  destroyStackValue(valueWrapper);

  return value;
}

void finalizaCompilador() {
  fclose(arquivoSaida);

  destroiTodosEscopos();
  finalizaRotulos();
}

void geraErro(char* erro) {
  fprintf (stderr, "Erro na linha %d - %s\n", linhaAtual, erro);
  finalizaCompilador();
  exit(-1);
}
