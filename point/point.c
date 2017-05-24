#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"

// i use this already in PointAddList not sure what it's good for
 PCoordinate CoordinateClone(PCoordinate pCoordinate){
    PCoordinate new_pCoordinate=(PCoordinate)malloc(sizeof(Coordinate));
    if (new_pCoordinate == NULL)
        return NULL;
    new_pCoordinate->coordinate_value=pCoordinate->coordinate_value;
    return new_pCoordinate;
}

//*************************************************************************************
//* Function name : CoordinateDestroy
//* Description   : Given a pointer it will free the mem to the coordinate.
//* Parameters    : pCoordinate - a pointer to a coordinate.
//* Return value  : None.
//*************************************************************************************
void CoordinateDestroy(PCoordinate pCoordinate){
    if (pCoordinate!=NULL)
        free(pCoordinate);
}

//*************************************************************************************
//* Function name : CoordinateCompare
//* Description   : Given two pointers it will compare both coordinate's values and will
//                  return TRUE if they are the same and FALSE otherwise.
//* Parameters    : pCoordinate1 / pCoordinate12 - a pointer to the coordinates we want
//                  to compare.
//* Return value  : TRUE / FALSE.
//*************************************************************************************
BOOL CoordinateCompare(PCoordinate pCoordinate1, PCoordinate pCoordinate2){
    if (pCoordinate1->coordinate_value==pCoordinate2->coordinate_value)
        return TRUE;
    else return FALSE;
}

//*************************************************************************************
//* Function name : CoordinatePrint
//* Description   : Given a pointer it will print the value of the coordinate.
//* Parameters    : pCoordinate - a pointer to a coordinate.
//* Return value  : None.
//*************************************************************************************
void CoordinatePrint(PCoordinate pCoordinate){
    printf("%d ", pCoordinate->coordinate_value);
}

//*************************************************************************************
//* Function name : PointCreate
//* Description   : Given a dimension size it will create a point struct of that
//                  dimension.
//* Parameters    : dimension_size - a dimension of a point.
//* Return value  : PPoint - A Pointer to a point.
//*************************************************************************************
PPoint PointCreate(int dimension){
    PPoint pPoint=(PPoint)malloc(sizeof(Point));
    if (pPoint==NULL)
        return NULL;
//  Assigning values to point
    pPoint->dimension=dimension;
    pPoint->size=0;
    pPoint->coordinate_list= ListCreate(CoordinateClone, CoordinateDestroy, CoordinateCompare, CoordinatePrint);
//  if the memory assignment fails
    if (pPoint->coordinate_list==NULL)
        return NULL;
    return pPoint;
}

//*************************************************************************************
//* Function name : PointDestroy
//* Description   : Given a pointer it will free the mem of the point struct.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : None.
//*************************************************************************************
void PointDestroy(PPoint pPoint){
    ListDestroy(pPoint->coordinate_list);
    free(pPoint);
}

//*************************************************************************************
//* Function name : PointAddCoordinate
//* Description   : Given a pointer and a coordinate value it will add a new coordinate
//                  to the point's coordinate list
//* Parameters    : pPoint - a pointer to a point.
//                  coordinate - coordinate value.
//* Return value  : FAIL / SUCCESS.
//*************************************************************************************
Result PointAddCoordinate(PPoint pPoint, int coordinate){
//  check if the point has the max amount of coordinates already
    if (pPoint->size==pPoint->dimension)
        return FAIL;
    PCoordinate pCoordinate=(PCoordinate)malloc(sizeof(Coordinate));
    if (pCoordinate==NULL)
        return FAIL;
//  assigning the coordinates value and adding it to the list of the point
    pCoordinate->coordinate_value=coordinate;
    if (ListAdd(pPoint->coordinate_list,pCoordinate)==FAIL)
        return FAIL;
//  update the point size
    pPoint->size++;
    return SUCCESS;
}

