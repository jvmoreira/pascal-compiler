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
void novaLinha();
void geraInstrucao(char* comando);
void geraInstrucaoUnica(char* comando);
void geraArgumentoInteiro(int argumento);
void geraArgumentoString(char *argumento);
void geraInstrucaoDesvio(char* desvio, int rotulo);
void geraInstrucaoComRotulo(char* comando, int rotulo);
void geraInstrucaoUnicaComRotulo(char* comando, int rotulo);
void commitInstrucao();
int desempilhaIntDaPilha(Stack stack);
void finalizaCompilador();
void geraErro(char* erro);

/* ==================
 * == ESCOPO ======== */
void iniciaEscopo();
void iniciaNovoEscopo();
void handleDesvioParaEscopoAtual();
void handleEntradaEscopo();
void handleSaidaEscopo();
void configuraDeclaracaoVariaveis();
void handleNovaVariavel(char* nome);
void handleNegaBool();
void handleInverteValor();
void handleNovaLeitura(char* simbolo);
void handleNovaEscrita(char* simbolo);
void handleNovoProcedimento(char* nomeProcedimento);
void adicionaTipoAosSimbolosGeraAMEM(VarType tipo);
void empilhaTipo(char* nome, int tipo);
void salvaLValue(char* nomeSimbolo);
void armazenaResultadoEmLValue();
void validaTipoAplicaOperacao(char* operacao, VarType tipo);
void geraInstrucaoCarregaValor(Symbol simbolo);
void carregaValorEmpilhaTipo(char* nomeSimbolo);
void carregaConstanteEmpilhaTipo(char* valor, VarType tipo);
void destroiTodosEscopos();
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
 * == DESVIOS ======= */
void handleWhile();
void avaliaExpressaoWhile();
void handleFimWhile();
void avaliaExpressaoIf();
void handleSaidaIfThen();
void handleFimIf();

#endif
