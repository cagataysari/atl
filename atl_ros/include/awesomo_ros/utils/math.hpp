#ifndef ATL_ROS_UTILS_MATH_HPP
#define ATL_ROS_UTILS_MATH_HPP

#include <random>

#include <Eigen/Geometry>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>


namespace atl {

int geoQuatToQuat(const geometry_msgs::Quaternion in,
                  Eigen::Quaterniond &out) {
  out = Eigen::Quaterniond(in.w, in.x, in.y, in.z);
}

int tfQuatToQuat(tf::Quaternion in, Eigen::Quaterniond &out) {
  out = Eigen::Quaterniond(in.w(), in.x(), in.y(), in.z());
}

}  // end of atl namespace
#endif
