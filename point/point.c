#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"

//void CoordinateClone(PCoordinate pCoordinate)
void CoordinateDestroy(PCoordinate pCoordinate){
    free(pCoordinate);
}
BOOL CoordinateCompare(PCoordinate pCoordinate1, PCoordinate pCoordinate2){
    if (pCoordinate1->coordinate_value==pCoordinate2->coordinate_value)
        return TRUE;
    else return FALSE;
}

void CoordinatePrint(PCoordinate pCoordinate){
    printf("%d ", pCoordinate->coordinate_value);
}


void* PointCreate(int dimension){
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

void PointDestroy(PPoint pPoint){
    ListDestroy(pPoint->coordinate_list);
    free(pPoint);
}

Result PointAddCoordinate(PPoint pPoint, int coordinate){
    if (pPoint->size==pPoint->dimension)
        return FAIL;
    PCoordinate pCoordinate=(PCoordinate)malloc(sizeof(Coordinate));
    if (pCoordinate==NULL)
        return FAIL;
    pCoordinate->coordinate_value=coordinate;
    ListAdd(pPoint->coordinate_list,pCoordinate);
    pPoint->size++;

}

int PointGetFirstCoordinate(PPoint pPoint){
    PCoordinate first=ListGetFirst(pPoint->coordinate_list);
    if (first==NULL)
        return 0;
    else return first->coordinate_value;
}

int PointGetNextCoordinate(PPoint pPoint){
    PCoordinate next=ListGetNext(pPoint->coordinate_list);
    if (next==NULL)
        return 0;
    else return next->coordinate_value;
}

void PointPrint(PPoint pPoint){
    int size=pPoint->size;
    int dim=pPoint->dimension;
    printf("Point Dimension: %d, Size: %d, Coordinates: ", dim ,size);
    ListPrint(pPoint->coordinate_list);
}

PPoint ClonePoint(PPoint pPoint);

BOOL PointCompare(PPoint pPoint1, PPoint pPoint2){
    if (ListCompare(pPoint1->coordinate_list,pPoint2->coordinate_list))
        return TRUE;
    else return FALSE;
}


int PointDistance(PPoint pPoint1, PPoint pPoint2){
//    make sure this function can't get empty points/
    int i=0;
    int sum=0;
    double result_arr[pPoint1->dimension]={0};
    result_arr[0]=pow((PointGetFirstCoordinate(pPoint1)-PointGetFirstCoordinate(pPoint2)),2);
    sum=(int)result_arr[0];
    for (i=1;i<pPoint1->dimension;i++){
        result_arr[i]=pow((PointGetNextCoordinate(pPoint1)-PointGetNextCoordinate(pPoint2)),2);
        sum+=(int)result_arr[i];
    }

    return sum;
}
