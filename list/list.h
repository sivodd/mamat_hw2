#ifndef _LIST_H_
#define _LIST_H_
#include "defs.h"

typedef struct List{
	PNode iterator;
	void* head;
	void* tail;
	void* (*CLONE_FUNC)(void*);
	Result (*DESTROY_FUNC)(void*);
	Result (*COMPARE_FUNC)(void*, void*);
	void* (*PRINT_FUNC)(void*);
} List, *PList;

typedef struct Node{
	void* Pobject;
	struct Node* next;
}Node, *PNode;

PList ListCreate(void* clonaFunc, Result destroyFunc, Result compareFunc, void* printFunc);
void ListDestroy(PList list);
Result ListAdd(PList list, void* new_object);
Result ListRemove(PList list, void* node);
PNode ListGetFirst(PList list);
PNode ListGetNext(PList list);
BOOL ListCompare(PList list1, PList list2);
void ListPrint(PList list);

#endif
