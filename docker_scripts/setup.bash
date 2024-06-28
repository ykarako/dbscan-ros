#!/bin/bash -e

source /opt/ros/${ROS_DISTRO}/setup.bash
echo '. /opt/ros/${ROS_DISTRO}/setup.bash' >> $HOME/.bashrc
echo '. $HOME/catkin_ws/devel/setup.bash' >> $HOME/.bashrc

# catkin make
cd ~/catkin_ws
catkin_make

