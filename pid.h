#ifndef PID_H
#define PID_H

#include <Arduino.h>
#include "pinConfig.h"

// PID Structure
typedef struct {
    float kp;  // Proportional gain
    float ki;  // Integral gain
    float kd;  // Derivative gain
    float setpoint; // Initial starting position
    float lastError;
    float integral;
    float minOutput;
    float maxOutput;
} PIDController;

// PID Controller Initialization (with initial pitch bias)
void initPID(PIDController &pid, float kp, float ki, float kd, float minOutput, float maxOutput, float initialSetpoint);

// PID Compute Function
float computePID(PIDController &pid, float measuredValue, float dt);

// Function to control motors based on PID output
void applyMotorControl(float pidOutput);

#endif // PID_H
