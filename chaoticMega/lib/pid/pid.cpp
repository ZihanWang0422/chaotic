#include "positionPid.h"
 
PosPidController::PosPidController(float P, float I, float D, float ramp, float limit)
    : P(P)
    , I(I)
    , D(D)
    , output_ramp(ramp)    // output derivative limit [volts/second]
    , limit(limit)         // output supply limit     [volts]
    , integral_prev(0.0)
    , error_prev(0.0)
    , output_prev(0.0)
{
    timestamp_prev = millis();
}
 
// PID controller function
float PosPidController::operator() (float error){
    // 计算上次调用到现在的时间Ts(秒)
    unsigned long timestamp_now = millis();
    float Ts = (timestamp_now - timestamp_prev) * 1e-3;
    // 快速修复异常 (micros overflow)，如果溢出或者出现其他异常，则Ts=0.001ms
    if(Ts <= 0 || Ts > 0.5) Ts = 1e-3; 
 
    // u(s) = (P + I/s + Ds)e(s)  //计算输入函数u(s)
    // Discrete implementations   //分元素计算
    // proportional part          //比例项
    // u_p  = P *e(k)             //u_p = P * e(k)
    float proportional = P * error;
    // Tustin transform of the integral part //积分项的双线性变换
    // u_ik = u_ik_1  + I*Ts*(ek + ek _1)/2  //u_ik = u_ik_1  + I*Ts*(ek + ek _1)/2
    float integral = integral_prev + I*Ts*(error + error_prev)*0.5;
    // antiwindup - limit the output
    integral = constrain(integral, -limit, limit);
    // Discrete derivation
    // u_dk = D(ek - ek_1)/Ts               //微分项，除以Ts，是在求微分
    float derivative = D*(error - error_prev)/Ts;
 
    // sum all the components
    float output = proportional + integral + derivative;
    // antiwindup - limit the output variable
    output = constrain(output, -limit, limit);
 
    // if output ramp defined   //这里解决超调问题。
    if(output_ramp > 0){
        // limit the acceleration by ramping the output
        float output_rate = (output - output_prev)/Ts;
        if (output_rate > output_ramp)
            output = output_prev + output_ramp*Ts;
        else if (output_rate < -output_ramp)
            output = output_prev - output_ramp*Ts;
    }
    
    // saving for the next pass
    integral_prev = integral;
    output_prev = output;
    error_prev = error;
    timestamp_prev = timestamp_now;
    return output;
}