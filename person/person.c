#include <stdio.h>
#include "person.h"
#include <string.h>

PPerson PersonCreate(char* name, int age, int ID)
{
	PPerson person = (PPerson)malloc(sizeof(Person));
	if (person != NULL) 
	{
		person->name = strdup(name);
		person->age = age;
		person->ID = ID;
		return person;
	}
	free(person);
	return NULL;
}

void printPerson(void* person)
{
	PPerson c_person = (PPerson)person;
	printf("Name: %s, ID: %d, Age: %d\n", c_person->name, c_person->ID, c_person->age);
}

void* clonePerson(void* original_person)
{
	PPerson c_original_person = (PPerson)original_person;
	PPerson new_person = PersonCreate(c_original_person->name, c_original_person->age, c_original_person->ID);
	if (new_person == NULL)
		return NULL;
	return new_person;
}

void destroyPerson(void* person)
{
	PPerson c_person = (PPerson)person;
	free(c_person->name);
	free(c_person);
}

BOOL comparePersons(void* person1, void* person2)
{
	PPerson c_person1 = (PPerson)person1;
	PPerson c_person2 = (PPerson)person2;
	if (c_person1->ID == c_person2->ID)
		return TRUE;
	return FALSE;
}