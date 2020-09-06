#include <stdlib.h>
#include <string.h>

#include "stack-models.h"
#include "stack-item.h"
#include "symbol.h"
#include "default-item.h"

StackItem newStackItemWithType(StackType type) {
  StackItem item = (StackItem) malloc(sizeof(_StackItem));
  item->type = type;
  item->previous = NULL;

  return item;
};

StackItem newStackItem(DefaultItem defaultItem) {
  StackItem item = newStackItemWithType(DEFAULT);

  item->content.defaultItem = defaultItem;

  return item;
}

StackItem newSymbolStackItem(Symbol symbol) {
  StackItem item = newStackItemWithType(SYMBOL);

  item->content.symbol = symbol;

  return item;
}

void destroyStackItem(StackItem item) {
  if(item->type == SYMBOL)
    destroySymbol(item->content.symbol);
  else
    destroyDefaultItem(item->content.defaultItem);

  free(item);
}
