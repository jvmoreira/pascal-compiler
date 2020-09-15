#include <stdio.h>
#include "libmepa.h"

Symbol LValue;
Stack tabelaDeSimbolos;
Stack pilhaTipos;
Stack pilhaVariaveis;
Stack pilhaSubrotinas;

struct {
  int atual;
  int rotulo;
  int numeroDeVariaveis;
  int numeroDeSubrotinas;
} escopo;

void iniciaPilhas() {
  tabelaDeSimbolos = newStackWithType(SYMBOL);
  pilhaTipos = newStackWithType(VALUE);
  pilhaVariaveis = newStackWithType(VALUE);
  pilhaSubrotinas = newStackWithType(VALUE);
}

void iniciaEscopo() {
  escopo.atual = -1;
  escopo.rotulo = -1;
  escopo.numeroDeVariaveis = 0;
  escopo.numeroDeSubrotinas = 0;

  iniciaPilhas();
}

void iniciaNovoEscopo() {
  empilhaRotulo(escopo.rotulo);
  stackInsertValue(pilhaVariaveis, newStackValue("nVar", escopo.numeroDeVariaveis));
  stackInsertValue(pilhaSubrotinas, newStackValue("nSubRT", escopo.numeroDeSubrotinas));

  escopo.atual++;
  escopo.rotulo = novoRotulo();
  escopo.numeroDeVariaveis = 0;
  escopo.numeroDeSubrotinas = 0;
}

void handleDesvioParaEscopoAtual() {
  geraInstrucaoDesvio("DSVS", escopo.rotulo);
}

int escopoProgramaPrincipal() {
  return escopo.atual == 0;
}

void geraInstrucaoENPR() {
  geraInstrucaoComRotulo("ENPR", escopo.rotulo);
  geraArgumentoInteiro(escopo.atual);
}

void handleEntradaEscopo() {
  if(escopoProgramaPrincipal())
    geraInstrucaoComRotulo("NADA", escopo.rotulo);
  else
    geraInstrucaoENPR();

  commitInstrucao();
}

void finalizaEscopoAtual() {
  int nVariaveis = desempilhaIntDaPilha(pilhaVariaveis);
  int nSubrotinas = desempilhaIntDaPilha(pilhaSubrotinas);

  escopo.atual--;
  escopo.rotulo = desempilhaRotulo();
  escopo.numeroDeVariaveis = nVariaveis;
  escopo.numeroDeSubrotinas = nSubrotinas;
}

void adicionaInstrucaoDMEM() {
  geraInstrucao("DMEM");
  geraArgumentoInteiro(escopo.numeroDeVariaveis);
  commitInstrucao();
}

void adicionaInstrucaoRTPR() {
  geraInstrucao("RTPR");
  geraArgumentoInteiro(escopo.atual);
  geraArgumentoInteiro(0);
  commitInstrucao();
}

void removeSubrotinasLocaisTabelaSimbolos() {
  for(int i = 0; i < escopo.numeroDeSubrotinas; ++i)
    destroySymbol(stackPopSymbol(tabelaDeSimbolos));
}

void removeVariaveisLocaisTabelaSimbolos() {
  for(int i = 0; i < escopo.numeroDeVariaveis; ++i)
    destroySymbol(stackPopSymbol(tabelaDeSimbolos));
}

void handleSaidaEscopo() {
  adicionaInstrucaoDMEM();
  removeSubrotinasLocaisTabelaSimbolos();
  removeVariaveisLocaisTabelaSimbolos();

  if(!escopoProgramaPrincipal())
    adicionaInstrucaoRTPR();

  finalizaEscopoAtual();
}

void handleNovaVariavel(char* variavel) {
  escopo.numeroDeVariaveis++;

  Symbol simbolo = newSymbol(variavel);
  simbolo->type = TYPE_UNDEFINED;
  simbolo->category = CAT_VARIABLE;
  simbolo->lexicalLevel = escopo.atual;
  simbolo->shift = escopo.numeroDeVariaveis - 1;
  stackInsertSymbol(tabelaDeSimbolos, simbolo);
}

Symbol buscaSimboloOrDie(char* nomeSimbolo) {
  Symbol symbol = stackSearchSymbol(tabelaDeSimbolos, nomeSimbolo);
  if(!symbol)
    geraErro("Simbolo não declarado");

  return symbol;
}

void handleNegaBool() {
  empilhaTipo("NEGA", TYPE_BOOL);
  validaTipoAplicaOperacao("NEGA", TYPE_BOOL);
}

void handleInverteValor() {
  empilhaTipo("INVR", TYPE_INT);
  validaTipoAplicaOperacao("INVR", TYPE_INT);
}

void handleNovaLeitura(char* nomeSimbolo) {
  salvaLValue(nomeSimbolo);
  geraInstrucaoUnica("LEIT");
  empilhaTipo("LEIT", LValue->type);
  armazenaResultadoEmLValue();
}

void handleNovaEscrita(char* nomeSimbolo) {
  Symbol simbolo = buscaSimboloOrDie(nomeSimbolo);
  geraInstrucaoCarregaValor(simbolo);
  geraInstrucaoUnica("IMPR");
}

void adicionaProcedimentoTabelaDeSimbolos(char* nomeProcedimento) {
  Symbol procedimento = newSymbol(nomeProcedimento);
  procedimento->type = TYPE_NULL;
  procedimento->category = CAT_PROCEDURE;
  procedimento->lexicalLevel = escopo.atual;
  procedimento->label = escopo.rotulo;
  stackInsertSymbol(tabelaDeSimbolos, procedimento);
}

