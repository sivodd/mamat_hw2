#include <stdio.h>
#include "person.h"
#include "list.h"

Person* PersonCreate(char* name, int age, int ID)
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

void printPerson(PPerson person)
{
	printf("Name: %s, ID: %d, Age: %d\n", person->name, person->ID, person->age);
}

PPerson clonePerson(PPerson original_person)
{
	PPerson new_person = PersonCreate(original_person->name, original_person->age, original_person->ID);
	if (new_person == NULL)
		return NULL;
	return new_person;
}

void destroyPerson(PPerson person)
{
	free(person);
}

Result comparePersons(PPerson person1, PPerson person2)
{
	if (person1->ID == person2->ID)
		return TRUE;
	return FALSE;
}