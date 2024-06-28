#!/bin/bash -e
source "/opt/ros/${ROS_DISTRO}/setup.bash"
source ~/catkin_ws/devel/setup.bash

rosrun dbscan_ros dbscan
