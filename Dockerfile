FROM ros:noetic
RUN apt-get update && apt-get upgrade -y && \
  apt-get install -y build-essential && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/*

WORKDIR /
COPY ./docker_scripts ./setup

WORKDIR /root/catkin_ws

COPY ./src ./src/dbscan-ros/src
COPY ./include ./src/dbscan-ros/include
COPY ./srv ./src/dbscan-ros/srv
COPY ./package.xml ./src/dbscan-ros/package.xml
COPY ./CMakeLists.txt ./src/dbscan-ros/CMakeLists.txt

RUN /setup/setup.bash

CMD /setup/run.bash
