#include <stdio.h>
#include "list.h"

PList ListCreate(void* cloneFunc, Result destroyFunc, Result compareFunc, void* printFunc)
{
	PList Plist = (PList)malloc(sizeof(List));
	if (Plist != NULL)
	{
		PNode iterator = NULL;
		Plist->head = NULL;
		Plist->tail = NULL;
		Plist->iterator = NULL;
		Plist->CLONE_FUNC = cloneFunc;
		Plist->DESTROY_FUNC = destroyFunc;
		Plist->COMPARE_FUNC = compareFunc;
		Plist->PRINT_FUNC = printFunc;
	}
	return Plist;
}

void ListDestroy(PList list)
{
	PNode cur_node = ListGetFirst(list);
	while (cur_node!=NULL)
	{
		list->DESTROY_FUNC(cur_node->Pobject);
		PNode temp = ListGetNext(list);
		free(cur_node);
		cur_node = temp;
	}
	free(list);
}

Result ListAdd(PList list, void* new_object)
{
	PNode new_node = (PNode)malloc(sizeof(Node));
	void* object = list->CLONE_FUNC(new_object);
	if (new_node == NULL || object == NULL)
	{
		free(new_node);
		free(object);
		return FAIL;
	}
	new_node->Pobject = object;
	if (list->tail == NULL)//if its the first object
		list->tail = list->head = new_node;
	else
		((PNode)(list->tail))->next = list->tail =  new_node;
	return SUCCESS;
}

Result ListRemove(PList list, void* object)
{
	//Transfer the iterators to the first object
	void* cur_object = ListGetFirst(list);
	//serching the object in the list
	while (cur_object != NULL && !list->COMPARE_FUNC(object, cur_object))
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

PNode ListGetFirst(PList list)
{
	list->iterator = list->head;
	return ((PNode)(list->head))->Pobject;
}

PNode ListGetNext(PList list)
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
	if (!list1->COMPARE_FUNC(ListGetFirst(list1), ListGetFirst(list2)))
		return FALSE;
	//iterate over the lists and compare the objects;
	while (ListGetNext(list1)!=NULL && ListGetNext(list2)!=NULL)
	{
		void* object1 = ((PNode)(list1->iterator))->Pobject;
		void* object2 = ((PNode)(list2->iterator))->Pobject;
		if (!list1->COMPARE_FUNC(object1, object2))
			return FALSE;
	}
	return TRUE;
}

void ListPrint(PList list)
{
	PNode cur_node = ListGetFirst(list);
	while (cur_node!=NULL)
	{
		list->PRINT_FUNC(cur_node->Pobject);
		cur_node = ListGetNext(list);
	}
	printf("\n");
}