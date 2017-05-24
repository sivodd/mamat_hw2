#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cluster.h"

//*************************************************************************************
//* Function name : ClusterCreate
//* Description   : Creates a new cluster given a dimension.
//* Parameters    : dimension - the dimension of the points in the cluster.
//* Return value  : PCluster - a pointer to the new cluster.
//*************************************************************************************
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

//*************************************************************************************
//* Function name : ClusterDestroy
//* Description   : Deletes the given cluster and frees it's memory.
//* Parameters    : pCluster - a pointer to a cluster.
//* Return value  : None.
//*************************************************************************************
void ClusterDestroy(PCluster pCluster){
    ListDestroy(pCluster->point_list);
    free(pCluster);
}

//*************************************************************************************
//* Function name : ClusterAddPoint
//* Description   : Adds the given point to the end of the given cluster's point list.
//* Parameters    : pCluster - a pointer to a cluster.
//                  pPoint - a pointer to a point.
//* Return value  : SUCCESS / FAIL
//*************************************************************************************
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint){
    if (pPoint->dimension!=pCluster->dimension)
        return FAIL;
    PPoint pPoint_curr=ListGetFirst(pCluster->point_list);
//    check if the point already exists in the cluster if so return fail.
    while(pPoint_curr!=NULL){
        if (ListCompare(pPoint_curr->coordinate_list, pPoint->coordinate_list))
            return FAIL;
        else ListGetNext(pCluster->point_list);
    }
//    put this in a comment because i think that add list dose this cloning.
//    PPoint new_point=PointClone(pPoint);
//    if (new_point==NULL)
//    return FAIL;
    ListAdd(pCluster->point_list,pPoint);
    return SUCCESS;
}

//*************************************************************************************
//* Function name : ClusterGetMinDistance
//* Description   : Calculates the minimum distance between a given point and a cluster.
//* Parameters    : pCluster - a pointer to a cluster.
//                  pPoint - a pointer to a point.
//* Return value  : minimum distance - number.
//*************************************************************************************
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint){
    int min_d=INFINITY;
    int d=0;
    PPoint pPoint_curr=ListGetFirst(pCluster->point_list);
//    loop on all points in cluster.
    while (pPoint_curr!=NULL){
        d=PointDistance(pPoint_curr, pPoint);
        //if the distance is smaller then the min distance and the point in the cluster
        // is no the same as pPoint
        if (d<min_d && d!=0)
            min_d=d;
        pPoint_curr=ListGetNext(pCluster->point_list);
    }
    return min_d;
}

//*************************************************************************************
//* Function name : ClusterPrint
//* Description   : Prints the cluster and the Minimum Square Distance.
//* Parameters    : pCluster - a pointer to a cluster.
//* Return value  : None.
//*************************************************************************************
void ClusterPrint(PCluster pCluster){
    int MinSqDist=INFINITY;
    int d=0;
    PPoint pPoint_curr=ListGetFirst(pCluster->point_list);
//  iter_temp will save the pointer to the iterator before we use a function that will move the iterator so
//  we can go back to starting point.
    PNode iter_tmp=pCluster->point_list->iterator;
    while (pPoint_curr!=NULL){
//      find the minimum distance between the current poin and the rest of the cluster.
        d=ClusterGetMinDistance(pCluster, pPoint_curr);
        if (d<MinSqDist)
            MinSqDist=d;
//      move the list iterator back to where current point is so we can find the next point in the list.
        pCluster->point_list->iterator=iter_tmp;
        pPoint_curr=ListGetNext(pCluster->point_list);
        iter_tmp=iter_tmp->next;
        }
//  printing cluster's dimension, cluster's points and the minimum square distance.
    printf("Cluster's dimension: %d\n", pCluster->dimension);
    ListPrint(pCluster->point_list);
    printf("\n\nMinimum Square Distance: %d", MinSqDist);
}
