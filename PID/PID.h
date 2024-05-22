#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct
{

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

	/* 微分低通滤波器时间常数 */
	float tau;

	/* Output limits */
	float limMin;
	float limMax;

	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* Sample time (in seconds) */
	float dT;

	/* 控制器“内存” */
	float integrator;
	float prevError; /* Required for integrator */
	float differentiator;
	float prevMeasurement;		 /* Required for differentiator */

	unsigned long prevTimestamp; /* timestamp of last execution */

	/* Controller output */
	float out;

} PIDController;

void PIDController_Init(PIDController *pid);
float PIDController_Update(PIDController *pid, float setpoint, float measurement);

#endif
