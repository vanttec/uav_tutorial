#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class SquareDrawer : public rclcpp::Node
{
public:
  SquareDrawer()
  : Node("square_drawer"), count_(0)
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&SquareDrawer::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = geometry_msgs::msg::Twist();

    if (count_ < 4) {
      // Move forward for 2 seconds
      message.linear.x = 1.0; // Forward speed
      message.angular.z = 0.0; // No rotation
      publisher_->publish(message);
      RCLCPP_INFO(this->get_logger(), "Moving forward: %d", count_);
      rclcpp::sleep_for(2s);
      count_++;
    } else {
      // Turn 90 degrees
      message.linear.x = 0.0; // No forward movement
      message.angular.z = 1.5708; // Rotate (approx. 90 degrees)
      publisher_->publish(message);
      RCLCPP_INFO(this->get_logger(), "Turning: %d", count_);
      rclcpp::sleep_for(1s);
      count_ = 0;
    }
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  int count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SquareDrawer>());
  rclcpp::shutdown();
  return 0;
}