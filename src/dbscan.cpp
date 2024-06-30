#include <iostream>
#include <ros/ros.h>

#include "dbscan/algo.h"
#include "dbscan/pbbs/parallel.h"

#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>

#include "dbscan_msgs/DBScan.h"

constexpr int DIM = 3;


bool calc_dbscan(dbscan_msgs::DBScan::Request &req, dbscan_msgs::DBScan::Response &res) {

    ROS_DEBUG("dbscan is called.");

    sensor_msgs::PointCloud cloud;
    sensor_msgs::convertPointCloud2ToPointCloud(req.points, cloud);
    double p_epsilon = req.eps;
    size_t p_minpts = req.min_samples;
    size_t n = cloud.points.size();

    bool* coreFlag = new bool[n];
    int* coreFlag2 = new int[n];
    int* cluster = new int[n];
    double* data = new double[DIM * n];

    for (size_t i = 0; i < n; i++) {
        data[i * DIM + 0] = cloud.points[i].x;
        data[i * DIM + 1] = cloud.points[i].y;
        data[i * DIM + 2] = cloud.points[i].z;
    }

    parlay::internal::start_scheduler();
    if (DBSCAN<DIM>(n, data, p_epsilon, p_minpts, coreFlag, coreFlag2, cluster)) {
        ROS_ERROR("Error: dimension >20 is not supported.");
        return false;
    }
    parlay::internal::stop_scheduler();

    res.labels.assign(cluster, cluster + n);

    delete[] coreFlag;
    delete[] coreFlag2;
    delete[] cluster;
    delete[] data;

    return true;
}


int main(int argc, char* argv[]) {
  ros::init(argc, argv, "dbscan");
  ros::NodeHandle nh;
  ros::ServiceServer service = nh.advertiseService("dbscan", calc_dbscan);
  ROS_INFO("dbscan is ready.");
  ros::spin();
  return 0;
}
