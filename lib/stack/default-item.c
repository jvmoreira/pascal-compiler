#include <stdlib.h>
#include <string.h>

#include "stack-models.h"
#include "default-item.h"
#include "helpers.h"

DefaultItem newDefaultItem(String name, int value) {
  if(invalidName(name))
    return NULL;

  DefaultItem item = (DefaultItem) malloc(sizeof(_DefaultItem));

  item->name = (String) malloc(1 + strlen(name));
  strcpy(item->name, name);
  item->value = value;

  return item;
}

DefaultItem extractDefaultItem(StackItem item) {
  if(!item || item->type != DEFAULT)
    return NULL;

  return item->content.defaultItem;
}

void destroyDefaultItem(DefaultItem item) {
  free(item->name);
  free(item);
}
