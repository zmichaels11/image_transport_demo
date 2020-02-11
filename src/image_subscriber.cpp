
#include <chrono>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"

using namespace std::literals::chrono_literals;

void image_callback(const sensor_msgs::msg::Image::ConstSharedPtr & msg)
{
  int p = 0;
  for (uint32_t j = 0; j < 16; ++j) {
    for (uint32_t i = 0; i < 16; ++i) {
      std::cout << "<" << static_cast<int>(msg->data[p]) << ", " <<
        static_cast<int>(msg->data[p+1]) << ", " <<
        static_cast<int>(msg->data[p+2]) << "> ";

      p+=3;
    }
    std::cout << "\n";
  }

  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("image_subscriber");
  image_transport::ImageTransport image_tx{node};
  image_transport::TransportHints hints{node.get(), "compressed"};
  auto sub = image_tx.subscribe("camera/image", 1, image_callback, 0, &hints);

  rclcpp::WallRate loop_rate{500ms};

  while (rclcpp::ok()) {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
