#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "point.h"

typedef struct cluster{
    PList point_list;
    int dimension;
}Cluster, *PCluster;

void PointDestroy(PPoint);
void PointPrint(PPoint);
PCluster ClusterCreate(int dimension);
void ClusterDestroy(PCluster pCluster);
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint);
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint);
void ClusterPrint(PCluster pCluster);

#endif
