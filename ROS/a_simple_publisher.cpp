//talker.cpp
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");//初始化一个节点，节点名唯一

  ros::NodeHandle n;//初始化一个节点的句柄，节点通过这个句柄和master通讯

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);//定义一个话题，1000是buffer长度，返回一个Publisher的object，可以通过这个object发布具体的消息内容

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world" << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();//响应一次回调函数，除了响应回调函数之外还有其他东西需要处理时，用spinOnce；若只需响应回调函数，则可以用spin

    loop_rate.sleep();//休眠等待直到loop_rate设定值
    ++count;
  }

  return 0;
}
