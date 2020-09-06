#ifndef __STACK_ITEM__
#define __STACK_ITEM__

StackItem newStackItem(StackValue stackValue);

StackItem newSymbolStackItem(Symbol symbol);

void destroyStackItem(StackItem item);

#endif
