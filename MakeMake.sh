#!/bin/bash
#######################################################################################################
## Function name: MakeMake
## Function description: Creates a makefile with the given parameters
## Parameters: $1 - compiler name
##	       $2 - program name
##             $3 - the file type ending we want to compile
## Return value: None.
#######################################################################################################

# This is a Makefile for the $1 project

if [ "$1" == "gcc" ]; then

    echo "CC = $1" >>Makefile
    echo "CFLAGS = -g -Wall" >> Makefile
    echo "CCLINK = \$(CC)" >> Makefile
    echo "LIBS = " >> Makefile

    echo "OBJS = main.o list.o person.o point.o cluster.o" >> Makefile
    echo "RM = rm -f" >> Makefile

    # Creating the executable 
    echo "$2: \$(OBJS)" >>Makefile
    echo -e "\t\$(CCLINK) -o $2 \$(OBJS) \$(LIBS)" >> Makefile

    # Creating object files using default rules
    $1 -MM *$3 >> Makefile

    echo "clean:" >>Makefile
    echo -e "\t\$(RM) $2 *.o" >> Makefile

elif [ "$1" == "g++" ]; then

    echo "CXX = $1" >>Makefile
    echo "CXXFLAGS = -g -Wall" >> Makefile
    echo "CXXLINK = \$(CCC)" >> Makefile
    echo "LIBS = " >> Makefile

    echo "OBJS = main.o list.o person.o point.o cluster.o" >> Makefile
    echo "RM = rm -f" >> Makefile

    # Creating the executable
    echo "$2: \$(OBJS)" >>Makefile
    echo -e "\t\$(CXXLINK) -o $2 \$(OBJS) \$(LIBS)" >> Makefile

    # Creating object files using default rules
    $1 -MM *$3 >> Makefile

    echo "clean:" >>Makefile
    echo -e "\t\$(RM) $2 *.o" >> Makefile
fi

