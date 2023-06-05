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
#include <ackermann_msgs/msg/detail/ackermann_drive__builder.hpp>
#include <ackermann_msgs/msg/detail/ackermann_drive__struct.hpp>
#include <cmath>
#include <cstdio>
#include <geometry_msgs/msg/detail/quaternion__struct.hpp>
#include <math.h>
#include <iostream>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <tf2/LinearMath/Matrix3x3.h>


#ifdef __FSIPLEIRIA_2D_ONLY__
	#include <geometry_msgs/msg/pose2_d.hpp>
#else 
	#include <geometry_msgs/msg/pose.hpp>
#endif


class TargetWaypoint{
	public: 
		TargetWaypoint(float track_width);
		TargetWaypoint();
		virtual ~TargetWaypoint() = default;
		ackermann_msgs::msg::AckermannDrive m_CurrentDrive;

		fs_KinematicsFloat_t predict_trackAngle();
		fs_KinematicsFloat_t current_Angle();
		
		ackermann_msgs::msg::AckermannDrive g_dirtyDispatcherMail();
		bool g_isDispatcherDirty();
		int s_throwDirtDispatcher();
		void instance_CarrotControl();
		/**
		* @brief Set/Update the current target waypoint
		*/
		int s_Odometry(const nav_msgs::msg::Odometry::SharedPtr msg);
		int s_TrackWidth(const float trackWidth);

		#ifdef __FSIPLEIRIA_2D_ONLY__
			int s_CurrentTargetWaypoint(const geometry_msgs::msg::Pose2D::SharedPtr msg);
		#else
			int s_CurrentTargetWaypoint(const geometry_msgs::msg::Pose::SharedPtr msg);
		#endif
	protected:
		bool m_isDispatcherDirty=false;
		ackermann_msgs::msg::AckermannDrive m_DispatcherMailBox; 
		PID_Controller* m_pid_controller;
		PID_Controller* m_pid_controller_angular;
		Steering_Reverse_Kinematics m_steering_reverse_kinematics;
		float m_trackWidth=0.0f;
		fs_PidFloat_t ks_p=(fs_PidFloat_t)0.1, ks_i=(fs_PidFloat_t)0.1, ks_d=(fs_PidFloat_t)0.1;
		fs_PidFloat_t kd_p=(fs_PidFloat_t)0.1, kd_i=(fs_PidFloat_t)0.1, kd_d=(fs_PidFloat_t)0.1;
		nav_msgs::msg::Odometry m_CurrentOdometry;
		#ifdef __FSIPLEIRIA_2D_ONLY__
			geometry_msgs::msg::Pose2D m_CurrentTargetWaypoint;
		#else
			geometry_msgs::msg::Pose m_CurrentTargetWaypoint;
		#endif
		
};
#endif // TARGET_H_