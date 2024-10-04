#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node{
  public:
    MinimalPublisher(): Node("minimal_publisher"), count_(0){
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
      timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
      message_ = geometry_msgs::msg::Twist();
      timestep = 0.5;
    }

  private:
    float time = 0.0;
    int sides = 5;
    float timestep;
    void timer_callback(){
      printf("timer_callback\n");
      if(((int)time % 2) < 1){
	message_.linear.x = 1.0;
	message_.angular.z = 0.0;
      } else {
	message_.linear.x = 0.0;
	message_.angular.z = (2*(1.5*3.14159)/sides);
      }
      publisher_->publish(message_);

      time += timestep;
      if (time >= 10){ time = 0.0; }
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    geometry_msgs::msg::Twist message_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
