#ifndef __LIB_MEPA__
#define __LIB_MEPA__

#include "types/mepa.h"
#include "libstack.h"

#define DEBUG 1

extern Simbolos simbolo, relacao;
extern char token[TAM_TOKEN];

/* ==================
 * == UTILS ========= */
void iniciaCompilador();
void finalizaCompilador();
void novaLinha();
void geraInstrucao(char* comando);
void geraInstrucaoUnica(char* comando);
void geraArgumentoInteiro(int argumento);
void geraArgumentoString(char *argumento);
void geraInstrucaoDesvio(char* desvio, int rotulo);
void geraInstrucaoComRotulo(char* comando, int rotulo);
void geraInstrucaoUnicaComRotulo(char* comando, int rotulo);
void commitInstrucao();
int geraErro(char* erro);

/* ==================
 * == ESCOPO ======== */
void iniciaEscopo();
void configuraDeclaracaoVariaveis();
void handleNovaVariavel(char* nome);
void handleInverteValor();
void handleNovaLeitura(char* simbolo);
void handleNovaEscrita(char* simbolo);
void adicionaTipoAosSimbolos(VarType tipo);
void adicionaInstrucaoAMEM();
void adicionaInstrucaoDMEM();
void empilhaTipo(char* nome, int tipo);
void salvaLValue(char* nomeSimbolo);
void armazenaResultadoEmLValue();
void validaTipoAplicaOperacao(char* operacao, VarType tipo);
void geraInstrucaoCarregaValor(Symbol simbolo);
void carregaValorEmpilhaTipo(char* nomeSimbolo);
void carregaConstanteEmpilhaTipo(char* valor, VarType tipo);
void destroiPilhas();
void printPilha(Stack pilha, char* nomePilha);
void printPilhaTipos();
void printTabelaDeSimbolos();

/* ==================
 * == ROTULOS ======= */
void iniciaRotulos();
int novoRotulo();
void empilhaRotulo(int rotulo);
int rotuloNoTopoDaPilha();
int desempilhaRotulo();
void printPilhaRotulos();
void finalizaRotulos();

/* ==================
 * == WHILE ========= */
void handleWhile();
void avaliaExpressaoWhile();
void handleFimWhile();

#endif
