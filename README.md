# rosbag2image
This ros package subscribes to image topics of ros and save them as images (format PNG) and converts imu data into .csv file, which results in the same data format as the [EuRoC MAV dataset](https://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets).<br>
## Dependency
* OpenCV (VERSION > 3.0)<br>

If ROS (indigo) is being used, it is recommended to manually install cv_bridge above oepncv3.0. [URL](https://github.com/ros-perception/vision_opencv)<br>

        git clone https://github.com/ros-perception/vision_opencv.git
        cd vision_opencv & cd cv_bridge
        mkdir build & cd build
        make 
        sudo make install
## Compile
    cd rosbag2image
    mkdir build & cd build
    cmake ..
    make 
    source devel/setup.bash
    roslaunch rosbag2image test.launch
Note that the node should run with three parameters: save path, topic name and isColor (true or false).<br>
