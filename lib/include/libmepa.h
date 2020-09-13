#ifndef __LIB_MEPA__
#define __LIB_MEPA__

#include "types/mepa.h"

/* ==================
 * == UTILS ========= */
void iniciaCompilador();
void finalizaCompilador();
void geraCodigo(char* comando);
void geraCodigoComRotulo(char* comando, char* rotulo);
int geraErro(char* erro);

/* ==================
 * == PILHAS ======== */
void iniciaPilhas();
void destroiPilhas();

#endif
