#ifndef __MEPA_TYPES__
#define __MEPA_TYPES__

typedef enum {
  s_program, s_var, s_integer, s_bool, s_label, s_numero, s_type, s_array, s_of, s_begin, s_end,
  s_procedure, s_function, s_read, s_write, s_goto, s_if, s_then, s_else, s_while, s_do,
  s_atribuicao, s_ponto_e_virgula, s_dois_pontos, s_mais, s_menos, s_igual, s_diferente,
  s_and, s_or, s_not, s_multp, s_div, s_menor, s_menor_igual, s_maior, s_maior_igual,
  s_virgula, s_ponto, s_abre_parenteses, s_fecha_parenteses, s_identificador
} Simbolos;

typedef struct {
  int atual;
  int rotulo;
  int numeroDeVariaveis;
  int numeroDeSubrotinas;
  int numeroDeParametros;
} Escopo;

#endif
