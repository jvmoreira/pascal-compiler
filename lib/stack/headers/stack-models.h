#ifndef __STACK_MODELS__
#define __STACK_MODELS__

#define MAX_STR_LEN 20

typedef char* String;

typedef enum {
  VAR, PARAMETER, PROCEDURE, FUNCTION, LABEL
} SymbolType;

typedef struct {
  String name;
  SymbolType type;
  short lexicalLevel;
  short shift;
} _Symbol;
typedef _Symbol* Symbol;

typedef struct {
  String name;
  int value;
} _DefaultItem;
typedef _DefaultItem* DefaultItem;

typedef union {
  Symbol symbol;
  DefaultItem defaultItem;
} _StackContent;
typedef _StackContent* StackContent;

typedef enum {
  DEFAULT, SYMBOL
} StackType;

typedef struct _StackItem {
  _StackContent content;
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
