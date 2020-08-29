#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

Simbolos simbolo, relacao;
char token[TAM_TOKEN];

FILE* outputFile=NULL;
void geraCodigo (char* rotulo, char* comando) {

  if (outputFile == NULL) {
    outputFile = fopen ("MEPA", "w");
  }

  if ( rotulo == NULL ) {
    fprintf(outputFile, "     %s\n", comando); fflush(outputFile);
  } else {
    fprintf(outputFile, "%s: %s \n", rotulo, comando); fflush(outputFile);
  }
}

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}
