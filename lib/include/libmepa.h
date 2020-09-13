#ifndef __LIB_MEPA__
#define __LIB_MEPA__

#include "types/mepa.h"

extern char token[TAM_TOKEN];
extern Simbolos simbolo, relacao;

void iniciaCompilador();

void iniciaPilhas();

void geraCodigo(char* comando);
void geraCodigoComRotulo(char* comando, char* rotulo);
int geraErro(char* erro);

#endif
