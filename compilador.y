%{

#include <stdio.h>
#include "libmepa.h"
int yylex();
int yyerror(char*);

extern char *yytext;
#define printToken printf("\n\nToken: %s\n\n", yytext);
#if DEBUG >= 3
#define exec(cmd, str) cmd; printf("%s\n", str);
#else
#define exec(cmd, str) cmd;
#endif

%}

%token PROGRAM VAR CONST INTEGER BOOL LABEL NUMERO TYPE ARRAY OF T_BEGIN
%token T_END PROCEDURE FUNCTION READ WRITE GOTO IF THEN ELSE WHILE DO AND OR NOT MULTP DIV
%token ATRIBUICAO PONTO_E_VIRGULA DOIS_PONTOS SINAL_MAIS SINAL_MENOS SINAL_IGUAL DIFERENTE
%token MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL VIRGULA PONTO ABRE_PARENTESES FECHA_PARENTESES IDENT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

programa:
  { exec(geraInstrucaoUnica("INPP"), "program"); }
  PROGRAM IDENT lista_idents_ou_nada PONTO_E_VIRGULA
  bloco PONTO
  { exec(geraInstrucaoUnica("PARA"), "program"); }
;

bloco:
    parte_declara_consts
    parte_declara_vars
  { exec(desviaParaEscopoAtual(), "bloco"); }
    parte_declara_subrotinas
  { exec(adicinaRotuloDoEscopoAtual(), "bloco"); }
    comando_composto
  { exec(handleSaidaEscopo(), "bloco"); }
;

parte_declara_consts:
  CONST declara_consts
  |
;

declara_consts:
    define_const PONTO_E_VIRGULA declara_consts
  | define_const PONTO_E_VIRGULA
;

define_const:
  IDENT { exec(handleNovaConstante(token), "define_const"); }
  SINAL_IGUAL expressao { exec(armazenaResultadoEmConstante(), "define_const"); }
;

parte_declara_vars:
  VAR declara_vars
  |
;

declara_vars:
    declara_var declara_vars
  | declara_var
;

declara_var:
  lista_id_var DOIS_PONTOS tipo_variavel
  PONTO_E_VIRGULA
;

tipo_variavel:
    INTEGER { exec(adicionaTipoAosSimbolosGeraAMEM(TYPE_INT), "tipo_variavel"); }
  | BOOL    { exec(adicionaTipoAosSimbolosGeraAMEM(TYPE_BOOL), "tipo_variavel"); }
  | IDENT   { exec(geraErro("Tipo não suportado"), "tipo_variavel"); }
;

lista_id_var:
  lista_id_var VIRGULA IDENT
  { exec(handleNovaVariavel(token), "lista_id_var"); }
  | IDENT { exec(handleNovaVariavel(token), "lista_id_var"); }
;

lista_idents_ou_nada:
  ABRE_PARENTESES lista_idents FECHA_PARENTESES
  |
;

lista_idents:
  lista_idents VIRGULA IDENT
  | IDENT
;

parte_declara_subrotinas:
  declara_procedimentos_ou_nada
  declara_funcoes_ou_nada
;

declara_procedimentos_ou_nada:
  declara_procedimentos |
;

declara_funcoes_ou_nada:
  declara_funcoes |
;

declara_procedimentos:
    declara_procedimento declara_procedimentos
  | declara_procedimento
;

declara_procedimento:
  PROCEDURE IDENT { exec(handleNovoProcedimento(token), "declara_procedimento"); }
  parametros_formais_ou_nada PONTO_E_VIRGULA
  bloco PONTO_E_VIRGULA
;

declara_funcoes:
    declara_funcao declara_funcoes
  | declara_funcao
;

declara_funcao:
  FUNCTION IDENT { exec(handleNovaFuncao(token), "declara_funcao"); }
  parametros_formais_ou_nada
  DOIS_PONTOS tipo_funcao PONTO_E_VIRGULA
  bloco PONTO_E_VIRGULA
;

tipo_funcao:
    INTEGER { exec(atualizaTipoNivelLexicoDaFuncao(TYPE_INT), "tipo_funcao"); }
  | BOOL    { exec(atualizaTipoNivelLexicoDaFuncao(TYPE_BOOL), "tipo_funcao"); }
  | IDENT   { exec(geraErro("Tipo de funcao nao suportado"), "tipo_funcao"); }
