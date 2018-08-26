#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include<sensor_msgs/Imu.h>
#include<std_msgs/String.h>
#include<sstream>
#include <iostream>  
#include <iomanip>  
#include <fstream>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgcodecs.hpp>
//file
#include <sys/stat.h> 
#include <sys/types.h>
#include<dirent.h>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::stringstream;
using std::fixed;
using std::setprecision;

stringstream ss;
string filepath;
std::vector<int> compression_params;
bool isColor;

void imageRight_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
        double t=img_msg->header.stamp.toSec();
        //convert to ns
        size_t t1=t*1e9;
    //convert to image	
    cv_bridge::CvImagePtr cv_ptr;
        try
        {
            if(isColor)
                cv_ptr = cv_bridge::toCvCopy(img_msg,sensor_msgs::image_encodings::RGB8);
            else
                cv_ptr = cv_bridge::toCvCopy(img_msg,sensor_msgs::image_encodings::MONO8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert from '%s' to 'mono8'.", img_msg->encoding.c_str());
        }
        ss<<t1;
        string name=string(ss.str()+".png");
        string image_right_file(filepath+"/right/"+name);
        cout<<name<<endl;
        cv::imwrite(image_right_file,cv_ptr->image,compression_params);
        ss.clear();
        ss.str("");
}

bool checkPath(std::string &path)
{
   DIR *dir;int isCreate=0 ; int isC=0;
    if ((dir=opendir((path+"/left/").c_str())) == NULL)
    {
        isCreate =mkdir((path+"/left/").c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }
    if((dir=opendir((path+"/right/").c_str())) == NULL)
    {
        isC=mkdir((path+"/right/").c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }

     if(isC==0&&isCreate==0)
         return true;
     else
         return false;
}


int main(int argc, char **argv)
{	
	if (argc<2) 
	{
	cout<<"please input file output path"<<endl;
	return -1;
	}
	//path
    filepath.assign(argv[1]);
    bool isOK=checkPath(filepath);
    if(!isOK){
        cout<<"file path can not be found."<<endl;
        return -1;
    }
    //topic
    string topic;
    topic.assign(argv[2]);
	compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);
	ros::init(argc, argv, "imWriteRight");
	ros::NodeHandle n;
    
    	cout<<endl<<"topic:"<<topic.c_str()<<endl;
	cout<<"Writing image to "<<filepath.c_str()<<endl;
    	std::istringstream(argv[3])>>std::boolalpha>>isColor;
	cout<<"isColor:"<<argv[3]<<endl;
	ros::Subscriber sub_image_imu=n.subscribe(topic.c_str(),100,imageRight_callback);
	ros::Rate loop_rate(50);
	while(ros::ok())
	{
	ros::spinOnce();
	loop_rate.sleep();
	}
    cout<<"the end"<<endl;
	return 0;
}
