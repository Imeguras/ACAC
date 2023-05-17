#ifndef SPAC_NODE_H_
#define SPAC_NODE_H_

#include <cstdio>
#include <string.h>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <ackermann_msgs/msg/ackermann_drive.hpp>
#include <string>
#define PARAMS_FREQUENCY "frequency"


#define DRIVEMODEL_NODE_NAME "DriveModelNode"
class SpacNode : public rclcpp::Node{
	public:
		SpacNode(); 

		/**
		 * @brief Get the Node Name object
		 * 
		 * @return std::string
		*/
		std::string g_NodeName();
		/**
		 * @brief Setter for the Frequency of the node
		 * 
		 * @param freq 
		 * @return the status, 0 if successful, non zero if not 
		**/
		int s_Frequency(int freq);
		/**
		 * @brief Getter for the Frequency of the node
		 *
		 * @return the frequency of the node
		*/
		int g_Frequency(); 
	protected:
		int m_frequency=0; 
		

};

#endif