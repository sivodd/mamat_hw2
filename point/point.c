#include <stdio.h>
#include <stdlib.h>
#include "point.h"

// i use this already in PointAddList not sure what it's good for
 void* CoordinateClone(void* pCoordinate){
	PCoordinate c_pCoordinate = (PCoordinate)pCoordinate;
    PCoordinate new_pCoordinate=(PCoordinate)malloc(sizeof(Coordinate));
    if (new_pCoordinate == NULL)
        return NULL;
    new_pCoordinate->coordinate_value=c_pCoordinate->coordinate_value;
    return new_pCoordinate;
}

//*************************************************************************************
//* Function name : CoordinateDestroy
//* Description   : Given a pointer it will free the mem to the coordinate.
//* Parameters    : pCoordinate - a pointer to a coordinate.
//* Return value  : None.
//*************************************************************************************
void CoordinateDestroy(void* pCoordinate){
	PCoordinate c_pCoordinate = (PCoordinate)pCoordinate;
    if (c_pCoordinate!=NULL)
        free(c_pCoordinate);
}

//*************************************************************************************
//* Function name : CoordinateCompare
//* Description   : Given two pointers it will compare both coordinate's values and will
//                  return TRUE if they are the same and FALSE otherwise.
//* Parameters    : pCoordinate1 / pCoordinate12 - a pointer to the coordinates we want
//                  to compare.
//* Return value  : TRUE / FALSE.
//*************************************************************************************
BOOL CoordinateCompare(void* pCoordinate1, void* pCoordinate2){
	PCoordinate c_pCoordinate1 = (PCoordinate)pCoordinate1;
	PCoordinate c_pCoordinate2 = (PCoordinate)pCoordinate2;
	if (c_pCoordinate1->coordinate_value==c_pCoordinate2->coordinate_value)
        return TRUE;
    else return FALSE;
}

//*************************************************************************************
//* Function name : CoordinatePrint
//* Description   : Given a pointer it will print the value of the coordinate.
//* Parameters    : pCoordinate - a pointer to a coordinate.
//* Return value  : None.
//*************************************************************************************
void CoordinatePrint(void* pCoordinate){
	PCoordinate c_pCoordinate = (PCoordinate)pCoordinate;
    printf("%d ", c_pCoordinate->coordinate_value);
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
	if (pPoint->coordinate_list == NULL)
	{
		free(pPoint);
		return NULL;
	}
    return pPoint;
}

//*************************************************************************************
//* Function name : PointDestroy
//* Description   : Given a pointer it will free the mem of the point struct.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : None.
//*************************************************************************************
void PointDestroy(void* pPoint){
	PPoint c_pPoint = (PPoint)pPoint;
	if (c_pPoint != NULL)
	{
		ListDestroy(c_pPoint->coordinate_list);
		free(c_pPoint);	
	}
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
	if (pPoint->size == pPoint->dimension)
		return FAIL;
    PCoordinate pCoordinate=(PCoordinate)malloc(sizeof(Coordinate));
    if (pCoordinate==NULL)
        return FAIL;
//  assigning the coordinates value and adding it to the list of the point
    pCoordinate->coordinate_value=coordinate;
	if (ListAdd(pPoint->coordinate_list, pCoordinate) == FAIL)
	{
		free(pCoordinate); //omer
		return FAIL;
	}
    free(pCoordinate);
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
void PointPrint(void* pPoint){
	PPoint c_pPoint = (PPoint)pPoint;
    int size=c_pPoint->size;
    int dim=c_pPoint->dimension;
    printf("Point Dimension: %d, Size: %d, Coordinates: ", dim ,size);
    ListPrint(c_pPoint->coordinate_list);
}
//*************************************************************************************
//* Function name : PointClone
//* Description   : Makes a clone to a Given a point.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : None.
//*************************************************************************************
void* PointClone(void* pPoint){
	PPoint c_pPoint = (PPoint)pPoint;
    PPoint new_pPoint=(PPoint)malloc(sizeof(Point));
    if (new_pPoint == NULL)
        return NULL;
//  assigning all pPoint values to the new point
    new_pPoint->size=c_pPoint->size;
    new_pPoint->coordinate_list=ListClone(c_pPoint->coordinate_list);
    new_pPoint->dimension=c_pPoint->dimension;
    return new_pPoint;
}

//*************************************************************************************
//* Function name : PointCompare
//* Description   : Compers the two points. returns TRUE if they are the same and FALSE
//                  otherwise.
//* Parameters    : pPoint1 / pPoint2 - pointers to the points we want to compare.
//* Return value  : TRUE / FALSE.
//*************************************************************************************
BOOL PointCompare(void* pPoint1, void* pPoint2){
	PPoint c_pPoint1 = (PPoint)pPoint1;
	PPoint c_pPoint2 = (PPoint)pPoint2;
    if (ListCompare(c_pPoint1->coordinate_list,c_pPoint2->coordinate_list))
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
//what if this gets empty points?
//  result will add up the distance between the two points for each coordinate
    int result=0;
    int size=0;
    int point1_value=0;
    int point2_value=0;
    if (pPoint1->size==0 || PointCompare(pPoint1,pPoint2))
        return 0; //if the point is empty will not get distance.
    point1_value=PointGetFirstCoordinate(pPoint1);
    point2_value=PointGetFirstCoordinate(pPoint2);
    result=(point1_value-point2_value)*(point1_value-point2_value);
    size=1;
//  make sure we did'nt get to the end of the point
    while (size<pPoint1->size){
        point1_value=PointGetNextCoordinate(pPoint1);
        point2_value=PointGetNextCoordinate(pPoint2);
        result+=(point1_value-point2_value)*(point1_value-point2_value);
        size++;
    }
    return result;
}
