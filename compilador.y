%{

#include <stdio.h>
#include "libmepa.h"
int yylex();
int yyerror(char*);

extern char *yytext;
#define printToken printf("\n\nToken: %s\n\n", yytext);

%}

%token PROGRAM VAR INTEGER BOOL LABEL TYPE ARRAY OF T_BEGIN T_END PROCEDURE FUNCTION
%token GOTO IF THEN ELSE WHILE DO AND OR NOT DIV
%token ATRIBUICAO PONTO_E_VIRGULA DOIS_PONTOS SINAL_MAIS SINAL_MENOS SINAL_IGUAL DIFERENTE
%token MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL VIRGULA PONTO ABRE_PARENTESES FECHA_PARENTESES IDENT

%%

programa:
  { geraInstrucao("INPP"); commitInstrucao(); }
  PROGRAM IDENT
  ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
  bloco PONTO
  { geraInstrucao("PARA"); commitInstrucao(); }
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
