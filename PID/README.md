# PID

PID controller implementation written in C.

Note on 'derivative-on-measurement': Since the 'error signal' effectively going into the differentiator does not depend on the setpoint: e[n] = 0 - measurement, and therefore (e[n] - e[n - 1]) = (0 - measurement) - (0 - prevMeasurement) = -Kd * (measurement - prevMeasurement). (Note the minus sign compared to derivative-on-error!)
I've included the minus sign in the code, so gains will have the effect as normal.



用 C 编写的 PID 控制器实现。

关于“测量导数”的注释：

由于有效进入微分器的“误差信号”不依赖于设定点：

e[n] = 0 - 测量，因此 (e[n] - e[n - 1]) = (0 - 测量值) - (0 - 上一次测量值) = -Kd * (测量值 - 上一次测量值)。 （注意与错误导数相比的减号！）

我在代码中包含了减号，因此增益将具有正常的效果。
