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

void destroyDefaultItem(DefaultItem item) {
  free(item->name);
  free(item);
}
