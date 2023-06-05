#include <gtest/gtest.h>
#include <cmath>

#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>


static rclcpp::Node::SharedPtr node_;



int main(int argc, char** argv){
	rclcpp::init(argc, argv);
	node_ = rclcpp::Node::make_shared("test_node_");
	 rclcpp::spin_some(node_);


	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	//destroy node
	node_.reset();

	rclcpp::shutdown();
	return ret;
}
