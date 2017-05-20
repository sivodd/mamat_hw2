#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "point.h"

typedef struct cluster{
    PList point_list;
    int dimension;
}Cluster, *PCluster;


//*************************************************************************************
//* Function name : ClusterCreate
//* Description   : Creates a new cluster given a dimension.
//* Parameters    : dimension - the dimension of the points in the cluster.
//* Return value  : PCluster - a pointer to the new cluster.
//*************************************************************************************
PCluster ClusterCreate(int dimension);

//*************************************************************************************
//* Function name : ClusterDestroy
//* Description   : Deletes the given cluster and frees it's memory.
//* Parameters    : pCluster - a pointer to a cluster.
//* Return value  : None.
//*************************************************************************************
void ClusterDestroy(PCluster pCluster);

//*************************************************************************************
//* Function name : ClusterAddPoint
//* Description   : Adds the given point to the end of the given cluster's point list.
//* Parameters    : pCluster - a pointer to a cluster.
//                  pPoint - a pointer to a point.
//* Return value  : SUCCESS / FAIL
//*************************************************************************************
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint);

//*************************************************************************************
//* Function name : ClusterGetMinDistance
//* Description   : Calculates the minimum distance between a given point and a cluster.
//* Parameters    : pCluster - a pointer to a cluster.
//                  pPoint - a pointer to a point.
//* Return value  : minimum distance - number.
//*************************************************************************************
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint);

//*************************************************************************************
//* Function name : ClusterPrint
//* Description   : Prints the cluster and the Minimum Square Distance.
//* Parameters    : pCluster - a pointer to a cluster.
//* Return value  : None.
//*************************************************************************************
void ClusterPrint(PCluster pCluster);

#endif
