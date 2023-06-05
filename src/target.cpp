#include "target.h"
#include "fmath.h"
#include <cmath>
#include <cstdio>
#include <geometry_msgs/msg/detail/quaternion__struct.hpp>
#include <math.h>
#include <iostream>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
//include geometry_msg::msg::Quaternion
#include <geometry_msgs/msg/quaternion.hpp>
#include <tf2/LinearMath/Matrix3x3.h>


TargetWaypoint::TargetWaypoint(){
	m_pid_controller= new PID_Controller(k_p, k_i, k_d);
	m_pid_controller_angular= new PID_Controller(k_p, k_i, k_d);

}


//I assumed the car is naturally pointed at the +Y axis 
fs_KinematicsFloat_t TargetWaypoint::predict_trackAngle(){
	#ifdef __FSIPLEIRIA_2D_ONLY__
		
		fs_KinematicsFloat_t delta_x = m_CurrentTargetWaypoint.x - m_CurrentOdometry.pose.pose.position.x;
		fs_KinematicsFloat_t delta_y = m_CurrentTargetWaypoint.y - m_CurrentOdometry.pose.pose.position.y;
		

		// Due to above x and y is flipped here
		fs_KinematicsFloat_t theta_dot = std::atan2(delta_x,delta_y);

		return theta_dot;

	#else
		fs_KinematicsFloat_t delta_x = m_CurrentTargetWaypoint.x - m_CurrentOdometry.pose.pose.position.x;
		fs_KinematicsFloat_t delta_y = m_CurrentTargetWaypoint.y - m_CurrentOdometry.pose.pose.position.y;
		fs_KinematicsFloat_t delta_z = m_CurrentTargetWaypoint.z - m_CurrentOdometry.pose.pose.position.z;
		
		//fs_KinematicsFloat_t theta_pos = std::atan2(,);
		return 0;
	#endif

}
fs_KinematicsFloat_t TargetWaypoint::compensate_CurrentAngle(fs_KinematicsFloat_t angle){
	geometry_msgs::msg::Quaternion quaternion_pose = m_CurrentOdometry.pose.pose.orientation;
	//grab the quaternion from the odometry message convert it to euler angles
	tf2::Quaternion q(quaternion_pose.x, quaternion_pose.y, quaternion_pose.z, quaternion_pose.w);
	tf2::Matrix3x3 m(q);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
	

	
	return 0;

}

int TargetWaypoint::s_Odometry(const nav_msgs::msg::Odometry::SharedPtr msg){
	m_CurrentOdometry=*msg;
	return 0;
}

#ifdef __FSIPLEIRIA_2D_ONLY__
	int TargetWaypoint::s_CurrentTargetWaypoint(const geometry_msgs::msg::Pose2D::SharedPtr msg){
		m_CurrentTargetWaypoint=*msg;
		return 0;
	}
	
#else
	int TargetWaypoint::s_CurrentTargetWaypoint(const geometry_msgs::msg::Pose::SharedPtr msg){
		m_CurrentTargetWaypoint=*msg;
		return 0;
	}
#endif