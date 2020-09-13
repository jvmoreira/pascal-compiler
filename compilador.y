%{

#include <stdio.h>
#include "libmepa.h"
int yylex();
int yyerror(char*);

extern char *yytext;
#define printToken printf("\n\nToken: %s\n\n", yytext);

%}

%token PROGRAM VAR INTEGER BOOL LABEL NUMERO TYPE ARRAY OF T_BEGIN
%token T_END PROCEDURE FUNCTION READ WRITE GOTO IF THEN ELSE WHILE DO AND OR NOT MULTP DIV
%token ATRIBUICAO PONTO_E_VIRGULA DOIS_PONTOS SINAL_MAIS SINAL_MENOS SINAL_IGUAL DIFERENTE
%token MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL VIRGULA PONTO ABRE_PARENTESES FECHA_PARENTESES IDENT

%%

programa:
  { geraInstrucaoUnica("INPP"); }
  PROGRAM IDENT
  ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
  bloco PONTO
  { geraInstrucaoUnica("PARA"); }
;

bloco:
  parte_declara_vars
  { }
  comando_composto
  { adicionaInstrucaoDMEM(); }
;

parte_declara_vars:
  var
;

var:
  VAR declara_vars { adicionaInstrucaoAMEM(); }
  |
;

declara_vars:
  declara_vars declara_var
  | declara_var
;

declara_var:
  { }
  lista_id_var DOIS_PONTOS tipo
  { }
  PONTO_E_VIRGULA
;

tipo:
  INTEGER { adicionaTipoAosSimbolos(TYPE_INT); }
  | BOOL { adicionaTipoAosSimbolos(TYPE_BOOL); }
  | IDENT { geraErro("Tipo não suportado"); }
;

lista_id_var:
  lista_id_var VIRGULA IDENT
  { handleNovaVariavel(token); }
  | IDENT { handleNovaVariavel(token); }
;

lista_idents:
  lista_idents VIRGULA IDENT
  | IDENT
;

comando_composto:
  T_BEGIN
  comandos
  T_END
;

comandos:
    comandos comando
  | comando
  |
;

comando:
    rotulo_opcional
    comando_sem_rotulo
    PONTO_E_VIRGULA
;

rotulo_opcional:
  NUMERO DOIS_PONTOS
  |
;

comando_sem_rotulo:
    atribuicao
  | READ ABRE_PARENTESES params_read FECHA_PARENTESES
  | WRITE ABRE_PARENTESES params_write FECHA_PARENTESES
  | comando_composto
;

params_read:
    params_read VIRGULA IDENT { handleNovaLeitura(token); }
  | IDENT { handleNovaLeitura(token); }
;

params_write:
    params_write VIRGULA IDENT { handleNovaEscrita(token); }
  | IDENT { handleNovaEscrita(token); }
;

atribuicao:
  variavel_lvalue
  ATRIBUICAO
  expressao
  { armazenaResultadoEmLValue(); }
;

relacao_com_expressao_simples:
    SINAL_IGUAL   expressao_simples { validaTipoAplicaOperacao("CMIG", TYPE_BOOL); }
  | DIFERENTE     expressao_simples { validaTipoAplicaOperacao("CMDG", TYPE_BOOL); }
  | MENOR         expressao_simples { validaTipoAplicaOperacao("CMME", TYPE_BOOL); }
  | MENOR_IGUAL   expressao_simples { validaTipoAplicaOperacao("CMEG", TYPE_BOOL); }
  | MAIOR         expressao_simples { validaTipoAplicaOperacao("CMMA", TYPE_BOOL); }
  | MAIOR_IGUAL   expressao_simples { validaTipoAplicaOperacao("CMAG", TYPE_BOOL); }
;

expressao:
  expressao_simples
  | expressao_simples relacao_com_expressao_simples
;

termo_com_sinal_opcional:
    SINAL_MENOS termo { handleInverteValor(); }
  | SINAL_MAIS  termo
  | termo
;

expressao_simples:
  termo_com_sinal_opcional operacoes_basicas
;

operacoes_basicas:
  operacoes_basicas operacao_basica
  | operacao_basica
  |
;

operacao_basica:
    SINAL_MAIS  termo { validaTipoAplicaOperacao("SOMA", TYPE_INT); }
  | SINAL_MENOS termo { validaTipoAplicaOperacao("SUBT", TYPE_INT); }
  | OR          termo { validaTipoAplicaOperacao("DISJ", TYPE_BOOL); }
;

termo:
    fator MULTP fator { validaTipoAplicaOperacao("MULT", TYPE_INT); }
  | fator DIV   fator { validaTipoAplicaOperacao("DIVI", TYPE_INT); }
  | fator AND   fator { validaTipoAplicaOperacao("CONJ", TYPE_BOOL); }
  | fator
;

fator:
    variavel
  | NUMERO { carregaConstanteEmpilhaTipo(token, TYPE_INT); }
  | ABRE_PARENTESES expressao FECHA_PARENTESES
  | NOT fator
;

variavel:
  IDENT { carregaValorEmpilhaTipo(token); }
;

variavel_lvalue:
  IDENT { salvaLValue(token); }
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
