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

#include "fmath.h"
#ifdef __FSIPLEIRIA_2D_ONLY__
	#include <geometry_msgs/msg/pose2_d.hpp>
#else 
	#include <geometry_msgs/msg/pose.hpp>
#endif

class TargetWaypoint{
	public: 
		TargetWaypoint(rclcpp::Logger logger);
		virtual ~TargetWaypoint() = default;
		void predict();
		/**
		* @brief Set/Update the current target waypoint
		*/
		#ifdef __FSIPLEIRIA_2D_ONLY__
			int s_CurrentTargetWaypoint(const geometry_msgs::msg::Pose2D::SharedPtr msg);
		#else
			int s_CurrentTargetWaypoint(const geometry_msgs::msg::Pose::SharedPtr msg);
		#endif
	protected:
		rclcpp::Logger* m_logger;
		PID_Controller* m_pid_controller;
		fs_PidFloat_t k_p=(fs_PidFloat_t)0.1, k_i=(fs_PidFloat_t)0.1, k_d=(fs_PidFloat_t)0.1;
		#ifdef __FSIPLEIRIA_2D_ONLY__
			geometry_msgs::msg::Pose2D m_CurrentTargetWaypoint;
		#else
			geometry_msgs::msg::Pose m_CurrentTargetWaypoint;
		#endif
		
};
#endif // TARGET_H_