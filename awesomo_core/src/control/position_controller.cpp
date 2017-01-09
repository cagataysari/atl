#include "awesomo_core/control/position_controller.hpp"


namespace awesomo {

PositionController::PositionController(void) {
  this->configured = false;

  this->dt = 0.0;
  this->x_controller = PID(0.0, 0.0, 0.0);
  this->y_controller = PID(0.0, 0.0, 0.0);
  this->z_controller = PID(0.0, 0.0, 0.0);

  this->hover_throttle = 0.0;

  this->roll_limit[0] = 0.0;
  this->roll_limit[1] = 0.0;

  this->pitch_limit[0] = 0.0;
  this->pitch_limit[1] = 0.0;

  this->setpoints  << 0.0, 0.0, 0.0;
  this->outputs << 0.0, 0.0, 0.0, 0.0;
}

int PositionController::configure(std::string config_file) {
  ConfigParser parser;

  // load config
  parser.addParam<double>("roll_controller.k_p", &this->y_controller.k_p);
  parser.addParam<double>("roll_controller.k_i", &this->y_controller.k_i);
  parser.addParam<double>("roll_controller.k_d", &this->y_controller.k_d);
  parser.addParam<double>("roll_controller.min", &this->roll_limit[0]);
  parser.addParam<double>("roll_controller.max", &this->roll_limit[1]);

  parser.addParam<double>("pitch_controller.k_p", &this->x_controller.k_p);
  parser.addParam<double>("pitch_controller.k_i", &this->x_controller.k_i);
  parser.addParam<double>("pitch_controller.k_d", &this->x_controller.k_d);
  parser.addParam<double>("pitch_controller.min", &this->pitch_limit[0]);
  parser.addParam<double>("pitch_controller.max", &this->pitch_limit[1]);

  parser.addParam<double>("throttle_controller.k_p", &this->z_controller.k_p);
  parser.addParam<double>("throttle_controller.k_i", &this->z_controller.k_i);
  parser.addParam<double>("throttle_controller.k_d", &this->z_controller.k_d);
  parser.addParam<double>("throttle_controller.hover_throttle", &this->hover_throttle);

  if (parser.load(config_file) != 0) {
    return -1;
  }

  // convert roll and pitch limits from degrees to radians
  this->roll_limit[0] = deg2rad(this->roll_limit[0]);
  this->roll_limit[1] = deg2rad(this->roll_limit[1]);
  this->pitch_limit[0] = deg2rad(this->pitch_limit[0]);
  this->pitch_limit[1] = deg2rad(this->pitch_limit[1]);

  this->configured = true;
  return 0;
}

Vec4 PositionController::calculate(Vec3 setpoints,
                                   Vec4 actual,
                                   double yaw,
                                   double dt) {
  double r, p, y, t;
  Vec3 errors, euler;
  Vec4 outputs;
  Mat3 R;

  // check rate
  this->dt += dt;
  if (this->dt < 0.01) {
    return this->outputs;
  }

  // calculate RPY errors relative to quadrotor by incorporating yaw
  errors(0) = setpoints(0) - actual(0);
  errors(1) = setpoints(1) - actual(1);
  errors(2) = setpoints(2) - actual(2);
  euler << 0.0, 0.0, actual(3);
  euler2rot(euler, 123, R);
  errors = R * errors;

  // roll, pitch, yaw and throttle (assuming NWU frame)
  // clang-format off
  r = -this->y_controller.calculate(errors(1), 0.0, this->dt);
  p = this->x_controller.calculate(errors(0), 0.0, this->dt);
  y = yaw;
  t = this->hover_throttle + this->z_controller.calculate(errors(2), 0.0, this->dt);
  t /= fabs(cos(r) * cos(p));  // adjust throttle for roll and pitch
  // clang-format o

  // limit roll, pitch
  r = (r < this->roll_limit[0]) ? this->roll_limit[0] : r;
  r = (r > this->roll_limit[1]) ? this->roll_limit[1] : r;
  p = (p < this->pitch_limit[0]) ? this->pitch_limit[0] : p;
  p = (p > this->pitch_limit[1]) ? this->pitch_limit[1] : p;

  // limit throttle
  t = (t < 0) ? 0.0 : t;
  t = (t > 1.0) ? 1.0 : t;

  // yaw first if above threshold
  if (fabs(yaw - actual(3)) > deg2rad(10.0)) {
    r = 0;
    p = 0;
  }

  // set outputs
  outputs << r, p, y, t;

  // keep track of setpoints and outputs
  this->setpoints = setpoints;
  this->outputs = outputs;
  this->dt = 0.0;

  return outputs;
}

void PositionController::reset(void) {
  this->x_controller.reset();
  this->y_controller.reset();
  this->z_controller.reset();
}

void PositionController::printOutputs(void) {
  printf("roll: %.2f\t", rad2deg(this->outputs(0)));
  printf("pitch: %.2f\t", rad2deg(this->outputs(1)));
  printf("throttle: %.2f\n", rad2deg(this->outputs(3)));
}

void PositionController::printErrors(void) {
  printf("x_controller: \n");
  printf("\terror_p: %f\t", this->x_controller.error_p);
  printf("\terror_i: %f\t", this->x_controller.error_i);
  printf("\terror_d: %f\n", this->x_controller.error_d);

  printf("y_controller: \n");
  printf("\terror_p: %f\t", this->y_controller.error_p);
  printf("\terror_i: %f\t", this->y_controller.error_i);
  printf("\terror_d: %f\t", this->y_controller.error_d);

  printf("z_controller: \n");
  printf("\terror_p: %f\t", this->z_controller.error_p);
  printf("\terror_i: %f\t", this->z_controller.error_i);
  printf("\terror_d: %f\n", this->z_controller.error_d);
}

}  // end of awesomo namespace
