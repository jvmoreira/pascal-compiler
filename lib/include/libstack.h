#ifndef __LIB_STACK__
#define __LIB_STACK__

#include "types/stack.h"

/* ==================
 * == HELPERS ======= */
int invalidName(String name);
int isValueStack(Stack stack);
int isSymbolStack(Stack stack);
int emptyStack(Stack stack);

/* ==================
 * == VALUE ========= */
StackValue newStackValue(String name, int value);
StackValue extractStackValue(StackItem item);
StackValue stackPopValue(Stack stack);
void destroyStackValue(StackValue stackValue);

/* ==================
 * == PARAMETER ===== */
 Parameter newParameter(SymbolCategory category);
 void addParameterToSymbol(Symbol symbol, Parameter param);
 void destroyParameters(Symbol symbol);

/* ==================
 * == SYMBOL ======== */
Symbol newSymbol(String name);
Symbol extractSymbol(StackItem item);
Symbol stackSearchSymbol(Stack stack, String targetName);
Symbol stackPopSymbol(Stack stack);
void destroySymbol(Symbol symbol);

/* ==================
 * == ITEM ========== */
StackItem newStackItem(StackValue stackValue);
StackItem newSymbolStackItem(Symbol symbol);
void destroyStackItem(StackItem item);

/* ==================
 * == STACK ========= */
Stack newStackWithType(StackType type);
void stackInsertValue(Stack stack, StackValue stackValue);
void stackInsertSymbol(Stack stack, Symbol symbol);
StackItem stackPop(Stack stack);
void destroyStack(Stack stack);

#endif
