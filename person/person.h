#ifndef _PERSON_H_
#define _PERSON_H_
#include "defs.h"
#include "list.h"
#include <stdlib.h>  


typedef struct Person{
	char* name;
	int age;
	int ID;
} Person, *PPerson;

PPerson PersonCreate(char* name, int age, int ID);
void printPerson(void* person);
void* clonePerson(void* original_person);
void destroyPerson(void* person);
BOOL comparePersons(void* person1, void* person2);

//Person* PersonCreate(char* name, int age, int ID);
//void printPerson(PPerson person);
//PPerson clonePerson(PPerson original_person);
//void destroyPerson(PPerson person);
//Result comparePersons(PPerson person1, PPerson person2);

#endif
