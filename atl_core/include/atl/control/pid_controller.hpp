#ifndef ATL_CONTROL_PID_CONTROLLER_HPP
#define ATL_CONTROL_PID_CONTROLLER_HPP

#include <float.h>
#include <math.h>
#include <iostream>

namespace atl {

class PID {
public:
  double error_prev;
  double error_sum;

  double error_p;
  double error_i;
  double error_d;

  double k_p;
  double k_i;
  double k_d;

  PID(void);
  PID(double k_p, double k_i, double k_d);
  double calculate(double setpoint, double input, double dt);
  void reset(void);
};

}  // namespace atl
#endif