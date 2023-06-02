#include <gtest/gtest.h>
#include <cmath>
#include <math.h>
#include <memory>
#include <nav_msgs/msg/detail/odometry__struct.hpp>
#include <geometry_msgs/msg/detail/pose2_d__struct.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include "../src/target.h"
#ifdef __FSIPLEIRIA_2D_ONLY__
TargetWaypoint setupAngles(rclcpp::Logger logger, nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose2D waypoint);
#else 
TargetWaypoint setupAngles(rclcpp::Logger logger, nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose waypoint);
#endif
rclcpp::Node::SharedPtr node_;


TEST(package_name, check_angle_straight){
	
	nav_msgs::msg::Odometry odom_check_angle_straight;
	#ifdef __FSIPLEIRIA_2D_ONLY__
		geometry_msgs::msg::Pose2D waypoint_check_angle_straight;
		waypoint_check_angle_straight.x = 0;
		waypoint_check_angle_straight.y = 0;
		waypoint_check_angle_straight.theta = 0;

	#else 
		geometry_msgs::msg::Pose waypoint_check_angle_straight;
		//it would make too much spaghetti... it sets things to zero


	#endif
	
	TargetWaypoint target = setupAngles(node_->get_logger(), odom_check_angle_straight, waypoint_check_angle_straight);
	fs_KinematicsFloat_t f = target.predict_trackAngle();
	
	EXPECT_FLOAT_EQ(f, (fs_KinematicsFloat_t)0);
}

TEST(package_name, check_angle_90){
	nav_msgs::msg::Odometry odom_check_angle_90;
	#ifdef __FSIPLEIRIA_2D_ONLY__
		geometry_msgs::msg::Pose2D waypoint_check_angle_90;
		waypoint_check_angle_90.x = 5;
		waypoint_check_angle_90.y = 0;
	#else
		geometry_msgs::msg::Pose waypoint_check_angle_90;
		//set the position to 5,0,0
		waypoint_check_angle_90.position.x = 5;
		waypoint_check_angle_90.position.y = 0;
		waypoint_check_angle_90.position.z = 0;
	#endif
	TargetWaypoint target2 = setupAngles(node_->get_logger(), odom_check_angle_90, waypoint_check_angle_90);
	fs_KinematicsFloat_t f = target2.predict_trackAngle();
	
	EXPECT_FLOAT_EQ(f, (fs_KinematicsFloat_t)M_PI_2);

}

#ifdef __FSIPLEIRIA_2D_ONLY__
	TargetWaypoint setupAngles(rclcpp::Logger logger, nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose2D waypoint){
		
		TargetWaypoint target(logger);
		//odom at a zero state
		nav_msgs::msg::Odometry::SharedPtr ptrOdom = std::make_shared<nav_msgs::msg::Odometry>(odom);
		
		target.s_Odometry(ptrOdom);

		geometry_msgs::msg::Pose2D::SharedPtr ptrWayp = std::make_shared<geometry_msgs::msg::Pose2D>(waypoint);

		target.s_CurrentTargetWaypoint(ptrWayp);
		return target;
		
	}
#else
	TargetWaypoint setupAngles(rclcpp::Logger logger, nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose waypoint){
	
		
		TargetWaypoint target(logger);
		//odom at a zero state
		nav_msgs::msg::Odometry::SharedPtr ptrOdom = std::make_shared<nav_msgs::msg::Odometry>(odom);
		
		target.s_Odometry(ptrOdom);

		geometry_msgs::msg::Pose::SharedPtr ptrWayp = std::make_shared<geometry_msgs::msg::Pose>(waypoint);

		target.s_CurrentTargetWaypoint(ptrWayp);
		return target;
	}
#endif


int main(int argc, char** argv){
	rclcpp::init(argc, argv);
	node_ = rclcpp::Node::make_shared("test_node_");
	 rclcpp::spin_some(node_);


	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	//destroy node
	node_.reset();

	rclcpp::shutdown();
	return ret;
}
