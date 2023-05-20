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
	
	//subscribe to topic PARAMS_TOPIC_WAYPOINT of type Pose2d
	#ifdef __FSIPLEIRIA_2D_ONLY__
		auto m_waypoint_sub = this->create_subscription<geometry_msgs::msg::Pose2D>(
			m_waypoint_topic, 10, std::bind(&SpacNode::waypoint_callback, this, std::placeholders::_1));
	#else 
		auto m_waypoint_sub = this->create_subscription<geometry_msgs::msg::Pose>(
			m_waypoint_topic, 10, std::bind(&SpacNo	de::waypoint_callback, this, std::placeholders::_1));
	#endif

	m_target_waypoint = new TargetWaypoint(this->get_logger());
	
	/* ToResearch: Apaparently you can only start timers on the constructor no matter what?*/
	RCLCPP_INFO(this->get_logger(), "Started carrot waypoint targeting routine on { %s }", __PRETTY_FUNCTION__ );
	auto interval = std::chrono::duration<double>(1.0 / m_frequency);
	this->m_timer = this->create_wall_timer(interval, std::bind(&TargetWaypoint::predict, m_target_waypoint));


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
#ifdef __FSIPLEIRIA_2D_ONLY__
	void SpacNode::waypoint_callback(const geometry_msgs::msg::Pose2D::SharedPtr msg){
		m_target_waypoint->s_CurrentTargetWaypoint(msg);
		// TODO: some logs would be nice
	}
#else
	void SpacNode::waypoint_callback(const geometry_msgs::msg::Pose::SharedPtr msg){
		m_target_waypoint->s_CurrentTargetWaypoint(msg);
		// TODO: some logs would be nice
	}
#endif


