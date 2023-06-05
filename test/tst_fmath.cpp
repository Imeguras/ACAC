#include "tst_fmath.h"
#include "gtest/gtest.h"

TEST(tst_fmath, sanity_check_steeringAngle){
	Steering_Reverse_Kinematics srk;
	fs_KinematicsFloat_t track_angle=0.0f;
	fs_KinematicsFloat_t track_width=1.0f;
	fs_KinematicsFloat_t steering_angle=srk.track_ComputeSteeringAngle(track_angle, track_width);
	EXPECT_FLOAT_EQ(FIVECUTFLOATING(steering_angle), FIVECUTFLOATING(0.0f));

}

TEST(tst_fmath, precalculated_steeringAngle){
	Steering_Reverse_Kinematics srk;
	fs_KinematicsFloat_t track_angle=M_PI/8;
	fs_KinematicsFloat_t track_width=3.0f;
	fs_KinematicsFloat_t steering_angle=srk.track_ComputeSteeringAngle(track_angle, track_width);
	//manual calculations 
	//1/2

	EXPECT_FLOAT_EQ(FIVECUTFLOATING(steering_angle), FIVECUTFLOATING(0.446192));

}
