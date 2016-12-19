#ifndef __AWESOMO_UTILS_MATH_HPP__
#define __AWESOMO_UTILS_MATH_HPP__

#include <Eigen/Dense>


namespace awesomo {

#ifndef __EIGEN_TYPEDEF__
#define __EIGEN_TYPEDEF__
typedef Eigen::Vector2d Vec2;
typedef Eigen::Vector3d Vec3;
typedef Eigen::Vector4d Vec4;
typedef Eigen::VectorXd VecX;

typedef Eigen::Matrix2d Mat2;
typedef Eigen::Matrix3d Mat3;
typedef Eigen::Matrix4d Mat4;
typedef Eigen::MatrixXd MatX;

typedef Eigen::Quaterniond Quaternion;
#endif

int fltcmp(double f1, double f2);
double deg2rad(double d);
double rad2deg(double r);
int euler2rot(double phi, double theta, double psi, int euler_seq, Mat3 &R);
int euler2quat(Vec3 euler, int euler_seq, Quaternion &q);
int quat2euler(Quaternion q, int euler_seq, Vec3 &euler);
int quat2rot(Quaternion q, Mat3 &R);

}  // end of awesomo namespace
#endif
