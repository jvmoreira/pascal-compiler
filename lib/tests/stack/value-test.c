#include "stack-models.h"
#include "value.h"
#include "testCase.h"

#include "value-test.h"

void executeStackValueTests() {
  newStackValueWithInvalidNamesTest();
  newStackValueTest();
  extractStackValueTest();
}

void newStackValueTest() {
  char name[5] = "John";
  int value = 16;
  StackValue stackValue = newStackValue(name, value);

  assert(stackValue != NULL, "#newStackValue returns pointer to a StackValue");
  assert(!strcmp(stackValue->name, name), "#newStackValue returns stackValue with correct name");
  assert(stackValue->value == value, "#newStackValue returns stackValue with correct value");

  destroyStackValue(stackValue);
}

void newStackValueWithInvalidNamesTest() {
  assert(newStackValue(NULL, 16) == NULL, "#newStackValue returns NULL when name is NULL");
  assert(newStackValue("", 16) == NULL, "#newStackValue returns NULL when name is empty");

  char invalidName[22] = { [0 ... 20] = 'a', '\0' };
  assert(newStackValue(invalidName, 16) == NULL, "#newStackValue returns NULL when name is bigger than MAX_STR_LENGTH");
}

void extractStackValueTest() {
  _StackItem item;
  _Symbol symbol;
  item.type = SYMBOL;
  item.symbol = &symbol;

  assert(extractStackValue(NULL) == NULL, "#extractStackValue returns NULL when item is NULL");
  assert(extractStackValue(&item) == NULL, "#extractStackValue returns NULL when item has SYMBOL type");

  _StackValue stackValue;
  item.type = VALUE;
  item.value = &stackValue;
  assert(extractStackValue(&item) == &stackValue, "#extractStackValue returns pointer to StackValue when item has VALUE type");
}
