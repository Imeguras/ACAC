#include "tst_spac.h"



TEST(tst_spac, spac_NodeSanityTest){
	//instantiate spac node
	auto ff = std::make_shared<SpacNode>(); 
	auto k = rclcpp::spin(ff);
	
	
	
}