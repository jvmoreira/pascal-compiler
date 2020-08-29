#include <stdlib.h>
#include <string.h>

#include "stack.h"

StackItem StackItemBuild(String name) {
  StackItem item = (StackItem) malloc(sizeof(Symbol));

  size_t nameSize = strlen(name) + 1;
  item->name = (String) malloc(nameSize);
  strncpy(item->name, name, nameSize);

  item->next = item->previous = NULL;

  return item;
}

Stack* StackBuild() {
  Stack *stack = (Stack*) malloc(sizeof(Stack));

  stack->top = stack->bottom = NULL;
  stack->length = 0;

  return stack;
}

int StackEmpty(Stack *stack) {
  return (stack == NULL) || ((stack->length == 0) && (stack->top == NULL));
}

void StackInsert(Stack *stack, StackItem item) {
  if(StackEmpty(stack))
    stack->bottom = item;
  else
    stack->top->next = item;

  item->previous = stack->top;
  stack->top = item;

  stack->length++;
}

StackItem StackSearch(Stack *stack, char *targetName) {
  if(StackEmpty(stack))
    return NULL;

  StackItem currentItem = stack->top;
  while(currentItem) {
    if(strcmp(currentItem->name, targetName) == 0)
      return currentItem;

    currentItem = currentItem->previous;
  }

  return NULL;
}

StackItem StackPop(Stack *stack) {
  if(StackEmpty(stack))
    return NULL;

  StackItem lastItem = stack->top;
  stack->top = stack->top->previous;
  stack->length--;

  if(!StackEmpty(stack))
    stack->top->next = NULL;

  if(stack->bottom == lastItem)
    stack->bottom = stack->top;

  lastItem->next = lastItem->previous = NULL;

  return lastItem;
}

void StackItemDestroy(StackItem *itemRef) {
  StackItem item = *itemRef;

  free(item->name);
  free(item);
  *itemRef = NULL;
}

void StackDestroy(Stack **stackRef) {
  Stack *stack = *stackRef;

  StackItem current = StackPop(stack);

  while(current) {
    StackItemDestroy(&current);
    current = StackPop(stack);
  }

  free(stack);
  *stackRef = NULL;
}
