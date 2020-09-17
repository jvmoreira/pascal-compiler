#include "../include/libmepa.h"

Symbol subrotinaSendoChamada;
int parametrosEmpilhados = 0;
int chamadaDeSubrotinaOcorrendo = 0;
SymbolCategory categoriaParametrosFormais;

void geraInstrucaoENPR() {
  geraInstrucaoComRotulo("ENPR", simboloGlobal->label);
  geraArgumentoInteiro(simboloGlobal->lexicalLevel);
  commitInstrucao();
}

void geraInstrucaoCHPR() {
  geraInstrucao("CHPR");
  geraArgumentoRotulo(subrotinaSendoChamada->label);
  geraArgumentoInteiro(escopo.atual);
  commitInstrucao();
}

void geraInstrucaoRTPR() {
  geraInstrucao("RTPR");
  geraArgumentoInteiro(escopo.atual);
  geraArgumentoInteiro(escopo.numeroDeParametros);
  commitInstrucao();
}


// ================================================
// == Declaracao Subrotinas =======================
// ================================================

void adicionaSubrotinaNaTabelaDeSimbolos(char* nomeSubrotina, SymbolCategory categoria) {
  Symbol subrotina = newSymbol(nomeSubrotina);
  subrotina->type = TYPE_NULL;
  subrotina->category = categoria;
  subrotina->lexicalLevel = escopo.atual + 1;
  subrotina->label = novoRotulo();
  subrotina->numberOfParameters = 0;
  stackInsertSymbol(tabelaDeSimbolos, subrotina);
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

void atualizaTipoNivelLexicoDaFuncao(VarType tipo) {
  simboloGlobal->type = tipo;
  simboloGlobal->shift = -4 - simboloGlobal->numberOfParameters;
}


// ================================================
// == Parametros Formais ==========================
// ================================================

void adicionaParametroFormalNaTabelaDeSimbolos(char* nomeParametro) {
  Symbol parametro = newSymbol(nomeParametro);
  parametro->type = TYPE_UNDEFINED;
  parametro->category = categoriaParametrosFormais;
  parametro->lexicalLevel = escopo.atual;
  parametro->shift = 0;
  stackInsertSymbol(tabelaDeSimbolos, parametro);
}

void configuraParametrosFormaisPorValor() {
  categoriaParametrosFormais = CAT_PARAM_VAL;
}

void configuraParametrosFormaisPorReferencia() {
  categoriaParametrosFormais = CAT_PARAM_REF;
}

void handleNovoParametroFormal(char* nomeParametro) {
  validaSimboloNoEscopoAtualOrDie(nomeParametro);
  adicionaParametroFormalNaTabelaDeSimbolos(nomeParametro);
  addParameterToSymbol(simboloGlobal, newParameter(categoriaParametrosFormais));
  escopo.numeroDeParametros++;
  simboloGlobal->numberOfParameters++;
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


// ================================================
// == Parametros Reais ============================
// ================================================

Parameter parametroAtual() {
  Parameter param = subrotinaSendoChamada->parameters;

  for(int i = 0; i < parametrosEmpilhados; ++i)
    param = param->next;

  if(!param)
    geraErro("#parametroAtual");

  return param;
}

void validaParametroPorValorOrDie() {
  if(parametroAtual()->category != CAT_PARAM_VAL)
  geraErro("Parametro passado por referencia nao pode ser constante");
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

void carregaParametroRealEmpilhaTipo(Symbol simbolo) {
  Parameter param = parametroAtual();
  int passagemPorReferencia = param->category == CAT_PARAM_REF;
  int simboloPassadoPorReferencia = simbolo->category == CAT_PARAM_REF;
  int deveCarregarEndereco = passagemPorReferencia && !simboloPassadoPorReferencia;

  char *instrucao = deveCarregarEndereco ? "CREN" : "CRVL";
  empilhaTipo(simbolo->name, passagemPorReferencia ? TYPE_ADDR : simbolo->type);

  geraInstrucao(instrucao);
  geraArgumentoInteiro(simbolo->lexicalLevel);
  geraArgumentoInteiro(simbolo->shift);
  commitInstrucao();
}
