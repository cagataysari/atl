#include "atl/data/pose.hpp"

namespace atl {

Pose::Pose(
    double roll, double pitch, double yaw, double x, double y, double z) {
  Vec3 euler{roll, pitch, yaw};
  this->orientation = euler321ToQuat(euler);
  this->position << x, y, z;
}

Mat3 Pose::rotationMatrix() { return this->orientation.toRotationMatrix(); }

void Pose::printPosition() {
  std::cout << "position [";
  std::cout << std::setprecision(2) << this->position(0);
  std::cout << std::setprecision(2) << this->position(1);
  std::cout << std::setprecision(2) << this->position(2);
  std::cout << "]" << std::endl;
}

void Pose::printOrientation() {
  std::cout << "quaternion[";
  std::cout << std::setprecision(2) << this->orientation.w();
  std::cout << std::setprecision(2) << this->orientation.x();
  std::cout << std::setprecision(2) << this->orientation.y();
  std::cout << std::setprecision(2) << this->orientation.z();
  std::cout << "]" << std::endl;
}

void Pose::print() {
  this->printPosition();
  this->printOrientation();
}

} // namespace atl