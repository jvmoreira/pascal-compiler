#include <stdio.h>
#include "libmepa.h"

Symbol LValue;
Symbol simboloGlobal;
Symbol subrotinaSendoChamada;
Stack tabelaDeSimbolos;
Stack pilhaTipos;
Stack pilhaVariaveis;
Stack pilhaSubrotinas;
Stack pilhaParametros;

int parametrosEmpilhados;
int chamadaDeSubrotinaOcorrendo;
SymbolCategory categoriaParametrosFormais;

struct {
  int atual;
  int rotulo;
  int numeroDeVariaveis;
  int numeroDeSubrotinas;
  int numeroDeParametros;
} escopo;

void iniciaPilhas() {
  tabelaDeSimbolos = newStackWithType(SYMBOL);
  pilhaTipos = newStackWithType(VALUE);
  pilhaVariaveis = newStackWithType(VALUE);
  pilhaSubrotinas = newStackWithType(VALUE);
  pilhaParametros = newStackWithType(VALUE);
}

void iniciaEscopo() {
  iniciaRotulos();

  escopo.atual = 0;
  escopo.rotulo = novoRotulo();
  escopo.numeroDeVariaveis = 0;
  escopo.numeroDeSubrotinas = 0;
  escopo.numeroDeParametros = 0;

  parametrosEmpilhados = 0;
  chamadaDeSubrotinaOcorrendo = 0;

  iniciaPilhas();
}

void iniciaNovoEscopo() {
  empilhaRotulo(escopo.rotulo);
  stackInsertValue(pilhaVariaveis, newStackValue("nVar", escopo.numeroDeVariaveis));
  stackInsertValue(pilhaSubrotinas, newStackValue("nSubRT", escopo.numeroDeSubrotinas));
  stackInsertValue(pilhaParametros, newStackValue("nParams", escopo.numeroDeParametros));

  escopo.atual++;
  escopo.rotulo = novoRotulo();
  escopo.numeroDeVariaveis = 0;
  escopo.numeroDeSubrotinas = 0;
  escopo.numeroDeParametros = 0;
}

void desviaParaEscopoAtual() {
  geraInstrucaoDesvio("DSVS", escopo.rotulo);
}

int escopoProgramaPrincipal() {
  return escopo.atual == 0;
}

void finalizaEscopoAtual() {
  if(escopoProgramaPrincipal())
    return;

  escopo.atual--;
  escopo.rotulo = desempilhaRotulo();
  escopo.numeroDeVariaveis = desempilhaIntDaPilha(pilhaVariaveis, "#finalizaEscopoAtual - nVar");
  escopo.numeroDeSubrotinas = desempilhaIntDaPilha(pilhaSubrotinas, "#finalizaEscopoAtual - nSubRT");
  escopo.numeroDeParametros = desempilhaIntDaPilha(pilhaParametros, "#finalizaEscopoAtual - nParams");
}

void adicionaInstrucaoDMEM() {
  if(!escopo.numeroDeVariaveis)
    return;
  geraInstrucao("DMEM");
  geraArgumentoInteiro(escopo.numeroDeVariaveis);
  commitInstrucao();
}

