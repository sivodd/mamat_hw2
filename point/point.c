#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"

// i use this already in PointAddList
// PCoordinate CoordinateClone(PCoordinate pCoordinate){
//    PCoordinate new_pCoordinate=(PCoordinate)malloc(sizeof(Coordinate));
//    if (new_pCoordinate == NULL)
//        return NULL;
//    new_pCoordinate->coordinate_value=pCoordinate->coordinate_value;
//    return new_pCoordinate;
//}

//*************************************************************************************
//* Function name : CoordinateDestroy
//* Description   : Given a pointer it will free the mem to the coordinate.
//* Parameters    : pCoordinate - a pointer to a coordinate.
//* Return value  : None.
//*************************************************************************************
void CoordinateDestroy(PCoordinate pCoordinate){
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
    pPoint->dimension=dimension;
    pPoint->size=0;
    pPoint->coordinate_list= ListCreate(NULL, CoordinateDestroy, CoordinateCompare, CoordinatePrint);
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
    if (pPoint->size==pPoint->dimension)
        return FAIL;
    PCoordinate pCoordinate=(PCoordinate)malloc(sizeof(Coordinate));
    if (pCoordinate==NULL)
        return FAIL;
    pCoordinate->coordinate_value=coordinate;
    ListAdd(pPoint->coordinate_list,pCoordinate);
    if (ListAdd(pPoint->coordinate_list,pCoordinate)==FAIL)
        return FAIL;
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
    PPoint new_pPoint=PointCreate(pPoint->dimension);
    if (new_pPoint == NULL)
        return NULL;
    new_pPoint->size=pPoint->size;
    new_pPoint->coordinate_list=pPoint->coordinate_list;
    int curr_coor=PointGetFirstCoordinate(pPoint);
    while (curr_coor!=0){
        PointAddCoordinate(new_pPoint, curr_coor);
        if (PointAddCoordinate(new_pPoint, curr_coor)==NULL)
            return NULL;
        curr_coor=PointGetNextCoordinate(pPoint);
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
int PointDistance(PPoint pPoint1, PPoint pPoint2){ //maybe we should use a static here
//    make sure this function can't get empty points/
    int result=0;
    int coor_value=0;
    PPoint result_point=PointCreate(pPoint1->dimension);
    if (result_point==NULL)
        return NULL;
    coor_value=PointGetFirstCoordinate(pPoint1);
    if (coor_value==0)
        return NULL; //if there a point is empty will not get distance.
    result=(int)pow((PointGetFirstCoordinate(pPoint1)-PointGetFirstCoordinate(pPoint2)),2);
    while (coor_value!=0){
        if (PointAddCoordinate(result_point, result)==FAIL)
            return NULL;
        result+=(int)pow((PointGetNextCoordinate(pPoint1)-PointGetNextCoordinate(pPoint2)),2);
        coor_value=((PCoordinate)(pPoint1->coordinate_list->iterator->Pobject))->coordinate_value;
    }
    free(result_point);
    return result;
}
