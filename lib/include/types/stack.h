#ifndef __STACK_TYPES__
#define __STACK_TYPES__

#define MAX_STR_LEN 16

typedef char* String;

typedef enum {
  CAT_VARIABLE, CAT_PARAMETER, CAT_PROCEDURE, CAT_FUNCTION, CAT_LABEL
} SymbolCategory;

typedef enum {
  TYPE_UNDEFINED, TYPE_INT, TYPE_BOOL
} VarType;

typedef struct {
  String name;
  SymbolCategory category;
  VarType type;
  short lexicalLevel;
  short shift;
} _Symbol;
typedef _Symbol* Symbol;

typedef struct {
  String name;
  int value;
} _StackValue;
typedef _StackValue* StackValue;

typedef enum {
  VALUE, SYMBOL
} StackType;

typedef struct _StackItem {
  union {
    Symbol symbol;
    StackValue value;
  };
  StackType type;
  struct _StackItem *previous;
} _StackItem;
typedef _StackItem* StackItem;

typedef struct {
  StackItem top;
  StackType type;
  int length;
} _Stack;
typedef _Stack* Stack;

#endif