void adicionaInstrucaoRTPR() {
  geraInstrucao("RTPR");
  geraArgumentoInteiro(escopo.atual);
  geraArgumentoInteiro(escopo.numeroDeParametros);
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

void removeParametrosReaisTabelaSimbolos() {
  for(int i = 0; i < escopo.numeroDeParametros; ++i)
    destroySymbol(stackPopSymbol(tabelaDeSimbolos));
}

void handleSaidaEscopo() {
  adicionaInstrucaoDMEM();
  removeSubrotinasLocaisTabelaSimbolos();
  removeVariaveisLocaisTabelaSimbolos();
  removeParametrosReaisTabelaSimbolos();

  if(!escopoProgramaPrincipal())
    adicionaInstrucaoRTPR();

  finalizaEscopoAtual();
}

Symbol buscaSimbolo(char* nomeSimbolo) {
  return stackSearchSymbol(tabelaDeSimbolos, nomeSimbolo);
}

Symbol buscaSimboloOrDie(char* nomeSimbolo) {
  Symbol symbol = buscaSimbolo(nomeSimbolo);
  if(!symbol)
    geraErro("Simbolo nao declarado");

  return symbol;
}

int simboloExisteNoEscopoAtual(char* nomeSimbolo) {
  Symbol simboloExistente = buscaSimbolo(nomeSimbolo);

  return simboloExistente && (simboloExistente->lexicalLevel == escopo.atual);
}

void validaSimboloNoEscopoAtualOrDie(char* nomeSimbolo) {
  if(simboloExisteNoEscopoAtual(nomeSimbolo))
    geraErro("Redeclaracao de simbolo");
}

void handleNovaVariavel(char* nomeVariavel) {
  validaSimboloNoEscopoAtualOrDie(nomeVariavel);
  escopo.numeroDeVariaveis++;

  Symbol variavel = newSymbol(nomeVariavel);
  variavel->type = TYPE_UNDEFINED;
  variavel->category = CAT_VARIABLE;
  variavel->lexicalLevel = escopo.atual;
  variavel->shift = escopo.numeroDeVariaveis - 1;
  stackInsertSymbol(tabelaDeSimbolos, variavel);
}

void handleNovaConstante(char* nomeConstante) {
  adicionaInstrucaoAMEM(1);
  handleNovaVariavel(nomeConstante);
  salvaLValueOrDie(nomeConstante);
  LValue->category = CAT_CONST;
}

void adicionaParametroFormalNaTabelaDeSimbolos(char* nomeParametro) {
  Symbol parametro = newSymbol(nomeParametro);
  parametro->type = TYPE_UNDEFINED;
  parametro->category = categoriaParametrosFormais;
  parametro->lexicalLevel = escopo.atual;
  parametro->shift = 0;
  stackInsertSymbol(tabelaDeSimbolos, parametro);
}

void handleNovoParametroFormal(char* nomeParametro) {
  validaSimboloNoEscopoAtualOrDie(nomeParametro);
  adicionaParametroFormalNaTabelaDeSimbolos(nomeParametro);
  addParameterToSymbol(simboloGlobal, newParameter(categoriaParametrosFormais));
  escopo.numeroDeParametros++;
  simboloGlobal->numberOfParameters++;
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
  salvaLValueOrDie(nomeSimbolo);
  geraInstrucaoUnica("LEIT");
  empilhaTipo("LEIT", LValue->type);
  armazenaResultadoEmLValue();
}

void handleNovaEscrita(char* nomeSimbolo) {
  Symbol simbolo = buscaSimboloOrDie(nomeSimbolo);
  geraInstrucaoCarregaValor(simbolo);
  geraInstrucaoUnica("IMPR");
}

void geraInstrucaoENPR() {
  geraInstrucaoComRotulo("ENPR", simboloGlobal->label);
  geraArgumentoInteiro(simboloGlobal->lexicalLevel);
  commitInstrucao();
}

void adicionaSubrotinaNaTabelaDeSimbolos(char* nomeProcedimento, SymbolCategory categoria) {
  Symbol procedimento = newSymbol(nomeProcedimento);
  procedimento->type = TYPE_NULL;
  procedimento->category = categoria;
  procedimento->lexicalLevel = escopo.atual + 1;
  procedimento->label = novoRotulo();
  procedimento->numberOfParameters = 0;
  stackInsertSymbol(tabelaDeSimbolos, procedimento);
}

void handleNovaSubrotina(char* nomeSubrotina, SymbolCategory categoria) {
  validaSimboloNoEscopoAtualOrDie(nomeSubrotina);
  escopo.numeroDeSubrotinas++;
  adicionaSubrotinaNaTabelaDeSimbolos(nomeSubrotina, categoria);
  iniciaNovoEscopo();
  salvaSimboloOrDie(nomeSubrotina);
  geraInstrucaoENPR();
}

void handleNovoProcedimento(char* nomeProcedimento) {
  handleNovaSubrotina(nomeProcedimento, CAT_PROCEDURE);
}

void handleNovaFuncao(char* nomeFuncao) {
  handleNovaSubrotina(nomeFuncao, CAT_FUNCTION);
}

void configuraChamadaSubrotina() {
  chamadaDeSubrotinaOcorrendo = 1;
  subrotinaSendoChamada = simboloGlobal;
}

void configuraChamadaFuncao() {
  adicionaInstrucaoAMEM(1);
  configuraChamadaSubrotina();
}

void handleNovoParametroReal() {
  parametrosEmpilhados++;
  if(parametrosEmpilhados > subrotinaSendoChamada->numberOfParameters)
    geraErro("Numero incorreto (maior) de parametros na chamada de subrotina");
}

void geraInstrucaoCHPR() {
  geraInstrucao("CHPR");
  geraArgumentoRotulo(subrotinaSendoChamada->label);
  geraArgumentoInteiro(escopo.atual);
  commitInstrucao();
}

void handleChamadaDeSubrotina() {
  if(parametrosEmpilhados < subrotinaSendoChamada->numberOfParameters)
    geraErro("Numero incorreto de parametros na chamada de subrotina");


  for(int i = 0; i < parametrosEmpilhados; ++i)
    desempilhaTipo();

  if(subrotinaSendoChamada->category == CAT_FUNCTION)
    empilhaTipo("Func", subrotinaSendoChamada->type);

  geraInstrucaoCHPR();
  parametrosEmpilhados = 0;
  chamadaDeSubrotinaOcorrendo = 0;
}

void adicinaRotuloDoEscopoAtual() {
  geraInstrucaoUnicaComRotulo("NADA", escopo.rotulo);
}

int simboloComTipoIndefinido(Symbol simbolo, SymbolCategory categoria) {
  return simbolo
    && simbolo->type == TYPE_UNDEFINED
    && simbolo->category == categoria;
}

void adicionaTipoAosSimbolosGeraAMEM(VarType tipo) {
  if(tabelaDeSimbolos->length < escopo.numeroDeVariaveis)
    geraErro("#adicionaTipoAosSimbolosGeraAMEM");

  int variaveisParaAlocar = 0;
  StackItem itemAtual = tabelaDeSimbolos->top;
  Symbol simboloAtual = extractSymbol(itemAtual);

  while(simboloComTipoIndefinido(simboloAtual, CAT_VARIABLE)) {
    simboloAtual->type = tipo;
    variaveisParaAlocar++;

    itemAtual = itemAtual->previous;
    simboloAtual = extractSymbol(itemAtual);
  }

  adicionaInstrucaoAMEM(variaveisParaAlocar);
}

void configuraParametrosFormaisPorValor() {
  categoriaParametrosFormais = CAT_PARAM_VAL;
}

void configuraParametrosFormaisPorReferencia() {
  categoriaParametrosFormais = CAT_PARAM_REF;
}

void atualizaTipoNivelLexicoDaFuncao(VarType tipo) {
  simboloGlobal->type = tipo;
  simboloGlobal->shift = -4 - simboloGlobal->numberOfParameters;
}

void adicionaTipoAosParametrosFormais(VarType tipo) {
  StackItem itemAtual = tabelaDeSimbolos->top;
  Symbol simboloAtual = extractSymbol(itemAtual);

  while(simboloComTipoIndefinido(simboloAtual, categoriaParametrosFormais)) {
    simboloAtual->type = tipo;

    itemAtual = itemAtual->previous;
    simboloAtual = extractSymbol(itemAtual);
  }

  Parameter paramAtual = simboloGlobal->parameters;
  while(paramAtual) {
    if(paramAtual->type == TYPE_UNDEFINED)
      paramAtual->type = tipo;

    paramAtual = paramAtual->next;
  }
}

void atualizaNivelLexicoDosParametrosFormais() {
  int deslocamento = -4;

  StackItem itemAtual = tabelaDeSimbolos->top;
  Symbol simboloAtual = extractSymbol(itemAtual);
  for(int i = 0; i < escopo.numeroDeParametros; ++i) {
    simboloAtual->shift = deslocamento--;

    itemAtual = itemAtual->previous;
    simboloAtual = extractSymbol(itemAtual);
  }
}

void verificaFuncaoOuVariavel() {
  if(simboloGlobal->category == CAT_FUNCTION){
    adicionaInstrucaoAMEM(1);
    handleChamadaDeSubrotina();
  }
  else
    carregaValorEmpilhaTipo(simboloGlobal->name);
}

void empilhaTipo(char* nome, VarType tipo) {
  stackInsertValue(pilhaTipos, newStackValue(nome, tipo));
}

int desempilhaTipo() {
  return desempilhaIntDaPilha(pilhaTipos, "#desempilhaTipo");
}

void salvaSimboloOrDie(char* nomeSimbolo) {
  simboloGlobal = buscaSimboloOrDie(nomeSimbolo);
}

void salvaSimboloComoLValue() {
  LValue = simboloGlobal;
}

void salvaLValueOrDie(char* nomeSimbolo) {
  LValue = buscaSimbolo(nomeSimbolo);

  if(!LValue)
    geraErro("#salvaLValueOrDie");

  if(LValue->category == CAT_FUNCTION && LValue->lexicalLevel != escopo.atual)
    geraErro("Simbolo nao aceita atribuicao neste escopo");
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
  if(LValue->category == CAT_CONST)
    geraErro("Constante nao pode ter seu valor alterado");

  int tipoResultado = desempilhaTipo();

  if(tipoResultado != (int)LValue->type)
    geraErro("Atribuicao com tipos incompativeis");

  geraInstrucaoArmazena();
}

// Ao armazenar o valor da constante
// o simbolo referente a ela ja esta em LValue
void armazenaResultadoEmConstante() {
  geraInstrucaoArmazena();
  LValue->type = desempilhaTipo();
}

int validaTipoOperacao() {
  int tipo1 = desempilhaTipo();
  int tipo2 = desempilhaTipo();

  if(tipo1 == TYPE_ADDR && chamadaDeSubrotinaOcorrendo)
    geraErro("Parametro passado por referencia deve ser variavel");

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

Parameter parametroAtual() {
  Parameter param = subrotinaSendoChamada->parameters;
  for(int i = 0; i < parametrosEmpilhados; ++i)
    param = param->next;

  if(!param)
    geraErro("#parametroAtual");
  return param;
}

void carregaParametroRealEmpilhaTipo(Symbol simbolo) {
  Parameter param = parametroAtual();
  int passagemPorReferencia = param->category == CAT_PARAM_REF;
  int variavelPassadaPorReferencia = simbolo->category == CAT_PARAM_REF;
  int deveCarregarEndereco = passagemPorReferencia && !variavelPassadaPorReferencia;

  if(deveCarregarEndereco && simbolo->category == CAT_CONST)
    geraErro("Constante nao pode ser passada como referencia");

  char *instrucao = deveCarregarEndereco ? "CREN" : "CRVL";
  empilhaTipo(simbolo->name, passagemPorReferencia ? TYPE_ADDR : simbolo->type);

  geraInstrucao(instrucao);
  geraArgumentoInteiro(simbolo->lexicalLevel);
  geraArgumentoInteiro(simbolo->shift);
  commitInstrucao();
}

void carregaValorEmpilhaTipo(char* nomeSimbolo) {
  Symbol simbolo = buscaSimboloOrDie(nomeSimbolo);

  if(chamadaDeSubrotinaOcorrendo) {
    carregaParametroRealEmpilhaTipo(simbolo);
  } else {
    geraInstrucaoCarregaValor(simbolo);
    empilhaTipo(simbolo->name, simbolo->type);
  }
}

void validaParametroPorValorOrDie() {
  if(parametroAtual()->category != CAT_PARAM_VAL)
    geraErro("Parametro passado por referencia nao pode ser constante");
}

void carregaConstante(char* constante) {
  if(chamadaDeSubrotinaOcorrendo) {
    validaParametroPorValorOrDie();
  }
  geraInstrucao("CRCT");
  geraArgumentoString(constante);
  commitInstrucao();
}

void carregaConstanteEmpilhaTipo(char* constante, VarType tipo) {
  carregaConstante(constante);
  empilhaTipo(constante, tipo);
}

int tipoNoTopoDaPilha() {
  StackValue tipo = extractStackValue(pilhaTipos->top);
  if(!tipo)
    geraErro("#tipoNoTopoDaPilha");

  return tipo->value;
}

void destroiPilhas() {
  destroyStack(tabelaDeSimbolos);
  destroyStack(pilhaTipos);
  destroyStack(pilhaVariaveis);
  destroyStack(pilhaSubrotinas);
  destroyStack(pilhaParametros);
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
