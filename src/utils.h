#ifndef UTILS_H_
#define UTILS_H_


/**
* @class These macros are supposed to be constants for the vehicle dimensions 
*/


/**
* @brief The distance between the front and rear axles
*/
#ifdef VOIDSTER
	#define WHEELBASE 1.550f
	#define MAX_STEERING (2*M_PI/9)
#endif
#ifdef ANT
	#define WHEELBASE 1.550f
	#define MAX_STEERING (2*M_PI/9) // TODO check it
#endif



#endif // UTILS_H_