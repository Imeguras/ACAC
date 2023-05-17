#include "spac_node.h"
SpacNode::SpacNode() : Node(DRIVEMODEL_NODE_NAME){
	this->declare_parameter(PARAMS_FREQUENCY, 0);
	this->get_parameter(PARAMS_FREQUENCY, m_frequency);
	
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