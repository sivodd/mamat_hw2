#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"

typedef struct point{
    PList coordinate_list;
    int dimension;
    int size;
}Point, *PPoint;

typedef struct coordinate{
    int coordinate_value;
}Coordinate, *PCoordinate;


PCoordinate CoordinateClone(PCoordinate pCoordinate);
void CoordinateDestroy(PCoordinate pCoordinate);
BOOL CoordinateCompare(PCoordinate pCoordinate1, PCoordinate pCoordinate2);
void CoordinatePrint(PCoordinate pCoordinate);

void* PointCreate(int dimension_size);
void PointDestroy(PPoint pPoint);
Result PointAddCoordinate(PPoint pPoint, int coordinate);
int PointGetFirstCoordinate(PPoint pPoint);
int PointGetNextCoordinate(PPoint pPoint);
void PointPrint(PPoint pPoint);
PPoint PointClone(PPoint pPoint);
BOOL PointCompare(PPoint pPoint1, PPoint pPoint2);
int PointDistance(PPoint pPoint1, PPoint pPoint2);


#endif
