#include <stdlib.h>
#include <string.h>

#include "stack-models.h"
#include "symbol.h"
#include "stack.h"
#include "helpers.h"

Symbol newSymbol(String name) {
  if(invalidName(name))
    return NULL;

  Symbol symbol = (Symbol) malloc(sizeof(_Symbol));

  symbol->name = (String) malloc(1 + strlen(name));
  strcpy(symbol->name, name);

  return symbol;
}

Symbol extractSymbol(StackItem item) {
  if(!item || item->type != SYMBOL)
    return NULL;

  return item->symbol;
}

Symbol stackPopSymbol(Stack stack) {
  if(!isSymbolStack(stack))
    return NULL;

  StackItem item = stackPop(stack);
  Symbol symbol = extractSymbol(item);
  free(item);

  return symbol;
}

void destroySymbol(Symbol symbol) {
  if(!symbol)
    return;
  free(symbol->name);
  free(symbol);
}
