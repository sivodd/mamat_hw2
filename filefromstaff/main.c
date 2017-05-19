#include "list.h"
#include "point.h"
#include "cluster.h"
#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  char Line[MAX_LINE_SIZE];
  char* delimiters = " \t\n";
  char* Command;
  PList pPersonList=NULL;;
  PCluster pCluster=NULL;
  pPersonList=ListCreate(clonePerson,destroyPerson,comparePersons,printPerson);
  if(!pPersonList)
    {
      printf("ListCreate for Person Failed. Exiting.\n");
      exit(-1);
    }
  while (fgets(Line, MAX_LINE_SIZE, stdin))
    {
     
      Command = strtok(Line, delimiters);
      
      if (NULL == Command )
	{
	  continue;
	}
      if ( 0 == strcmp(Command, "Add_Person") )
	{
	  char* ID = strtok(NULL, delimiters);
	  char* name = strtok(NULL, delimiters);
	  char* age = strtok(NULL, delimiters);
	  PPerson pPerson = PersonCreate(name,atoi(age), atoi(ID));
          if(!ListAdd(pPersonList,pPerson))
	    {
	      printf("Add_Person Failed\n");
	    }
	  destroyPerson(pPerson); //Since PersonList holds a copy
	}
      if ( 0 == strcmp(Command, "Remove_Person") )
	{
	  char* ID = strtok(NULL, delimiters);
	  if(0==strcmp(ID, "All"))
	    {
	      ListDestroy(pPersonList);
	      pPersonList=ListCreate(clonePerson,destroyPerson,comparePersons,printPerson);
	      continue;
	    }
	  PPerson pPerson = PersonCreate("",0, atoi(ID));//name and age irelevant
          if(!ListRemove(pPersonList,pPerson))
	    {
	      printf("Remove_Person Failed\n");
	    }
	  destroyPerson(pPerson); //Since PersonList holds a copy
	}
      
      if ( 0 == strcmp(Command, "Start_Cluster") )
	{
	  char* Dim = strtok(NULL, delimiters);
	  
          if(!(pCluster=ClusterCreate(atoi(Dim))))
	    {
	      printf("Start_Cluster Failed. Exiting.\n");
	      exit(-1);
	    }
	}
      if ( 0 == strcmp(Command, "Clear_Cluster") )
	{
	  ClusterDestroy(pCluster);
	  pCluster=NULL;
	}
      if ( 0 == strcmp(Command, "Add_Point") )
	{
	  char* Dim = strtok(NULL, delimiters);
	  int n=atoi(Dim);
	  PPoint pPoint = PointCreate(n);
	  char* Coordinate = strtok(NULL, delimiters);
	  while(Coordinate)
	    {
	      if(!PointAddCoordinate(pPoint, atoi(Coordinate)))
		{
		  printf("Add Coordinate Failed.\n");	
		}
	      Coordinate = strtok(NULL, delimiters);
	    }	  
	  if(!ClusterAddPoint(pCluster,pPoint))
	    {
	      printf("Add_Point Failed.\n");	
	    }
	  PointDestroy(pPoint);
	}
      if ( 0 == strcmp(Command, "Print") )
	{
	  if(pPersonList)
	    {
	      ListPrint(pPersonList);
	    }
	   if(pCluster)
	     {
	       ClusterPrint(pCluster);
	     }
	}
    } // while(fgets(Line, MAX_LINE_SIZE, stdin))
  if(pPersonList)
    {
      ListDestroy(pPersonList);
    }
  if(pCluster)
    {
      ClusterDestroy(pCluster);
    }
  return 0;
}


