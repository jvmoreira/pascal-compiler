#ifndef __STACK__
#define __STACK__

typedef char* String;

typedef enum {
    VAR, PARAMETER, PROCEDURE, FUNCTION, LABEL
} SymbolType;

typedef struct _Symbol {
    String name;
    SymbolType type;
    short lexicalLevel;
    short shift;
    struct _Symbol *next;
    struct _Symbol *previous;
} Symbol;

typedef Symbol* StackItem;

typedef struct {
    StackItem top;
    StackItem bottom;

    int length;
} Stack;

StackItem StackItemBuild(String name);

Stack* StackBuild();

int StackEmpty(Stack *stack);

void StackInsert(Stack *stack, StackItem item);

StackItem StackSearch(Stack *stack, char *targetName);

StackItem StackPop(Stack *stack);

void StackItemDestroy(StackItem *itemRef);

void StackDestroy(Stack **stackRef);

#endif
