%{

#include <stdio.h>
#include <string.h>

#include "libmepa.h"
#include "compilador.tab.h"

#define IMPRIME(STR) printf("%s    # %s \n", STR, token);

int linhaAtual = 1;
Simbolos simbolo, relacao;
char token[TAM_TOKEN];

%}

pulo_linha [\n]

descarte [\t ]+

ident [a-zA-Z][a-zA-Z1-9]*

numero [0-9]+

comentario "(*".*"*)"

%option nounput
%option noinput

%%

{pulo_linha} {linhaAtual++;}

{descarte}

{comentario}

program { simbolo  = s_program;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("program ");
          return PROGRAM;
}

var     { simbolo = s_var;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("var  ");
          return VAR;
}

label   { simbolo = s_label;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("label  ");
          return LABEL;
}

type    { simbolo = s_type;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("type  ");
          return TYPE;
}

array   { simbolo = s_array;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("array  ");
          return ARRAY;
}

of      { simbolo = s_of;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("of  ");
          return OF;
}

begin   { simbolo = s_begin;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("begin ");
          return T_BEGIN;
}

end     { simbolo = s_end;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("end  ");
          return T_END;
}

procedure { simbolo = s_procedure;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("procedure  ");
          return PROCEDURE;
}

function { simbolo = s_function;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("function  ");
          return FUNCTION;
}

goto    { simbolo = s_goto;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("goto  ");
          return GOTO;
}

if      { simbolo = s_if;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("if  ");
          return IF;
}

then    { simbolo = s_then;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("then  ");
          return THEN;
}

else    { simbolo = s_else;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("else  ");
          return ELSE;
}

while   { simbolo = s_while;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("while  ");
          return WHILE;
}

do      { simbolo = s_do;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("do  ");
          return DO;
}

and     { simbolo = s_and;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("and  ");
          return AND;
}

or      { simbolo = s_or;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("or  ");
          return OR;
}

not     { simbolo = s_not;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("not  ");
          return NOT;
}

div     { simbolo = s_div;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME("div  ");
          return DIV;
}

:=      { simbolo = s_atribuicao;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" atribuicao  ");
          return ATRIBUICAO;
}

\;      { simbolo = s_ponto_e_virgula;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" pt_virgula  ");
          return PONTO_E_VIRGULA;
}

\:      { simbolo = s_dois_pontos;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" dois pontos ");
          return DOIS_PONTOS;
}

\+      { simbolo = s_mais;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" mais ");
          return SINAL_MAIS;
}

\-      { simbolo = s_menos;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" menos ");
          return SINAL_MENOS;
}

=      { simbolo = s_igual;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" igual ");
          return SINAL_IGUAL;
}

\<\>      { simbolo = s_diferente;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" diferente ");
          return DIFERENTE;
}

\<      { simbolo = s_menor;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" menor que ");
          return MENOR;
}

\<=      { simbolo = s_menor_igual;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" menor ou igual que ");
          return MENOR_IGUAL;
}

\>      { simbolo = s_maior;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" maior que ");
          return MAIOR;
}

\>=      { simbolo = s_maior_igual;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" maior ou igual que ");
          return MAIOR_IGUAL;
}

\,      { simbolo = s_virgula;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" virgula  ");
          return VIRGULA;
}


\.      { simbolo = s_ponto;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" ponto  ");
          return PONTO;
}

\(      { simbolo = s_abre_parenteses;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" abre_parenteses  ");
          return ABRE_PARENTESES;
}

\)      { simbolo = s_fecha_parenteses;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" fecha_parenteses ");
          return FECHA_PARENTESES;
}

{ident} { simbolo = s_identificador;
          strncpy(token, yytext, TAM_TOKEN);
          IMPRIME(" ident  ");
          return IDENT;
}

%%
