#include <stdlib.h>

#include "libstack.h"

Parameter newParameter(SymbolCategory category) {
  if((category != CAT_PARAM_VAL) && (category != CAT_PARAM_REF))
    return NULL;

  Parameter param = (Parameter) malloc(sizeof(_Parameter));
  param->category = category;
  param->type = TYPE_UNDEFINED;
  param->next = NULL;

  return param;
}

void addParameterToSymbol(Symbol symbol, Parameter param) {
  if(!symbol)
    return;

  if(!symbol->parameters) {
    symbol->parameters = param;
    return;
  }

  Parameter lastParam = symbol->parameters;
  while(lastParam->next)
    lastParam = lastParam->next;

  lastParam->next = param;
}

void destroyParameters(Symbol symbol) {
  Parameter param = symbol->parameters;
  while(param) {
    Parameter paramToDestroy = param;
    param = param->next;
    free(paramToDestroy);
  }
}
