#include <iostream>
#include <ros/ros.h>

#include "dbscan/algo.h"
#include "dbscan/pbbs/parallel.h"

#include <geometry_msgs/Point.h>
#include "dbscan/DBScan.h"

constexpr int DIM = 3;


bool calc_dbscan(dbscan::DBScan::Request &req, dbscan::DBScan::Response &res) {

    ROS_INFO("dbscan is called.");

    double p_epsilon = req.eps;
    size_t p_minpts = req.min_samples;
    std::vector<geometry_msgs::Point> points = req.points;
    size_t n = req.points.size();

    bool* coreFlag = new bool[n];
    int* coreFlag2 = new int[n];
    int* cluster = new int[n];
    double* data = new double[DIM * n];

    for (size_t i = 0; i < n; i++) {
        geometry_msgs::Point p = points[i];
        data[i * DIM + 0] = p.x;
        data[i * DIM + 1] = p.y;
        data[i * DIM + 2] = p.z;
    }

    if (DBSCAN<DIM>(n, data, p_epsilon, p_minpts, coreFlag, coreFlag2, cluster)) {
        ROS_ERROR("Error: dimension >20 is not supported.");
        return false;
    }

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
  parlay::internal::start_scheduler();
  ros::ServiceServer service = nh.advertiseService("dbscan", calc_dbscan);
  ROS_INFO("dbscan is ready.");
  ros::spin();
  parlay::internal::stop_scheduler();
  return 0;
}
