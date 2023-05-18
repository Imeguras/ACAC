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
#define PARAMS_TOPIC_WAYPOINT "wp_topic"
#define PARAMS_TOPIC_ODOMETRY "odom_topic"
#define PARAMS_TOPIC_ACKERMANN "ackermann_topic"



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

		/**
		 * @brief Getter for the Waypoint topic
		 * 
		 * @return std::string 
		*/
		std::string g_WaypointTopic();
		/**
		* @brief Getter for the Odometry topic
		*
		* @return std::string
		*/
		std::string g_OdometryTopic();
		/**
		* @brief Getter for the Ackermann Drive messages topic
		*
		* @return std::string
		*/
		std::string g_AckermannTopic();



	protected:
		int m_frequency=0; 
		/**
		 * @brief These three properties are meant to be set through ros2 params and may only be set that way
		*/
		std::string m_waypoint_topic;
		std::string m_odometry_topic;
		std::string m_ackermann_topic;
		

};

#endif