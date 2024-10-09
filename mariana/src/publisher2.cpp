
//tortugueando en circulo 
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <unistd.h> 

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
      //timer_ = this->create_wall_timer(
      //0.5s, std::bind(&MinimalPublisher::timer_callback, this));
      time_callback(); { 

      }
    }
 
  private:
float time=0;
    void timer_callback()
    { 
       
        auto message = geometry_msgs::msg::Twist();
        for(float i=0; i<10; i+=0.5); 
        {
        message.linear.x = 1.0;
        message.angular.x=0.0;
        message.angular.x=0.0;
        publisher_->publish(message);
        usleep(50000);
        time+=0.5;
            }
    
      RCLCPP_INFO(this->get_logger(), "Publishing linear.x=%.2f, angular.x=%.2f", message.linear.x,message.angular.x);

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