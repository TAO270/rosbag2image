#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include<sensor_msgs/Imu.h>
#include<std_msgs/String.h>
#include<sstream>
#include <iostream>  
#include <iomanip>  
#include <fstream>

using namespace std;

string  filepath;

ofstream csv_file;
string temp;

    void imu_callback(const sensor_msgs::ImuConstPtr &imu_msg)
    {
        double t = imu_msg->header.stamp.toSec();

        size_t  t1=t*1e9;
        double ax = imu_msg->linear_acceleration.x;
        double ay = imu_msg->linear_acceleration.y;
        double az = imu_msg->linear_acceleration.z;
            
        double rx = imu_msg->angular_velocity.x;
        double ry = imu_msg->angular_velocity.y;
        double rz = imu_msg->angular_velocity.z;
         temp=filepath+"/imu_data.csv";
        csv_file.open(temp.c_str(),ios::app);
        csv_file<<t1<<","<<rx<<","<<ry<<","<<rz<<","<<ax<<","<<ay<<","<<az<<endl;
        csv_file.close();
    }

int main(int argc, char **argv)
{	
	if (argc<2) 
	{
        cout<<"please inpute file path"<<endl;
        return -1;
    }
    
	filepath.assign(argv[1]);
	//new csv
    temp=filepath+"/imu_data.csv";
	csv_file.open(temp.c_str());
	csv_file<<"#timestamp [ns]"<<","<<"rx [rad s^-1]"<<","<<"ry [rad s^-1]"<<","<<"rz [rad s^-1]";
	csv_file<<","<<"ax [m s^-2]"<<","<<"ay [m s^-2]"<<","<<"az [m s^-2]"<<endl;
	csv_file.close();
	ros::init(argc, argv, "imu2csv");
	ros::NodeHandle n;
        string topic;
    	topic.assign(argv[2]);
	ros::Subscriber sub_image_imu=n.subscribe(topic.c_str(),1000,imu_callback);
	cout<<endl<<"topic:"<<topic.c_str()<<endl;
	cout<<"imu 2 csv…… "<<endl;
	ros::Rate loop_rate(500);
	while(ros::ok())
	{
	ros::spinOnce();
	loop_rate.sleep();
	}
	return 0;
}
