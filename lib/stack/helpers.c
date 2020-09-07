#include <string.h>

#include "stack-models.h"
#include "helpers.h"

int invalidName(String name) {
  return !name || !strlen(name) || (strlen(name) > MAX_STR_LEN);
}

int emptyStack(Stack stack) {
  return !stack || !stack->top;
}