//*************************************************************************************
//* Function name : PointGetFirstCoordinate
//* Description   : Given a pointer to a point it will return the first coordinate.
//                  if there isn't one it will return 0.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : coordinate value or 0 if there is no coordinate.
//*************************************************************************************
int PointGetFirstCoordinate(PPoint pPoint){
    PCoordinate first=ListGetFirst(pPoint->coordinate_list);
//  if the list function didn't find the first node return 0
    if (first==NULL)
        return 0;
    else return first->coordinate_value;
}

//*************************************************************************************
//* Function name : PointGetNextCoordinate
//* Description   : Given a pointer to a point it will returns the next coordinate the
//                  iterator is on. if there isn't one it will return 0.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : coordinate value or 0 if there is no coordinate.
//*************************************************************************************
int PointGetNextCoordinate(PPoint pPoint){
    PCoordinate next=ListGetNext(pPoint->coordinate_list);
    if (next==NULL)
        return 0;
    else return next->coordinate_value;
}

//*************************************************************************************
//* Function name : PrintPoint
//* Description   : Print the point content given a pointer to the point.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : None.
//*************************************************************************************
void PointPrint(PPoint pPoint){
    int size=pPoint->size;
    int dim=pPoint->dimension;
    printf("Point Dimension: %d, Size: %d, Coordinates: ", dim ,size);
    ListPrint(pPoint->coordinate_list);
}
//*************************************************************************************
//* Function name : PointClone
//* Description   : Makes a clone to a Given a point.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : None.
//*************************************************************************************
PPoint PointClone(PPoint pPoint){
//  creating memory for a new point where we will copy the old point to.
    PPoint new_pPoint=PointCreate(pPoint->dimension);
    if (new_pPoint == NULL)
        return NULL;
//  assigning the new points values
    new_pPoint->size=pPoint->size;
    new_pPoint->coordinate_list=pPoint->coordinate_list;
    int curr_coor=PointGetFirstCoordinate(pPoint);
    int new_size=1;
//  copy all coordinates until we get to the point size meaning we copied all coordinates
    while (new_size < pPoint->size){
        PointAddCoordinate(new_pPoint, curr_coor);
        if (PointAddCoordinate(new_pPoint, curr_coor)==NULL)
            return NULL;
//      moving the current coordinate to the next pPoint coordinate so it can be copied.
        curr_coor=PointGetNextCoordinate(pPoint);
        new_size++;
    }
    return new_pPoint;
}

//*************************************************************************************
//* Function name : PointCompare
//* Description   : Compers the two points. returns TRUE if they are the same and FALSE
//                  otherwise.
//* Parameters    : pPoint1 / pPoint2 - pointers to the points we want to compare.
//* Return value  : TRUE / FALSE.
//*************************************************************************************
BOOL PointCompare(PPoint pPoint1, PPoint pPoint2){
    if (ListCompare(pPoint1->coordinate_list,pPoint2->coordinate_list))
        return TRUE;
    else return FALSE;
}

//*************************************************************************************
//* Function name : PointDistance
//* Description   : Calculates the distance between twa given points.
//* Parameters    : pPoint1 / pPoint2 - pointers to the points we want to measure.
//* Return value  : Distance number - how far they are from each other.
//*************************************************************************************

int PointDistance(PPoint pPoint1, PPoint pPoint2){
// ???maybe we should use a static here
// ???make sure this function can't get empty points
//  result will add up the distance between the two points for each coordinate
    int result=0;
    int size=0;
//  ??? do we need to use coor_value=0??? coor_value=PointGetFirstCoordinate(pPoint1);
    if (pPoint1->size==0)
        return NULL; //if the point is empty will not get distance.
    result=(int)pow((PointGetFirstCoordinate(pPoint1)-PointGetFirstCoordinate(pPoint2)),2);
    size=1;
//  make sure we did'nt get to the end of the point
    while (size<pPoint1->size){
        result+=(int)pow((PointGetNextCoordinate(pPoint1)-PointGetNextCoordinate(pPoint2)),2);
    }

    return result;
}
