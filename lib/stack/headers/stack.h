#ifndef __STACK__
#define __STACK__

Stack newStackWithType(StackType type);

void stackInsertValue(Stack stack, StackValue stackValue);

void stackInsertSymbol(Stack stack, Symbol symbol);

StackItem stackPop(Stack stack);

void destroyStack(Stack stack);

#endif
