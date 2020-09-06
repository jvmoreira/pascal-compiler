#ifndef __STACK_ITEM__
#define __STACK_ITEM__

StackItem newStackItem(DefaultItem defaultItem);

StackItem newSymbolStackItem(Symbol symbol);

void destroyStackItem(StackItem item);

#endif
