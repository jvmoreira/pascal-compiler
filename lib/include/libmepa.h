#ifndef __LIB_MEPA__
#define __LIB_MEPA__

#include "types/mepa.h"
#include "libstack.h"

#define DEBUG 5

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
void geraInstrucaoComRotulo(char* comando, char* rotulo);
void commitInstrucao();
int geraErro(char* erro);

/* ==================
 * == ESCOPO ======== */
void iniciaEscopo();
void configuraDeclaracaoVariaveis();
void handleNovaVariavel(char* nome);
void adicionaTipoAosSimbolos(VarType tipo);
void adicionaInstrucaoAMEM();
void adicionaInstrucaoDMEM();
void salvaLValue(char* nomeSimbolo);
void armazenaResultadoEmLValue();
void validaTipoAplicaOperacao(char* operacao, VarType tipo);
void carregaValorEmpilhaTipo(char* nomeSimbolo);
void carregaConstanteEmpilhaTipo(char* valor, VarType tipo);
void destroiPilhas();
void printPilha(Stack pilha, char* nomePilha);
void printPilhaTipos();
void printTabelaDeSimbolos();

#endif