void handleNovoProcedimento(char* nomeProcedimento) {
  escopo.numeroDeSubrotinas++;
  iniciaNovoEscopo();
  adicionaProcedimentoTabelaDeSimbolos(nomeProcedimento);
}

void adicionaInstrucaoAMEM(int numeroDeVariaveis) {
  geraInstrucao("AMEM");
  geraArgumentoInteiro(numeroDeVariaveis);
  commitInstrucao();
}

int variavelComTipoIndefinido(Symbol simbolo) {
  return simbolo
    && simbolo->type == TYPE_UNDEFINED
    && simbolo->category == CAT_VARIABLE;
}

void adicionaTipoAosSimbolosGeraAMEM(VarType tipo) {
  if(tabelaDeSimbolos->length < escopo.numeroDeVariaveis)
    geraErro("#adicionaTipoAosSimbolosGeraAMEM");

  int variaveisParaAlocar = 0;
  StackItem itemAtual = tabelaDeSimbolos->top;
  Symbol simboloAtual = extractSymbol(itemAtual);

  while(variavelComTipoIndefinido(simboloAtual)) {
    simboloAtual->type = tipo;
    variaveisParaAlocar++;

    itemAtual = itemAtual->previous;
    simboloAtual = extractSymbol(itemAtual);
  }

  adicionaInstrucaoAMEM(variaveisParaAlocar);
}

void empilhaTipo(char* nome, int tipo) {
  stackInsertValue(pilhaTipos, newStackValue(nome, tipo));
}

int desempilhaTipo() {
  return desempilhaIntDaPilha(pilhaTipos);
}

void salvaLValue(char* nomeSimbolo) {
  LValue = buscaSimboloOrDie(nomeSimbolo);
}

void geraInstrucaoArmazena() {
  int atribuicaoIndireta = LValue->category == CAT_PARAM_REF;
  char *instrucao = atribuicaoIndireta ? "ARMI" : "ARMZ";
  geraInstrucao(instrucao);
  geraArgumentoInteiro(LValue->lexicalLevel);
  geraArgumentoInteiro(LValue->shift);
  commitInstrucao();
}

void armazenaResultadoEmLValue() {
  int tipoResultado = desempilhaTipo();
  if(tipoResultado != (int)LValue->type)
    geraErro("Atribuicao com tipos incompativeis");

  geraInstrucaoArmazena();
}

int validaTipoOperacao() {
  int tipo1 = desempilhaTipo();
  int tipo2 = desempilhaTipo();
  return tipo1 == tipo2;
}

void validaTipoAplicaOperacao(char* operacao, VarType tipoOperacao) {
  if(!validaTipoOperacao())
    geraErro("Operacao com tipos incompativeis");

  geraInstrucaoUnica(operacao);
  empilhaTipo(operacao, tipoOperacao);
}

void geraInstrucaoCarregaValor(Symbol simbolo) {
  int valorIndireto = simbolo->category == CAT_PARAM_REF;
  char *instrucao = valorIndireto ? "CRVI" : "CRVL";
  geraInstrucao(instrucao);
  geraArgumentoInteiro(simbolo->lexicalLevel);
  geraArgumentoInteiro(simbolo->shift);
  commitInstrucao();
}

void carregaValorEmpilhaTipo(char* nomeSimbolo) {
  Symbol simbolo = buscaSimboloOrDie(nomeSimbolo);

  geraInstrucaoCarregaValor(simbolo);
  empilhaTipo(simbolo->name, simbolo->type);
}

void carregaConstante(char* constante) {
  geraInstrucao("CRCT");
  geraArgumentoString(constante);
  commitInstrucao();
}

void carregaConstanteEmpilhaTipo(char* constante, VarType tipo) {
  carregaConstante(constante);
  empilhaTipo(constante, tipo);
}

void destroiPilhas() {
  destroyStack(tabelaDeSimbolos);
  destroyStack(pilhaTipos);
  destroyStack(pilhaVariaveis);
  destroyStack(pilhaSubrotinas);
}

void destroiTodosEscopos() {
  destroiPilhas();
}

void printPilha(Stack pilha, char* nomePilha) {
  StackItem itemAtual = pilha->top;
  StackValue conteudo = extractStackValue(itemAtual);

  printf("%s\n", nomePilha);
  while(conteudo) {
    printf("\tNOME\t\tTIPO\n");
    printf("\t%s\t\t%i\n\n", conteudo->name, conteudo->value);

    itemAtual = itemAtual->previous;
    conteudo = extractStackValue(itemAtual);
  }
}

void printPilhaTipos() {
  printPilha(pilhaTipos, "PILHA DE TIPOS");
}

void printTabelaDeSimbolos() {
  StackItem itemAtual = tabelaDeSimbolos->top;
  Symbol simboloAtual = extractSymbol(itemAtual);

  printf("TABELA DE SIMBOLOS\n");
  while(simboloAtual) {
    printf("\tNOME\tTIPO\tCAT\tNV LEX\tDESLOC\n");
    printf("\t%s\t%i\t%i\t%i\t%i\n\n", simboloAtual->name, simboloAtual->type, simboloAtual->category, simboloAtual->lexicalLevel, simboloAtual->shift);

    itemAtual = itemAtual->previous;
    simboloAtual = extractSymbol(itemAtual);
  }
}
