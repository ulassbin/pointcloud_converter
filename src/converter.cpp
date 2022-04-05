#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>


namespace converter
{
class Converter
{
  public:
  Converter()
  {
  	ros::NodeHandle nh;
  	sub_cloud_ = nh.subscribe<sensor_msgs::PointCloud>("cloud_in", 100, &Converter::cloudCallback, this);
	  pub_cloud_ = nh.advertise<sensor_msgs::PointCloud2>("cloud_out", 100);
  };
  private:
  void cloudCallback(const sensor_msgs::PointCloud cloud_in)
  {
    sensor_msgs::PointCloud2 cloud_out;
  	sensor_msgs::convertPointCloudToPointCloud2(cloud_in, cloud_out);
  	pub_cloud_.publish(cloud_out);
  };
  ros::Subscriber sub_cloud_;
  ros::Publisher pub_cloud_;
};
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "pointcloud_converter");
  converter::Converter converter;  
  ros::spin();
  return 0;
}
