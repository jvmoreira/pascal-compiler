#include <stdlib.h>
#include <string.h>

#include "libstack.h"

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

int itemMatchName(StackItem item, String name) {
  if(item->type != SYMBOL)
    return 0;

  Symbol symbol = extractSymbol(item);
  String symbolName = symbol ? symbol->name : NULL;
  return !symbolName ? 0 : strcmp(name, symbolName) == 0;
}

Symbol stackSearchSymbol(Stack stack, String targetName) {
  if(emptyStack(stack) || !isSymbolStack(stack) || invalidName(targetName))
    return NULL;

  StackItem item = stack->top;
  while(item && !itemMatchName(item, targetName))
    item = item->previous;

  return extractSymbol(item);
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
