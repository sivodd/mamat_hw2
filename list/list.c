#include <stdio.h>
#include "list.h"

PList ListCreate(CLONE_FUNC cloneFunc, DESTROY_FUNC destroyFunc, COMPARE_FUNC compareFunc, PRINT_FUNC printFunc)
{
	PList Plist = (PList)malloc(sizeof(List));
	if (Plist != NULL)
	{
		Plist->iterator = NULL;
//        sivan- changed this to also be Plist->iterator
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
	Node* temp  = NULL;
	//tranfer the iterator to the begining of the list 
	void* cur_object = ListGetFirst(list);
	//iterate the list and free all the nodes and objects
	while (list->iterator!=NULL)
	{
		list->DestroyFunc(cur_object);
		temp = list->iterator;
		cur_object = ListGetNext(list);
		free(temp);
	}
	free(list);
}

Result ListAdd(PList list, void* added_object)
{
	PNode new_node = (PNode)malloc(sizeof(Node));
	void* object = list->CloneFunc(new_object);
	//if one of the alloc not succeeded
	if (new_node == NULL || object == NULL)
	{
//		not sure you can free null maybe change this to two different if's //sivan
		free(new_node);
		free(object);
		return FAIL;
	}
	//attaching the object to the node
	new_node->Pobject = object;
	//adding the node to the list
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
	//Node* pre_node = NULL;
	//serching the object in the list
	while (cur_object != NULL && !list->CompareFunc(object, cur_object))
	{
		//pre_node = list->iterator;
		cur_object = ListGetNext(list);
	}
	//If the object is found
	if (cur_object != NULL)
	{
		list->DestroyFunc(cur_object); 
		
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

void deleteNode(PList list, Node* node)
{
	Node* pre_node = NULL;
	Node* cur_node = list->head;
	while (cur_node!=node)
	{
		pre_node = cur_node;
		cur_node = cur_node->next;
	}
	//if its the first object
	if (pre_node == NULL)
		list->head = cur_node->next;
	//if its not the first object
	else
		pre_node->next = cur_node->next;
	//if its the last object
	if (cur_node->next == NULL)
		list->tail = pre_node;
	//if the iterator pointing to the node that going to be deleted
	if (cur_node = list->iterator)
		list->iterator = cur_node->next;
	//free the node 
	free(cur_node);
}