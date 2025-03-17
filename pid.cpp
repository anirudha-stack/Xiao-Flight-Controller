#include "pid.h"

// Initialize PID controller with given gains and initial setpoint
void initPID(PIDController &pid, float kp, float ki, float kd, float minOutput, float maxOutput, float initialSetpoint) {
    pid.kp = kp;
    pid.ki = ki;
    pid.kd = kd;
    pid.setpoint = initialSetpoint; // Set initial pitch as reference
    pid.lastError = 0.0;
    pid.integral = 0.0;
    pid.minOutput = minOutput;
    pid.maxOutput = maxOutput;
}

// Compute PID output
float computePID(PIDController &pid, float measuredValue, float dt) {
    float error = pid.setpoint - measuredValue;
    pid.integral += error * dt;
    float derivative = (error - pid.lastError) / dt;
    pid.lastError = error;

    // Compute output
    float output = (pid.kp * error) + (pid.ki * pid.integral) + (pid.kd * derivative);

    // Constrain output
    output = constrain(output, pid.minOutput, pid.maxOutput);
    return output;
}

// Apply PID output to motors
void applyMotorControl(float pidOutput) {
    int basePWM = 20;  // Base power for motors
    int motorRightPWM = constrain(basePWM + pidOutput, 0, 255);
    int motorLeftPWM = constrain(basePWM - pidOutput, 0, 255);

    analogWrite(MOTOR_FRONT_RIGHT, motorRightPWM);
    analogWrite(MOTOR_BACK_LEFT, motorLeftPWM);
}
