#ifndef __STACK_TYPES__
#define __STACK_TYPES__

#define MAX_STR_LEN 16

typedef char* String;

typedef enum {
  CAT_VARIABLE, CAT_CONST, CAT_PARAM_VAL, CAT_PARAM_REF, CAT_PROCEDURE, CAT_FUNCTION, CAT_LABEL
} SymbolCategory;

typedef enum {
  TYPE_NULL, TYPE_UNDEFINED, TYPE_INT, TYPE_BOOL, TYPE_ADDR
} VarType;

typedef struct _Parameter {
  VarType type;
  SymbolCategory category;
  struct _Parameter *next;
} _Parameter;
typedef _Parameter* Parameter;

typedef struct {
  String name;
  SymbolCategory category;
  VarType type;
  int lexicalLevel;
  int shift;
  int label;
  int numberOfParameters;
  Parameter parameters;
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
