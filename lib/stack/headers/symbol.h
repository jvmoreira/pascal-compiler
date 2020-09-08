#ifndef __STACK_SYMBOL__
#define __STACK_SYMBOL__

Symbol newSymbol(String name);

Symbol extractSymbol(StackItem item);

Symbol stackPopSymbol(Stack stack);

void destroySymbol(Symbol symbol);

#endif
