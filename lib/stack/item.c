#include <stdlib.h>

#include "libstack.h"

StackItem newStackItemWithType(StackType type) {
  StackItem item = (StackItem) malloc(sizeof(_StackItem));
  item->type = type;
  item->previous = NULL;

  return item;
};

StackItem newStackItem(StackValue stackValue) {
  StackItem item = newStackItemWithType(VALUE);

  item->value = stackValue;

  return item;
}

StackItem newSymbolStackItem(Symbol symbol) {
  StackItem item = newStackItemWithType(SYMBOL);

  item->symbol = symbol;

  return item;
}

void destroyStackItem(StackItem item) {
  if(item->type == SYMBOL)
    destroySymbol(item->symbol);
  else
    destroyStackValue(item->value);

  free(item);
}
