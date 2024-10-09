cmake_minimum_required(VERSION 3.8)
project(blu_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)

# Add executables
add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp geometry_msgs turtlesim)

add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(square_publisher src/square_publisher.cpp)
ament_target_dependencies(square_publisher rclcpp geometry_msgs)

# Testing
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Install targets
install(TARGETS
  talker
  listener
  square_publisher
  DESTINATION lib/${PROJECT_NAME})

ament_package()

