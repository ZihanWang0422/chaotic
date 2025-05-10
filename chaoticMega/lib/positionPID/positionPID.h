
#include <Arduino.h>
#define PID_H
 
/**
 *  PID controller class
 */
class PosPidController
{
public:
    /**
     *  
     * @param P - Proportional gain 
     * @param I - Integral gain
     * @param D - Derivative gain 
     * @param ramp - Maximum speed of change of the output value
     * @param limit - Maximum output value
     */
    PosPidController(float P, float I, float D, float ramp, float limit);
    ~PosPidController() = default;
 
    float operator() (float error);
 
    float P; //!< Proportional gain 
    float I; //!< Integral gain 
    float D; //!< Derivative gain 
    float output_ramp; //!< Maximum speed of change of the output value
    float limit; //!< Maximum output value
 
protected:
    float integral_prev; //!< last integral component value
    float error_prev; //!< last tracking error value
    unsigned long timestamp_prev; //!< Last execution timestamp
    float output_prev;  //!< last pid output value
};