#ifndef SPAC_NODE_H_
#define SPAC_NODE_H_
/**
* @brief Serve para indicar se o modelo tem em consideração um plano ou um espaço. <b> É suposto ser definido no cmake para evitar dependências circulares </b>
*/
//#define __FSIPLEIRIA_2D_ONLY__

#include <cstdio>
#include <string>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <ackermann_msgs/msg/ackermann_drive.hpp>
#include <chrono>

#ifdef __FSIPLEIRIA_2D_ONLY__
	#include <geometry_msgs/msg/pose2_d.hpp>
#else 
	#include <geometry_msgs/msg/pose.hpp>
#endif
#include "target.h"


#define PARAMS_FREQUENCY "frequency"
#define PARAMS_TOPIC_WAYPOINT "wp_topic"
#define PARAMS_TOPIC_ODOMETRY "odom_topic"
#define PARAMS_TOPIC_ACKERMANN "ackermann_topic"
#define DRIVEMODEL_NODE_NAME "DriveModelNode"


class SpacNode : public rclcpp::Node{
	public:
		SpacNode();
		virtual ~SpacNode() = default;
		
		/**
		 * @brief Get the Node Name object
		 * 
		 * @return std::string
		*/
		std::string g_NodeName();
		/**
		 * @brief Getter for the Frequency of the node, to note that when used it will fetch params in order to update the internal variable
		 *
		 * @return the frequency of the node
		*/
		int g_Frequency(); 
		/**
		 * @brief Setter for the Frequency of the node, to note that when used it will update the internal variable and the params
		 * 
		 * @param freq 
		 * @return the status, 0 if successful, non zero if not 
		**/
		int s_Frequency(int freq);
		

		/**
		 * @brief Getters for the Waypoint, Odometry and Ackermann Drive topics respectively, to note that when used it will fetch params in order to update the internal variable
		 * 
		 * @return std::string 
		*/
		std::string g_WaypointTopic();
		std::string g_OdometryTopic();
		std::string g_AckermannTopic();



	protected:
		int m_frequency=0;
		rclcpp::TimerBase::SharedPtr m_timer;
		/**
		 * @brief These three properties are meant to be set through ros2 params and may only be set that way
		*/
		std::string m_waypoint_topic;
		std::string m_odometry_topic;
		std::string m_ackermann_topic;
		/**
		 * @brief Callback function for the waypoint topic
		 * 
		 * @param msg 
		*/
		#ifdef __FSIPLEIRIA_2D_ONLY__
			void waypoint_callback(const geometry_msgs::msg::Pose2D::SharedPtr msg);
		#else
			void waypoint_callback(const geometry_msgs::msg::Pose::SharedPtr msg);
		#endif
		/**
		 * @brief Callback function for the odometry topic
		 * 
		 * @param msg 
		*/
		void odometry_callback(const nav_msgs::msg::Odometry::SharedPtr msg);
	private: 
		TargetWaypoint * m_target_waypoint;
};

#endif