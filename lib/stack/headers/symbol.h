#ifndef __STACK_SYMBOL__
#define __STACK_SYMBOL__

Symbol newSymbol(String name);

Symbol extractSymbol(StackItem item);

void destroySymbol(Symbol symbol);

#endif
