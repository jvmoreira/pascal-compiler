#include <stdlib.h>
#include <string.h>

#include "libstack.h"

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

StackValue stackPopValue(Stack stack) {
  if(!isValueStack(stack))
    return NULL;

  StackItem item = stackPop(stack);
  StackValue value = extractStackValue(item);
  free(item);

  return value;
}

void destroyStackValue(StackValue stackValue) {
  if(!stackValue)
    return;
  free(stackValue->name);
  free(stackValue);
}
