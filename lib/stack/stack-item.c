#include <stdlib.h>
#include <string.h>

#include "stack-models.h"
#include "stack-item.h"

StackItem newStackItem() {
  StackItem item = (StackItem) malloc(sizeof(_StackItem));

  item->content.defaultItem = NULL;
  item->previous = NULL;

  return item;
}

void destroyStackItem(StackItem item) {
  free(item);
}