;

parametros_formais_ou_nada:
  ABRE_PARENTESES
  parametros_formais { exec(atualizaNivelLexicoDosParametrosFormais(), "parametros_formais_ou_nada"); }
  FECHA_PARENTESES
  |
;

parametros_formais:
    secao_parametros_formais PONTO_E_VIRGULA parametros_formais
  | secao_parametros_formais
;

secao_parametros_formais:
  { exec(configuraParametrosFormaisPorValor(), "secao_parametros_formais"); }
    lista_parametros_formais DOIS_PONTOS tipo_parametro_formal
  | VAR { exec(configuraParametrosFormaisPorReferencia(), "secao_parametros_formais"); }
    lista_parametros_formais DOIS_PONTOS tipo_parametro_formal
;

lista_parametros_formais:
    lista_parametros_formais VIRGULA IDENT { exec(handleNovoParametroFormal(token), "lista_parametros_formais"); }
  | IDENT { exec(handleNovoParametroFormal(token), "lista_parametros_formais"); }
;

tipo_parametro_formal:
    INTEGER { exec(adicionaTipoAosParametrosFormais(TYPE_INT), "tipo_parametro_formal"); }
  | BOOL    { exec(adicionaTipoAosParametrosFormais(TYPE_BOOL), "tipo_parametro_formal"); }
  | IDENT   { exec(geraErro("Parametro com tipo não suportado"), "tipo_parametro_formal"); }
;

comando_composto:
    T_BEGIN comandos T_END
  | T_BEGIN T_END
;

comandos:
    comando PONTO_E_VIRGULA comandos
  | comando
  | comando PONTO_E_VIRGULA
;

comando:
  rotulo_opcional
  comando_sem_rotulo
;

rotulo_opcional:
  NUMERO DOIS_PONTOS
  |
;

comando_sem_rotulo:
    atribuicao_ou_chamada_procedimento
  | comando_repetitivo
  | comando_condicional
  | comando_composto
  | READ ABRE_PARENTESES params_read FECHA_PARENTESES
  | WRITE ABRE_PARENTESES params_write FECHA_PARENTESES
;

atribuicao_ou_chamada_procedimento:
  IDENT { exec(salvaSimboloOrDie(token), "atribuicao_ou_chamada_procedimento"); }
  decide_atribuicao_ou_chamada_procedimento
;

decide_atribuicao_ou_chamada_procedimento:
    atribuicao
  | chamada_procedimento { exec(handleChamadaDeSubrotina(), "decide_atribuicao_ou_chamada_procedimento"); }
;

atribuicao:
    ATRIBUICAO { exec(salvaSimboloComoLValue(), "atribuicao"); }
    expressao
  { exec(armazenaResultadoEmLValue(), "atribuicao"); }
;

chamada_procedimento:
    ABRE_PARENTESES
  { exec(configuraChamadaSubrotina(), "chamada_procedimento"); }
    lista_parametros_reais
    FECHA_PARENTESES
  | ABRE_PARENTESES { exec(configuraChamadaSubrotina(), "chamada_procedimento"); } FECHA_PARENTESES
  | { exec(configuraChamadaSubrotina(), "chamada_procedimento"); }
;

lista_parametros_reais:
    expressao { exec(handleNovoParametroReal(), "lista_parametros_reais"); } VIRGULA lista_parametros_reais
  | expressao { exec(handleNovoParametroReal(), "lista_parametros_reais"); }
;

params_read:
    params_read VIRGULA IDENT { exec(handleNovaLeitura(token), "params_read"); }
  | IDENT { exec(handleNovaLeitura(token), "params_read"); }
;

params_write:
    params_write VIRGULA IDENT { exec(handleNovaEscrita(token), "params_write"); }
  | IDENT { exec(handleNovaEscrita(token), "params_write"); }
;

comando_repetitivo:
  WHILE { exec(handleWhile(), "comando_repetitivo"); }
  expressao { exec(avaliaExpressaoWhile(), "comando_repetitivo"); }
  DO comando_sem_rotulo { exec(handleFimWhile(), "comando_repetitivo"); }
;

