#ifndef __LIB_MEPA__
#define __LIB_MEPA__

#include "types/mepa.h"
#include "libstack.h"

#define DEBUG 1
#define TAM_TOKEN 16

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
void geraArgumentoRotulo(int rotulo);
void geraInstrucaoDesvio(char* desvio, int rotulo);
void geraInstrucaoComRotulo(char* comando, int rotulo);
void geraInstrucaoUnicaComRotulo(char* comando, int rotulo);
void commitInstrucao();
void adicionaInstrucaoAMEM(int numeroDeVariaveis);
int desempilhaIntDaPilha(Stack stack, char* mensagemErro);
void finalizaCompilador();
void geraErro(char* erro);

/* ==================
 * == ESCOPO ======== */
void iniciaEscopo();
void iniciaNovoEscopo();
void desviaParaEscopoAtual();
void handleSaidaEscopo();
void handleNovaVariavel(char* nomeVariavel);
void handleNovaConstante(char* nomeConstante);
void handleNovoParametroFormal(char* nomeParametro);
void handleNegaBool();
void handleInverteValor();
void handleNovaLeitura(char* simbolo);
void handleNovaEscrita(char* simbolo);
void handleNovoProcedimento(char* nomeProcedimento);
void handleNovaFuncao(char* nomeFuncao);
void configuraChamadaSubrotina();
void configuraChamadaFuncao();
void handleNovoParametroReal();
void handleChamadaDeSubrotina();
void adicinaRotuloDoEscopoAtual();
void adicionaTipoAosSimbolosGeraAMEM(VarType tipo);
void configuraParametrosFormaisPorValor();
void configuraParametrosFormaisPorReferencia();
void atualizaTipoNivelLexicoDaFuncao(VarType tipo);
void adicionaTipoAosParametrosFormais(VarType tipo);
void atualizaNivelLexicoDosParametrosFormais();
void verificaFuncaoOuVariavel();
void empilhaTipo(char* nome, VarType tipo);
int desempilhaTipo();
void salvaSimboloOrDie(char* nomeSimbolo);
void salvaSimboloComoLValue();
void salvaLValueOrDie(char* nomeSimbolo);
void armazenaResultadoEmLValue();
void armazenaResultadoEmConstante();
void validaTipoAplicaOperacao(char* operacao, VarType tipo);
void geraInstrucaoCarregaValor(Symbol simbolo);
void carregaValorEmpilhaTipo(char* nomeSimbolo);
void carregaConstanteEmpilhaTipo(char* valor, VarType tipo);
int tipoNoTopoDaPilha();
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
