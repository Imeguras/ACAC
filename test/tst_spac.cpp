/** ==========================================
* @title:  Spac Operational Test Suite
* @author: João Vieira
* @date:   2023-06-14
==========================================**/

#include "tst_spac.h"



TEST(tst_spac, spac_NodeSanityTest){
	//instantiate spac node
	auto ff = std::make_shared<SpacNode>(); 
	auto k = rclcpp::spin(ff);
	//Expect SpacNode g_NodeName to return DRIVEMODEL_NODE_NAME
	EXPECT_EQ(ff->g_NodeName(), DRIVEMODEL_NODE_NAME);
	//call for the rclcpp destructor for node ff
	ff.reset();
	//check if it dies
	EXPECT_EQ(ff.use_count(), 0);

	
}

// Check if altering a parameter 