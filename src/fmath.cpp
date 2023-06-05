#include "fmath.h"
#include "utils.h"

/**
* @brief Public Constructor for the PID_Controller class
*/
PID_Controller::PID_Controller(fs_PidFloat_t Kp, fs_PidFloat_t Ki, fs_PidFloat_t Kd): PID_Controller(){
	s_Tunings(Kp, Ki, Kd); 
}
/**
* @brief Constructor meant to setup everything to 0 It should not be used directly, and its only public so that it can be used in the other constructor
*/
PID_Controller::PID_Controller(){
	kp=0;
	ki=0;
	kd=0;
	error=0;
	error_prev=0;
	error_sum=0;
}
fs_PidFloat_t PID_Controller::compute(fs_PidFloat_t setpoint, fs_PidFloat_t input){
	error=setpoint-input;
	error_sum+=error;
	fs_PidFloat_t output=kp*error+ki*error_sum+kd*(error-error_prev);
	error_prev=error;
	return output;
}
/**
* @brief Setter for the PID Tunings/Constants
*/
int PID_Controller::s_Tunings(fs_PidFloat_t Kp, fs_PidFloat_t Ki, fs_PidFloat_t Kd){
	kp=Kp;
	ki=Ki;
	kd=Kd;
	return 0;
}
fs_PidFloat_t PID_Controller::g_Proportion(){
	return kp;
}
fs_PidFloat_t PID_Controller::g_Integral(){
	return ki;
}
fs_PidFloat_t PID_Controller::g_Derivative(){
	return kd;
}


Steering_Reverse_Kinematics::Steering_Reverse_Kinematics(){
	
}
fs_KinematicsFloat_t Steering_Reverse_Kinematics::track_ComputeSteeringAngle(fs_KinematicsFloat_t track_angle, fs_KinematicsFloat_t track_width ){
	fs_KinematicsFloat_t turning_radius = VOIDSTER_WHEELBASE / std::tan(track_angle);
	fs_KinematicsFloat_t inner_angle = std::atan(VOIDSTER_WHEELBASE / (turning_radius - (track_width / 2)));
    fs_KinematicsFloat_t outer_angle = std::atan(VOIDSTER_WHEELBASE / (turning_radius + (track_width / 2)));
	fs_KinematicsFloat_t steering_angle=(inner_angle+outer_angle)/2;

	return steering_angle;
}