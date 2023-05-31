#include <geometry_msgs/msg/detail/pose2_d__struct.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <nav_msgs/msg/detail/odometry__struct.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include "../src/target.h"
TargetWaypoint setupAngles(nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose2D waypoint);





TEST(package_name, check_angle_straight){
	nav_msgs::msg::Odometry odom_check_angle_straight;

	geometry_msgs::msg::Pose2D waypoint_check_angle_straight;
	waypoint_check_angle_straight.x = 0;
	waypoint_check_angle_straight.y = 5;

	TargetWaypoint target = setupAngles(odom_check_angle_straight, waypoint_check_angle_straight);
	fs_KinematicsFloat_t f = target.predict();
	EXPECT_FLOAT_EQ(f, 0);
}
// test for 90 degrees
TEST(package_name, check_angle_90){
	nav_msgs::msg::Odometry odom_check_angle_90;

	geometry_msgs::msg::Pose2D waypoint_check_angle_90;
	waypoint_check_angle_90.x = 5;
	waypoint_check_angle_90.y = 0;

	TargetWaypoint target = setupAngles(odom_check_angle_90, waypoint_check_angle_90);
	fs_KinematicsFloat_t f = target.predict();
	EXPECT_FLOAT_EQ(f, 90);
}

#ifdef __FSIPLEIRIA_2D_ONLY__
	TargetWaypoint setupAngles(nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose2D waypoint){
		//instantiate target
		//create a logger
		rclcpp::Logger logger = rclcpp::get_logger("test_logger");
		TargetWaypoint target(logger);
		//odom at a zero state
		nav_msgs::msg::Odometry::SharedPtr ptrOdom = std::make_shared<nav_msgs::msg::Odometry>(odom);
		
		target.s_Odometry(ptrOdom);

		geometry_msgs::msg::Pose2D::SharedPtr ptrWayp = std::make_shared<geometry_msgs::msg::Pose2D>(waypoint);

		target.s_CurrentTargetWaypoint(ptrWayp);
		return target;
		
	}
#else
	TargetWaypoint setupAngles(nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose waypoint){
		//instantiate target
		//create a logger
		rclcpp::Logger logger = rclcpp::get_logger("test_logger");
		TargetWaypoint target(logger);
		//odom at a zero state
		nav_msgs::msg::Odometry odom;
		nav_msgs::msg::Odometry::SharedPtr ptrOdom = std::make_shared<nav_msgs::msg::Odometry>(odom);
		
		target.s_Odometry(ptrOdom);
		
			geometry_msgs::msg::Pose waypoint;
			
			geometry_msgs::msg::Pose::SharedPtr ptrWayp = std::make_shared<geometry_msgs::msg::Pose>(waypoint);

		target.s_CurrentTargetWaypoint(ptrWayp);
	}
#endif


int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
