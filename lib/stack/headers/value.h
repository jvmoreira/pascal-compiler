#ifndef __STACK_VALUE__
#define __STACK_VALUE__

StackValue newStackValue(String name, int value);

StackValue extractStackValue(StackItem item);

void destroyStackValue(StackValue stackValue);

#endif