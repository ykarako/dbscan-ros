FROM ros:noetic
RUN apt-get update && apt-get install -y curl && (curl https://sh.rustup.rs -sSf | sh -s -- -y --profile default) && \
    apt-get remove --purge -y curl && apt-get autoremove --purge -y && \
    rm -rf /var/cache/apt

WORKDIR /

COPY ./docker_scripts ./setup

WORKDIR /root/catkin_ws

COPY ./msgs/dbscan_msgs ./src/dbscan_msgs
COPY ./dbscan-python/src ./src/dbscan-python/src
COPY ./dbscan-python/package.xml ./src/dbscan-python/package.xml
COPY ./dbscan-python/CMakeLists.txt ./src/dbscan-python/CMakeLists.txt

RUN /setup/setup.bash

CMD /setup/run.bash
