#ifndef _PERSON_H_
#define _PERSON_H_
#include "defs.h"

typedef struct Person{
	char* name;
	int age;
	int ID;
} Person, *PPerson;

Person* PersonCreate(char* name, int age, int ID);
void printPerson(PPerson person);
PPerson clonePerson(PPerson original_person);
void destroyPerson(PPerson person);
Result comparePersons(PPerson person1, PPerson person2);

#endif
