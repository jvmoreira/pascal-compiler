#ifndef __STACK__
#define __STACK__

Stack newStackWithType(StackType type);

StackItem stackPop(Stack stack);

void destroyStack(Stack stack);

#endif
