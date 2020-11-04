#include "ros/ros.h"
#include "std_msgs/String.h"

#include <rtt/RTT.hpp>
#include "HelloWorld-component.hpp"
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Rate loop_rate(10);

  HelloWorld hw("Hello");

  hw.configure();
  hw.setPeriod(1);
  hw.start();

  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  hw.stop();
  hw.cleanup();

  return 0;
}
