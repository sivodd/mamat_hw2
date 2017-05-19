#include <stdio.h>
#include "list.h"

PList ListCreate(CLONE_FUNC cloneFunc, DESTROY_FUNC destroyFunc, COMPARE_FUNC compareFunc, PRINT_FUNC printFunc)
{
	PList Plist = (PList)malloc(sizeof(List));
	if (Plist != NULL)
	{
		PNode iterator = NULL;
		Plist->head = NULL;
		Plist->tail = NULL;
		Plist->iterator = NULL;
		Plist->CloneFunc = cloneFunc;
		Plist->DestroyFunc = destroyFunc;
		Plist->CompareFunc = compareFunc;
		Plist->PrintFunc = printFunc;
	}
	return Plist;
}

void ListDestroy(PList list)
{
	PNode cur_node = ListGetFirst(list);
	while (cur_node!=NULL)
	{
		list->DestroyFunc(cur_node->Pobject);
		PNode temp = ListGetNext(list);
		free(cur_node);
		cur_node = temp;
	}
	free(list);
}

Result ListAdd(PList list, void* new_object)
{
	PNode new_node = (PNode)malloc(sizeof(Node));
	void* object = list->CloneFunc(new_object);
	if (new_node == NULL || object == NULL)
	{
		free(new_node);
		free(object);
		return FAIL;
	}
	new_node->Pobject = object;
	new_node->next = NULL;
	if (list->tail == NULL)//if its the first object
		list->tail = list->head = new_node;
	else
	{
		((PNode)(list->tail))->next = new_node;
		list->tail = new_node;
	}
	return SUCCESS;
}

Result ListRemove(PList list, void* object)
{
	//Transfer the iterators to the first object
	void* cur_object = ListGetFirst(list);
	//serching the object in the list
	while (cur_object != NULL && !list->CompareFunc(object, cur_object))
	{
		cur_object = ListGetNext(list);
	}
	//If the object is found
	if (cur_object != NULL)
	{
		free(cur_object);
		PNode temp = ((PNode)(list->iterator))->next;
		free(list->iterator);
		list->iterator = temp;
		return SUCCESS;
	}
	//If the object is not found
	return FAIL;
}

void* ListGetFirst(PList list)
{
	list->iterator = list->head;
	if (list->iterator == NULL)
		return NULL;
	return ((PNode)(list->head))->Pobject;
}

void* ListGetNext(PList list)
{
	if (list->iterator == NULL || ((PNode)(list->iterator))->next == NULL)
	{
		list->iterator = NULL;
		return NULL;
	}
	list->iterator = ((PNode)(list->iterator))->next;
	return ((PNode)(list->iterator))->Pobject;
}

BOOL ListCompare(PList list1, PList list2)
{
	//Transfer the iterators to the first object and compare the first objects
	if (!list1->CompareFunc(ListGetFirst(list1), ListGetFirst(list2)))
		return FALSE;
	//iterate over the lists and compare the objects;
	while (ListGetNext(list1)!=NULL && ListGetNext(list2)!=NULL)
	{
		void* object1 = ((PNode)(list1->iterator))->Pobject;
		void* object2 = ((PNode)(list2->iterator))->Pobject;
		if (!list1->CompareFunc(object1, object2))
			return FALSE;
	}
	return TRUE;
}

void ListPrint(PList list)
{
	void* cur_object = ListGetFirst(list);
	while (cur_object !=NULL)
	{
		list->PrintFunc(cur_object);
		cur_object = ListGetNext(list);
	}
	printf("\n");
}