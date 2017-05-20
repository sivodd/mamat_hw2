#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    ListDestroy(pCluster->point_list);
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
    return SUCCESS;
}

int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint){
    int min_d=INFINITY;
    int d=0;
    PPoint pPoint_curr=ListGetFirst(pCluster->point_list);
    while (pPoint_curr!=NULL){
        d=PointDistance(pPoint_curr, pPoint);
        if (d<min_d && d!=0) //check that it dose'nt measure dist from it self.
            min_d=d;
        pPoint_curr=ListGetNext(pCluster->point_list);
    }
    return min_d;
}


void ClusterPrint(PCluster pCluster){
    int MinSqDist=INFINITY;
    int d=0;
    PPoint pPoint_curr=ListGetFirst(pCluster->point_list);
    PNode iter_tmp=pCluster->point_list->iterator;
    while (pPoint_curr!=NULL){
        d=ClusterGetMinDistance(pCluster, pPoint_curr);
        if (d<MinSqDist)
            MinSqDist=d;
        pCluster->point_list->iterator=iter_tmp;
        pPoint_curr=ListGetNext(pCluster->point_list);
        iter_tmp=iter_tmp->next;
        }
    printf("Cluster's dimension: %d\n", pCluster->dimension);
    ListPrint(pCluster->point_list);
    printf("\n\nMinimum Square Distance: %d", MinSqDist);
}