comando_condicional:
  if_then
  cond_else
  { exec(handleFimIf(), "comando_condicional"); }
;

if_then:
  IF expressao
  { exec(avaliaExpressaoIf(), "if_then"); }
   THEN comando_sem_rotulo
  { exec(handleSaidaIfThen(), "if_then"); }
;

cond_else:
  ELSE comando_sem_rotulo
  | %prec LOWER_THAN_ELSE
;

relacao_com_expressao_simples:
    SINAL_IGUAL   expressao_simples { exec(validaTipoAplicaOperacao("CMIG", TYPE_BOOL), "relacao_com_expressao_simples"); }
  | DIFERENTE     expressao_simples { exec(validaTipoAplicaOperacao("CMDG", TYPE_BOOL), "relacao_com_expressao_simples"); }
  | MENOR         expressao_simples { exec(validaTipoAplicaOperacao("CMME", TYPE_BOOL), "relacao_com_expressao_simples"); }
  | MENOR_IGUAL   expressao_simples { exec(validaTipoAplicaOperacao("CMEG", TYPE_BOOL), "relacao_com_expressao_simples"); }
  | MAIOR         expressao_simples { exec(validaTipoAplicaOperacao("CMMA", TYPE_BOOL), "relacao_com_expressao_simples"); }
  | MAIOR_IGUAL   expressao_simples { exec(validaTipoAplicaOperacao("CMAG", TYPE_BOOL), "relacao_com_expressao_simples"); }
;

expressao:
  expressao_simples
  | expressao_simples relacao_com_expressao_simples
;

termo_com_sinal_opcional:
    SINAL_MENOS termo { exec(handleInverteValor(), "termo_com_sinal_opcional"); }
  | SINAL_MAIS  termo
  | termo
;

expressao_simples:
    termo_com_sinal_opcional operacoes_basicas
  | termo_com_sinal_opcional
;

operacoes_basicas:
    operacao_basica operacoes_basicas
  | operacao_basica
;

operacao_basica:
    SINAL_MAIS  termo { exec(validaTipoAplicaOperacao("SOMA", TYPE_INT), "operacao_basica"); }
  | SINAL_MENOS termo { exec(validaTipoAplicaOperacao("SUBT", TYPE_INT), "operacao_basica"); }
  | OR          termo { exec(validaTipoAplicaOperacao("DISJ", TYPE_BOOL), "operacao_basica"); }
;

termo:
    fator MULTP fator { exec(validaTipoAplicaOperacao("MULT", TYPE_INT), "termo"); }
  | fator DIV   fator { exec(validaTipoAplicaOperacao("DIVI", TYPE_INT), "termo"); }
  | fator AND   fator { exec(validaTipoAplicaOperacao("CONJ", TYPE_BOOL), "termo"); }
  | fator
;

fator:
    variavel_ou_funcao
  | NUMERO { exec(carregaConstanteEmpilhaTipo(token, TYPE_INT), "fator"); }
  | ABRE_PARENTESES expressao FECHA_PARENTESES
  | NOT fator { exec(handleNegaBool(), "fator"); }
;

variavel_ou_funcao:
  IDENT { exec(salvaSimboloOrDie(token), "variavel_ou_funcao"); }
  funcao_ou_nada
;

funcao_ou_nada:
    chamada_funcao { exec(handleChamadaDeSubrotina(), "funcao_ou_nada"); }
  | { exec(verificaFuncaoOuVariavel(), "funcao_ou_nada"); }
;

chamada_funcao:
    ABRE_PARENTESES
    { exec(configuraChamadaFuncao(), "chamada_funcao"); }
    lista_parametros_reais
    FECHA_PARENTESES
  | ABRE_PARENTESES { exec(configuraChamadaFuncao(), "chamada_funcao"); } FECHA_PARENTESES
;

%%

int main (int argc, char** argv) {
  if (argc != 2) {
    printf("usage compilador <arq>\n");
    return(-1);
  }

  FILE* sourceFile;
  sourceFile = fopen (argv[1], "r");

  if(sourceFile == NULL) {
    printf("File %s not found\n", argv[1]);
    return(-1);
  }

  iniciaCompilador();

  extern FILE* yyin;
  yyin = sourceFile;
  yyparse();

  finalizaCompilador();

  return 0;
}
