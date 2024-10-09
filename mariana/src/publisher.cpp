
//singeometry

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;
/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher")
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10); 
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    { 
      auto message = geometry_msgs::msg::Twist();
      message.linear.x = 1.0;
      message.linear.y = 0.0;
      message.linear.z = 0.0;
      message.angular.x =0.0;
      message.angular.y =0.0;
      message.angular.z =0.0;


      message.linear.x = 1.0;
      message.angular.x =0.0;
      message.angular.x =1.0;

      RCLCPP_INFO(this->get_logger(), "Publishing linear.x=%.2f,linear.y=%.2f,linear.z=%.2f, angular.x=%.2f,angular.y=%.2f,angular.z=%.2f", message.linear.x,message.linear.y,message.linear.z,message.angular.x,message.angular.y,message.angular.z);
      publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};







int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MinimalPublisher>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}


