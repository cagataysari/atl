#ifndef ATL_VISION_CAMERA_CONFIG_HPP
#define ATL_VISION_CAMERA_CONFIG_HPP

#include <yaml-cpp/yaml.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "atl/utils/utils.hpp"

namespace atl {

class CameraConfig {
public:
  bool loaded;

  int index;
  int image_width;
  int image_height;

  float shutter_speed;
  float exposure_value;
  float gain_value;
  Vec3 lambda;
  float alpha;

  cv::Mat camera_matrix;
  cv::Mat rectification_matrix;
  cv::Mat distortion_coefficients;
  cv::Mat projection_matrix;

  bool imshow;
  bool snapshot;
  bool showfps;

  CameraConfig(void);
  int load(const std::string &config_file);
  void print(void);
};

}  // namespace atl
#endif