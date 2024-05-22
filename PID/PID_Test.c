#include <stdio.h>
#include <stdlib.h>

#include "PID.h"

/* Controller parameters */
#define PID_KP 10.0f
#define PID_KI 0.5f
#define PID_KD 0.8f

#define PID_TAU 0.02f

#define PID_LIM_MIN -10.0f
#define PID_LIM_MAX 10.0f

#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT 5.0f

#define SAMPLE_TIME_S 0.01f

/* Maximum run-time of simulation */
#define SIMULATION_TIME_MAX 4.0f

/* Simulated dynamical system (first order) */
float TestSystem_Update(float inp);

int main()
{
    /* Initialise PID controller */
    PIDController pid = {.Kp = PID_KD,
                         .Ki = PID_KI,
                         .Kd = PID_KD,
                         .tau = PID_TAU,
                         .limMin = PID_LIM_MIN,
                         .limMax = PID_LIM_MAX,
                         .limMinInt = PID_LIM_MIN_INT,
                         .limMaxInt = PID_LIM_MAX_INT,
                         .dT = SAMPLE_TIME_S};

    PIDController_Init(&pid);

    /* Simulate response using test system */
    float setpoint = 1.0f;

    printf("Time (s)\tSystem Output\tControllerOutput\r\n");
    for (float t = 0.0f; t <= 20; t += SAMPLE_TIME_S)
    {

        /* 从系统获取测量值 */
        float measurement = TestSystem_Update(pid.out);

        /* 计算新的控制信号 */
        PIDController_Update(&pid, setpoint, measurement);

        printf("%f \r\n", pid.out);
    }

    return 0;
}

float TestSystem_Update(float inp)
{

    static float output = 0.0f;
    static const float alpha = 0.02f;

    output = (SAMPLE_TIME_S * inp + output) / (1.0f + alpha * SAMPLE_TIME_S);

    return output;
}
