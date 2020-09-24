//A. Groeling - 9/20/20
#ifndef LINALG_H
#define LINALG_H

#include "lib/Eigen/Core"

//data types for homogeneous calculations
typedef Eigen::Matrix<double, 4, 4> Matrix4d;
typedef Eigen::Matrix<double, 4, 1> Vector4d;
typedef Eigen::Matrix<double, 4, Eigen::Dynamic> Matrix4Xd;

//datatypes for cartesian calculations
typedef Eigen::Matrix<double, 3, 3> Matrix3d;
typedef Eigen::Matrix<double, 3, 1> Vector3d;
typedef Eigen::Matrix<double, 3, Eigen::Dynamic> Matrix3Xd;

#endif
