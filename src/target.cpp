#include "target.h"
#include "fmath.h"
#include <cmath>
#include <cstdio>
#include <math.h>
#include <iostream>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>



TargetWaypoint::TargetWaypoint(rclcpp::Logger logger){

	this->m_logger= &logger;
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