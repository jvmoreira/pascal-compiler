#include "stack-models.h"
#include "default-item.h"
#include "testCase.h"

#include "default-item-test.h"

void executeDefaultItemTests() {
  newDefaultItemWithInvalidNamesTest();
  newDefaultItemTest();
}

void newDefaultItemTest() {
  char name[5] = "John";
  int value = 16;
  DefaultItem item = newDefaultItem(name, value);

  assert(item != NULL, "#newDefaultItem returns pointer to a DefaultItem");
  assert(!strcmp(item->name, name), "#newDefaultItem returns defaultItem with correct name");
  assert(item->value == value, "#newDefaultItem returns defaultItem with correct value");

  destroyDefaultItem(item);
}

void newDefaultItemWithInvalidNamesTest() {
  assert(newDefaultItem(NULL, 16) == NULL, "#newDefaultItem returns NULL when name is NULL");
  assert(newDefaultItem("", 16) == NULL, "#newDefaultItem returns NULL when name is empty");

  char invalidName[22] = { [0 ... 20] = 'a', '\0' };
  assert(newDefaultItem(invalidName, 16) == NULL, "#newDefaultItem returns NULL when name is bigger than MAX_STR_LENGTH");
}
