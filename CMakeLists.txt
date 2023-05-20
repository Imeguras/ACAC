cmake_minimum_required(VERSION 3.8)
project(spac)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Faz com que o programa só tome em conta um plano 2D e não irá atuar em altura nem irá considerar dados sobre esse eixo
add_definitions(-D__FSIPLEIRIA_2D_ONLY__)

# Força o uso de double precision(64 bits em vez de 32)
# add_definitions(-D__FSIPLEIRIA_PID_DOUBLE_PRECISION__)


find_package(ament_cmake REQUIRED)
# ros2 
find_package(rclcpp REQUIRED)
# ackermann_msg

find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(ackermann_msgs REQUIRED)
find_package(tf2 REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
add_executable(main src/main.cpp src/spac_node.cpp src/fmath.cpp src/target.cpp)

#include 
ament_target_dependencies(main rclcpp std_msgs nav_msgs geometry_msgs ackermann_msgs tf2)


target_include_directories(main PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(main PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS main
  DESTINATION lib/${PROJECT_NAME})

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Doxygen


ament_package()
