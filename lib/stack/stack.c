#include <stdlib.h>

#include "stack-models.h"
#include "stack.h"
#include "item.h"
#include "helpers.h"

Stack newStackWithType(StackType type) {
  Stack stack = (Stack) malloc(sizeof(_Stack));

  stack->type = type;
  stack->length = 0;
  stack->top = NULL;

  return stack;
}

StackItem stackPop(Stack stack) {
  if(emptyStack(stack))
    return NULL;

  StackItem item = stack->top;
  stack->top = item->previous;
  stack->length--;

  return item;
}

void destroyStack(Stack stack) {
  StackItem item;

  for(; (item = stackPop(stack)) ;)
    destroyStackItem(item);

  free(stack);
}
