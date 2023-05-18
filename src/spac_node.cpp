#include "spac_node.h"
SpacNode::SpacNode() : Node(DRIVEMODEL_NODE_NAME){
	this->declare_parameter(PARAMS_FREQUENCY, 0);
	this->get_parameter(PARAMS_FREQUENCY, m_frequency);
	this->declare_parameter(PARAMS_TOPIC_WAYPOINT, "/");
	this->get_parameter(PARAMS_TOPIC_WAYPOINT, m_waypoint_topic);
	this->declare_parameter(PARAMS_TOPIC_ODOMETRY, "/");
	this->get_parameter(PARAMS_TOPIC_ODOMETRY, m_odometry_topic);
	this->declare_parameter(PARAMS_TOPIC_ACKERMANN, "/");
	this->get_parameter(PARAMS_TOPIC_ACKERMANN, m_ackermann_topic);

	
	
	//write yaml with parameters

}


int SpacNode::s_Frequency(int freq){
	m_frequency=freq; 
	this->set_parameter(rclcpp::Parameter(PARAMS_FREQUENCY, m_frequency));
	return 0; 
}
int SpacNode::g_Frequency(){
	this->get_parameter(PARAMS_FREQUENCY, m_frequency);
	return m_frequency; 
}
std::string SpacNode::g_NodeName(){
	return DRIVEMODEL_NODE_NAME; 
}
std::string SpacNode::g_WaypointTopic(){
	std::string topic; 
	this->get_parameter(PARAMS_TOPIC_WAYPOINT, topic);
	return topic; 
}
std::string SpacNode::g_OdometryTopic(){
	std::string topic; 
	this->get_parameter(PARAMS_TOPIC_ODOMETRY, topic);
	return topic; 
}
std::string SpacNode::g_AckermannTopic(){
	std::string topic; 
	this->get_parameter(PARAMS_TOPIC_ACKERMANN, topic);
	return topic; 
}

