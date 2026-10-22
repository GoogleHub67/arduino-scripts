/*
  62_pid_antivindup
  Implements an advanced Proportional-Integral-Derivative (PID) control algorithm
  featuring a dynamic clamping Anti-Windup mechanism to prevent integral saturation
  when actuator outputs hit physical system limits.
*/

struct PIDController {
  float Kp, Ki, Kd;
  float integralSum;
  float lastError;
  float outMin, outMax;
};

PIDController myLoop = { 2.5, 1.2, 0.5, 0.0, 0.0, 0.0, 255.0 }; // Scaled for 8-bit PWM actuators

float updatePID(PIDController &pid, float setpoint, float currentInput, float dt) {
  float error = setpoint - currentInput;
  
  // 1. Proportional step computation calculation
  float pTerm = pid.Kp * error;
  
  // 2. Derivative step calculation tracking slope speed differentials
  float dTerm = pid.Kd * ((error - pid.lastError) / dt);
  
  // 3. Compute active raw control loop tracking indicators before integrating
  float preClampedOutput = pTerm + pid.integralSum + dTerm;
  
  // 4. Actuator limit verification tracking system boundaries
  float clampedOutput = preClampedOutput;
  if (clampedOutput > pid.outMax) clampedOutput = pid.outMax;
  else if (clampedOutput < pid.outMin) clampedOutput = pid.outMin;
  
  // 5. Dynamic Clamping Anti-Windup Integration Logic Architecture
  // Only integrate the tracking error parameters if the output channel is un-clamped
  // or if the error sign works to pull the controller out of saturation states.
  bool isSaturated = (preClampedOutput != clampedOutput);
  bool sameSign = ((error > 0 && preClampedOutput > 0) || (error < 0 && preClampedOutput < 0));
  
  if (!isSaturated || !sameSign) {
    pid.integralSum += pid.Ki * error * dt;
  }
  
  pid.lastError = error;
  return clampedOutput;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\n--- Precision Anti-Windup PID Engine Engaged ---");
}

void loop() {
  float controlSignal = updatePID(myLoop, 100.0, 45.2, 0.1);
  Serial.print("System Control Out value: ");
  Serial.println(controlSignal);
  delay(100);
}
