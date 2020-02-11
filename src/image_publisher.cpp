
#include <chrono>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"

using namespace std::literals::chrono_literals;


int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("image_publisher");
  image_transport::ImageTransport image_tx{node};
  auto pub = image_tx.advertise("camera/image", 1);

//  auto img = cv::imread("dashing.png", CV_LOAD_IMAGE_COLOR);
  auto img = cv::Mat{256, 256, CV_8UC3, cv::Scalar(255, 0, 0)};
  auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", img).toImageMsg();
  rclcpp::WallRate loop_rate{500ms};

  while (rclcpp::ok()) {
    pub.publish(msg);
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
