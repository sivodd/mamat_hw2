#include <stdio.h>
#include <stdlib.h>
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
//  assigning all of Cluster's parameters and creating a list for points
    pCluster->dimension=dimension;
    pCluster->point_list= ListCreate(PointClone, PointDestroy, PointCompare, PointPrint);
	if (pCluster->point_list == NULL)
	{
		free(pCluster);
		return NULL;
	}
    return pCluster;
}

//*************************************************************************************
//* Function name : ClusterDestroy
//* Description   : Deletes the given cluster and frees it's memory.
//* Parameters    : pCluster - a pointer to a cluster.
//* Return value  : None.
//*************************************************************************************
void ClusterDestroy(void* pCluster){
	PCluster c_pCluster = (PCluster)pCluster;
    ListDestroy(c_pCluster->point_list);
    free(c_pCluster);
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
//  check if the point already exists in the cluster if so return fail.
    while(pPoint_curr!=NULL){
        if (ListCompare(pPoint_curr->coordinate_list, pPoint->coordinate_list))
            return FAIL;
        else pPoint_curr=ListGetNext(pCluster->point_list);
    }
//  add pPoint to the end of the cluster.
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
    int min_d=2147483647;
    int d=0;
    PPoint pPoint_curr=ListGetFirst(pCluster->point_list);
//  iterates on all points in cluster.
    while (pPoint_curr!=NULL){
        d=PointDistance(pPoint_curr, pPoint);
        //if the distance is smaller then the min distance and the point in the cluster
        // and is not the same as pPoint
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
void ClusterPrint(void* pCluster){
	PCluster c_pCluster = (PCluster)pCluster;
    int MinSqDist=2147483647;
    int d=0;
    PPoint pPoint_curr=ListGetFirst(c_pCluster->point_list);
//  iter_temp will save the pointer to the iterator before we use a function that will move the iterator so
//  we can have every point compared with the whole list
    PNode iter_tmp=c_pCluster->point_list->iterator;
//  check that we didn't get to the end of the list and that the list has more then 1 point.
    while (pPoint_curr!=NULL && c_pCluster->point_list->head!=c_pCluster->point_list->tail){
//      find the minimum distance between the current point and the rest of the cluster.
        d=ClusterGetMinDistance(pCluster, pPoint_curr);
        if (d<MinSqDist)
            MinSqDist=d;
//      move the list iterator back to where current point is so we can find the next point in the list.
        c_pCluster->point_list->iterator=iter_tmp;
        pPoint_curr=ListGetNext(c_pCluster->point_list);
        iter_tmp=iter_tmp->next;
        }
//  printing cluster's dimension, cluster's points and the minimum square distance.
    printf("Cluster's dimension: %d\n", c_pCluster->dimension);
    ListPrint(c_pCluster->point_list);
    if (d==0){
        printf("1000 \n");
    }
    else printf("Minimum Square Distance: %d\n", MinSqDist);
}
