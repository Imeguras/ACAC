#include "tst_target.h"

TEST(tst_target, check_angle_straight){
	
	nav_msgs::msg::Odometry odom_check_angle_straight;
	#ifdef __FSIPLEIRIA_2D_ONLY__
		geometry_msgs::msg::Pose2D waypoint_check_angle_straight;
		waypoint_check_angle_straight.x = 0;
		waypoint_check_angle_straight.y = 0;
		waypoint_check_angle_straight.theta = 0;

	#else 
		geometry_msgs::msg::Pose waypoint_check_angle_straight;
		//it would make too much spaghetti... it sets things to zero


	#endif
	
	TargetWaypoint target = setupAngles( odom_check_angle_straight, waypoint_check_angle_straight);
	fs_KinematicsFloat_t f = target.predict_trackAngle();
	
	EXPECT_FLOAT_EQ(f, (fs_KinematicsFloat_t)0);
}

TEST(tst_target, check_angle_90){
	nav_msgs::msg::Odometry odom_check_angle_90;
	#ifdef __FSIPLEIRIA_2D_ONLY__
		geometry_msgs::msg::Pose2D waypoint_check_angle_90;
		waypoint_check_angle_90.x = 5;
		waypoint_check_angle_90.y = 0;
	#else
		geometry_msgs::msg::Pose waypoint_check_angle_90;
		//set the position to 5,0,0
		waypoint_check_angle_90.position.x = 5;
		waypoint_check_angle_90.position.y = 0;
		waypoint_check_angle_90.position.z = 0;
	#endif
	TargetWaypoint target2 = setupAngles( odom_check_angle_90, waypoint_check_angle_90);
	fs_KinematicsFloat_t f = target2.predict_trackAngle();
	
	EXPECT_FLOAT_EQ(f, (fs_KinematicsFloat_t)M_PI_2);

}
TEST(tst_target, check_Shrimple_FixAngle){
	//create a random msg::Odometry
	nav_msgs::msg::Odometry odom_check_fixangle;
	//get a random number between 0 and 2pi
	fs_KinematicsFloat_t random_angle=rand()/RAND_MAX * 2 * M_PI;
	//set the yaw of the quarternion to that angle
	odom_check_fixangle.pose.pose.orientation.z = sin(random_angle/2);
	odom_check_fixangle.pose.pose.orientation.w = cos(random_angle/2);
	#ifdef __FSIPLEIRIA_2D_ONLY__
	geometry_msgs::msg::Pose2D irrelevant;
	#else
	geometry_msgs::msg::Pose irrelevant;
	#endif
	TargetWaypoint target3 = setupAngles( odom_check_fixangle, irrelevant );
	

	auto ret= target3.current_Angle();
	EXPECT_FLOAT_EQ(ret, random_angle);
}

#ifdef __FSIPLEIRIA_2D_ONLY__
	TargetWaypoint setupAngles( nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose2D waypoint){
		
		TargetWaypoint target;
		//odom at a zero state
		nav_msgs::msg::Odometry::SharedPtr ptrOdom = std::make_shared<nav_msgs::msg::Odometry>(odom);
		
		target.s_Odometry(ptrOdom);

		geometry_msgs::msg::Pose2D::SharedPtr ptrWayp = std::make_shared<geometry_msgs::msg::Pose2D>(waypoint);

		target.s_CurrentTargetWaypoint(ptrWayp);
		return target;
		
	}
#else
	TargetWaypoint setupAngles( nav_msgs::msg::Odometry odom, geometry_msgs::msg::Pose waypoint){
	
		
		TargetWaypoint target;
		//odom at a zero state
		nav_msgs::msg::Odometry::SharedPtr ptrOdom = std::make_shared<nav_msgs::msg::Odometry>(odom);
		
		target.s_Odometry(ptrOdom);

		geometry_msgs::msg::Pose::SharedPtr ptrWayp = std::make_shared<geometry_msgs::msg::Pose>(waypoint);

		target.s_CurrentTargetWaypoint(ptrWayp);
		return target;
	}
#endif


