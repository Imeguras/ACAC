#include "target.h"
#include "fmath.h"
#include <math.h>
#include <iostream>
#include <rclcpp/logging.hpp>



TargetWaypoint::TargetWaypoint(rclcpp::Logger logger){

	this->m_logger= &logger;
	m_pid_controller= new PID_Controller(k_p, k_i, k_d);
	m_pid_controller_angular= new PID_Controller(k_p, k_i, k_d);

}



fs_KinematicsFloat_t TargetWaypoint::predict(){
	#ifdef __FSIPLEIRIA_2D_ONLY__
		//Here only one rotational axis the Z axis is considered

		//get the angle formed between Pose2D and Odometry in radians

		//assuming the +Y is the nose of the car at 0 degrees
		fs_KinematicsFloat_t x__ = m_CurrentTargetWaypoint.x-m_CurrentOdometry.pose.pose.position.x; 
		fs_KinematicsFloat_t y__ = m_CurrentTargetWaypoint.y-m_CurrentOdometry.pose.pose.position.y;
		fs_KinematicsFloat_t dot_angle=std::atan2(x__, y__ );
		return dot_angle;
		
	
		// blank quartenion
		tf2::Quaternion blank;
		
		blank.setRPY(0, 0, (tf2Scalar)dot_angle);

		// put the only the yaw in the current orientation
		tf2::Vector3 axis = tf2::Vector3(0, 0, 1);
		tf2::Quaternion current_orientation = tf2::Quaternion(axis, (tf2Scalar )m_CurrentOdometry.pose.pose.orientation.z);
		//debug axis and current_orientation
		
		
		//for now this model works dumb ie it will always steer as quickly as possible
		//check the angle in Z formed between blank and current_orientation in Z
		// TODO: Implement something that takes the smoothness of the steer into account
		tf2Scalar angle= blank.normalize().angle(current_orientation.normalize());
		
		//fs_PidFloat_t track_angle =  m_pid_controller_angular->compute(0, angle);
		// TODO: find a way to get the track radius
		return angle;

		//fs_KinematicsFloat_t steerAngle =m_steering_reverse_kinematics.track_ComputeSteeringAngle((fs_KinematicsFloat_t)0, (fs_KinematicsFloat_t)track_angle);
		
		







	#else
		// Todo consider all axis
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