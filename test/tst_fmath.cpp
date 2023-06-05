#include "tst_fmath.h"

TEST(tst_fmath, sanity_check_steeringAngle){
	Steering_Reverse_Kinematics srk;
	fs_KinematicsFloat_t track_angle=0.0f;
	fs_KinematicsFloat_t track_width=1.0f;
	fs_KinematicsFloat_t steering_angle=srk.track_ComputeSteeringAngle(track_angle, track_width);
	EXPECT_EQ(steering_angle, 0.0f);

}

