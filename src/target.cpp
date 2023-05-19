#include "target.h"
#include <rclcpp/logger.hpp>


TargetWaypoint::TargetWaypoint(rclcpp::Logger logger){
	this->m_logger= &logger;
	m_pid_controller= new PID_Controller(k_p, k_i, k_d);
	
}



void TargetWaypoint::predict(){

	RCLCPP_INFO(*this->m_logger, "Done { %s }", __PRETTY_FUNCTION__ );


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