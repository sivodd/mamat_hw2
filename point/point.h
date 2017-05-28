#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"
#include <stdlib.h>

typedef struct point{
    PList coordinate_list;
    int dimension;
    int size;
}Point, *PPoint;

typedef struct coordinate{
    int coordinate_value;
}Coordinate, *PCoordinate;


//PCoordinate CoordinateClone(PCoordinate pCoordinate);
void* CoordinateClone(void* pCoordinate);

//*************************************************************************************
//* Function name : CoordinateDestroy
//* Description   : Given a pointer it will free the mem to the coordinate.
//* Parameters    : pCoordinate - a pointer to a coordinate.
//* Return value  : None.
//*************************************************************************************
void CoordinateDestroy(void* pCoordinate);

//*************************************************************************************
//* Function name : CoordinateCompare
//* Description   : Given two pointers it will compare both coordinate's values and will
//                  return TRUE if they are the same and FALSE otherwise.
//* Parameters    : pCoordinate1 / pCoordinate12 - a pointer to the coordinates we want
//                  to compare.
//* Return value  : TRUE / FALSE.
//*************************************************************************************
BOOL CoordinateCompare(void* pCoordinate1, void* pCoordinate2);

//*************************************************************************************
//* Function name : CoordinatePrint
//* Description   : Given a pointer it will print the value of the coordinate.
//* Parameters    : pCoordinate - a pointer to a coordinate.
//* Return value  : None.
//*************************************************************************************
void CoordinatePrint(void* pCoordinate);

//*************************************************************************************
//* Function name : PointCreate
//* Description   : Given a dimension size it will create a point struct of that
//                  dimension.
//* Parameters    : dimension_size - a dimension of a point.
//* Return value  : PPoint - A Pointer to a point.
//*************************************************************************************
PPoint PointCreate(int dimension_size);

//*************************************************************************************
//* Function name : PointDestroy
//* Description   : Given a pointer it will free the mem of the point struct.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : None.
//*************************************************************************************
void PointDestroy(void* pPoint);

//*************************************************************************************
//* Function name : PointAddCoordinate
//* Description   : Given a pointer and a coordinate value it will add a new coordinate
//                  to the point's coordinate list
//* Parameters    : pPoint - a pointer to a point.
//                  coordinate - coordinate value.
//* Return value  : FAIL / SUCCESS.
//*************************************************************************************
Result PointAddCoordinate(PPoint pPoint, int coordinate);

//*************************************************************************************
//* Function name : PointGetFirstCoordinate
//* Description   : Given a pointer to a point it will return the first coordinate.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : coordinate value.
//*************************************************************************************
int PointGetFirstCoordinate(PPoint pPoint);

//*************************************************************************************
//* Function name : PointGetNextCoordinate
//* Description   : Given a pointer to a point it will return next coordinate the
//                  iterator is on.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : coordinate value.
//*************************************************************************************
int PointGetNextCoordinate(PPoint pPoint);

//*************************************************************************************
//* Function name : PrintPoint
//* Description   : Print the point content given a pointer to the point.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : None.
//*************************************************************************************
void PointPrint(void* pPoint);

//*************************************************************************************
//* Function name : PointClone
//* Description   : Makes a clone to a Given a point.
//* Parameters    : pPoint - a pointer to a point.
//* Return value  : None.
//*************************************************************************************
void* PointClone(void* pPoint);

//*************************************************************************************
//* Function name : PointCompare
//* Description   : Compers the two points. returns TRUE if they are the same and FALSE
//                  otherwise.
//* Parameters    : pPoint1 / pPoint2 - pointers to the points we want to compare.
//* Return value  : TRUE / FALSE.
//*************************************************************************************
BOOL PointCompare(void* pPoint1, void* pPoint2);

//*************************************************************************************
//* Function name : PointDistance
//* Description   : Calculates the distance between twa given points.
//* Parameters    : pPoint1 / pPoint2 - pointers to the points we want to measure.
//* Return value  : Distance number - how far they are from each other.
//*************************************************************************************
int PointDistance(PPoint pPoint1, PPoint pPoint2);


#endif
