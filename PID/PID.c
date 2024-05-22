#include "PID.h"

void PIDController_Init(PIDController *pid)
{
	/* Clear controller variables */
	pid->integrator = 0.0f;
	pid->prevError = 0.0f;

	pid->differentiator = 0.0f;
	pid->prevMeasurement = 0.0f;

	pid->out = 0.0f;
}

float PIDController_Update(PIDController *pid, float setpoint, float measurement)
{
	unsigned long timestamp = micros();
	pid->dT = (timestamp - pid->prevTimestamp) * 1e-6f; 
	pid->prevTimestamp = timestamp;

	/* 误差 */
	float error = setpoint - measurement;

	/* 比例 */
	float proportional = pid->Kp * error;

	/* 积分 */
	pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->dT * (error + pid->prevError);

	/* 通过钳位器防止积分饱和 */
	pid->integrator = (pid->integrator > pid->limMaxInt) ? (pid->limMaxInt)
														 : ((pid->integrator < pid->limMinInt) ? (pid->limMinInt)
																							   : (pid->integrator));

	/* 微分 (带限微分器)  */
	pid->differentiator = -(2.0f * pid->Kd * (measurement - pid->prevMeasurement) /* 注意：测量导数，因此方程前面有负号*/
							+ (2.0f * pid->tau - pid->dT) * pid->differentiator) /
						  (2.0f * pid->tau + pid->dT);

	/* 计算输出并应用限制 */
	pid->out = proportional + pid->integrator + pid->differentiator;
	pid->out = (pid->out > pid->limMax) ? pid->limMax : ((pid->out < pid->limMin) ? pid->limMin : pid->out);

	/* 存储误差和测量值以供以后使用*/
	pid->prevError = error;
	pid->prevMeasurement = measurement;

	/* 返回控制器输出 */
	return pid->out;
}
