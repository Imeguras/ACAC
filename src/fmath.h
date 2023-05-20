#ifndef FMATH_H_
#define FMATH_H_
#include <cstdint>


#ifdef __FSIPLEIRIA_PID_DOUBLE_PRECISION__
	typedef int64_t fs_PidFloat_t;
#else
	typedef int32_t fs_PidFloat_t;
#endif

class PID_Controller{
	public:
		PID_Controller(fs_PidFloat_t Kp, fs_PidFloat_t Ki, fs_PidFloat_t Kd);
		
		fs_PidFloat_t compute(fs_PidFloat_t setpoint, fs_PidFloat_t input);
		int s_Tunings(fs_PidFloat_t Kp, fs_PidFloat_t Ki, fs_PidFloat_t Kd);
		fs_PidFloat_t g_Proportion();
		fs_PidFloat_t g_Integral();
		fs_PidFloat_t g_Derivative();

	protected:
		PID_Controller();
		fs_PidFloat_t kp, ki, kd;
		fs_PidFloat_t error, error_prev, error_sum;
	
};

#ifdef __FSIPLEIRIA_KINEMATICS_DOUBLE_PRECISION__
	typedef int64_t fs_KinematicsFloat_t;
#else
	typedef int32_t fs_KinematicsFloat_t;
#endif

class Steering_Reverse_Kinematics{
	public:
		
		Steering_Reverse_Kinematics();
		fs_KinematicsFloat_t track_ComputeSteeringAngle(fs_KinematicsFloat_t track_radius, fs_KinematicsFloat_t track_angle);
};
#endif // FMATH_H_