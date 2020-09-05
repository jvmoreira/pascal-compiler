#ifndef __DEFAULT_ITEM__
#define __DEFAULT_ITEM__

DefaultItem newDefaultItem(String name, int value);

DefaultItem extractDefaultItem(StackItem item);

void destroyDefaultItem(DefaultItem item);

#endif
