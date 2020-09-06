#include <stdlib.h>
#include <string.h>

#include "stack-models.h"
#include "value.h"
#include "helpers.h"

StackValue newStackValue(String name, int value) {
  if(invalidName(name))
    return NULL;

  StackValue stackValue = (StackValue) malloc(sizeof(_StackValue));
  stackValue->value = value;

  stackValue->name = (String) malloc(1 + strlen(name));
  strcpy(stackValue->name, name);

  return stackValue;
}

StackValue extractStackValue(StackItem item) {
  if(!item || item->type != VALUE)
    return NULL;

  return item->value;
}

void destroyStackValue(StackValue stackValue) {
  free(stackValue->name);
  free(stackValue);
}
