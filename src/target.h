#ifndef TARGET_H_
#define TARGET_H_
#include <cstdio>
#include <string>
#include <chrono>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/logger.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <ackermann_msgs/msg/ackermann_drive.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Scalar.h>
#include <ackermann_msgs/msg/detail/ackermann_drive__struct.hpp>

#include "fmath.h"

#ifdef __FSIPLEIRIA_2D_ONLY__
	#include <geometry_msgs/msg/pose2_d.hpp>
#else 
	#include <geometry_msgs/msg/pose.hpp>
#endif


class TargetWaypoint{
	public: 
		TargetWaypoint();
		virtual ~TargetWaypoint() = default;
		ackermann_msgs::msg::AckermannDrive m_CurrentDrive;

		fs_KinematicsFloat_t predict_trackAngle();
		fs_KinematicsFloat_t compensate_CurrentAngle(fs_KinematicsFloat_t angle);
		/**
		* @brief Set/Update the current target waypoint
		*/
		int s_Odometry(const nav_msgs::msg::Odometry::SharedPtr msg);
		
		#ifdef __FSIPLEIRIA_2D_ONLY__
			int s_CurrentTargetWaypoint(const geometry_msgs::msg::Pose2D::SharedPtr msg);
		#else
			int s_CurrentTargetWaypoint(const geometry_msgs::msg::Pose::SharedPtr msg);
		#endif
	protected:
		
		PID_Controller* m_pid_controller;
		PID_Controller* m_pid_controller_angular;
		Steering_Reverse_Kinematics m_steering_reverse_kinematics;
		fs_PidFloat_t k_p=(fs_PidFloat_t)0.1, k_i=(fs_PidFloat_t)0.1, k_d=(fs_PidFloat_t)0.1;
		nav_msgs::msg::Odometry m_CurrentOdometry;
		#ifdef __FSIPLEIRIA_2D_ONLY__
			geometry_msgs::msg::Pose2D m_CurrentTargetWaypoint;
		#else
			geometry_msgs::msg::Pose m_CurrentTargetWaypoint;
		#endif
		
};
#endif // TARGET_H_