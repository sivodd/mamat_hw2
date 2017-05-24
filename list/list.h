#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include "defs.h"



//*type defintions*//
typedef void* Pobject;

//*Function types*//
typedef void* (*CLONE_FUNC)(Pobject);
typedef void (*DESTROY_FUNC)(Pobject);
typedef BOOL (*COMPARE_FUNC)(Pobject, Pobject);
typedef void* (*PRINT_FUNC)(Pobject);

typedef struct Node {
	void* Pobject;
	struct Node* next;
}Node, *PNode;

typedef struct List{
	PNode iterator;
	void* head;
	void* tail;
	CLONE_FUNC CloneFunc;
	DESTROY_FUNC DestroyFunc;
	COMPARE_FUNC CompareFunc;
	PRINT_FUNC PrintFunc;
} List, *PList;

PList ListCreate(CLONE_FUNC cloneFunc, DESTROY_FUNC destroyFunc, COMPARE_FUNC compareFunc, PRINT_FUNC printFunc);
void ListDestroy(PList list);
Result ListAdd(PList list, void* new_object);
Result ListRemove(PList list, void* node);
void* ListGetFirst(PList list);
void* ListGetNext(PList list);
BOOL ListCompare(PList list1, PList list2);
void ListPrint(PList list);

#endif
