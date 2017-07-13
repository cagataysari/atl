#ifndef ATL_ROS_NODES_IMU_NODE_HPP
#define ATL_ROS_NODES_IMU_NODE_HPP

#include <ros/ros.h>

#include <atl/atl_core.hpp>

#include "atl/ros/utils/msgs.hpp"
#include "atl/ros/utils/node.hpp"

namespace atl {

// NODE SETTINGS
#define NODE_NAME "atl_imu"
#define NODE_RATE 200

// PUBLISH TOPICS
#define IMU_TOPIC "/atl/imu"
#define JOINT_ORIENTATION_TOPIC "/atl/gimbal/joint/orientation/inertial"

class IMUNode : public ROSNode {
public:
  MPU6050 imu;
  std::string quad_frame;
  std::string gimbal_imu;

  IMUNode(int argc, char **argv) : ROSNode(argc, argv) {}
  int configure(std::string node_name, int hz);
  int publishIMU(Vec3 euler);
  int publishJointOrientation(Quaternion q);
  int loopCallback(void);
};

}  // namespace atl
#endif