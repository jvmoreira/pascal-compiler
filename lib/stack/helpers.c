#include <string.h>

#include "stack-models.h"
#include "helpers.h"

int invalidName(String name) {
  return !name || !strlen(name) || (strlen(name) > MAX_STR_LEN);
}

int isValueStack(Stack stack) {
  return stack && (stack->type == VALUE);
}

int isSymbolStack(Stack stack) {
  return stack && (stack->type == SYMBOL);
}

int emptyStack(Stack stack) {
  return !stack || !stack->top;
}
