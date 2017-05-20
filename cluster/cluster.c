#include <stdio.h>
#include <stdlib.h>

#include "cluster.h"


PCluster ClusterCreate(int dimension){
    PCluster pCluster=(PCluster)malloc(sizeof(Cluster));
    if (pCluster==NULL)
        return NULL;
    pCluster->dimension=dimension;
    pCluster->point_list= ListCreate(PointClone, PointDestroy, PointCompare, PointPrint);
    if (pCluster->point_list==NULL)
        return NULL;
    return pCluster;
}
void ClusterDestroy(PCluster pCluster){
    PointDestroy(pCluster->point_list);
    free(pCluster);
}

Result ClusterAddPoint(PCluster pCluster, PPoint pPoint){
    if (pPoint->dimension!=pCluster->dimension)
        return FAIL;
    PPoint pPoint_curr=ListGetFirst(pCluster->point_list);
    while(pPoint_curr!=NULL){
        if (ListCompare(pPoint_curr->coordinate_list, pPoint->coordinate_list))
            return FAIL;
        else ListGetNext(pCluster->point_list);
    }
    PPoint new_point=PointClone(pPoint);
    if (new_point==NULL)
        return FAIL;
    ListAdd(pCluster->point_list,new_point);
}

int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint){
    int min_d=100;
    int d=0;
//    not sure what is the max distance possible
    PPoint pPoint_curr=ListGetFirst(pCluster->point_list);
    while (pPoint_curr!=NULL){
        d=PointDistance(pPoint_curr, pPoint);
        if (d<min_d)
            min_d=d;
        pPoint_curr=ListGetNext(pCluster->point_list);
    }
    return min_d;
}


void ClusterPrint(PCluster pCluster){
    int MinSqDist=1000;
    int d=0
    PPoint pPoint_curr1=ListGetFirst(pCluster->point_list);
    PPoint pPoint_curr2=ListGetNext(pCluster->point_list);
    while (pPoint_curr1!=NULL){
        while (pPoint_curr2!=NULL){
            d=PointDistance(pPoint_curr1,pPoint_curr2);
            if (d<MinSqDist)
                MinSqDist=d;
            pPoint_curr2=((PNode*)(pPoint_curr2))->
        }
    }



    printf("Cluster's dimension: %d\n", pCluster->dimension);
    ListPrint(pCluster->point_list);

    printf("\n\nMinimum Square Distance:  ")
}
