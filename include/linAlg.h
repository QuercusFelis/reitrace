//A. Groeling - 9/20/20
#ifndef LINALG_H
#define LINALG_H

#include "Eigen/Core"

//data types for homogeneous calculations
typedef Eigen::Matrix<float, 4, 4> Matrix4f;
typedef Eigen::Matrix<float, 4, 1> Vector4f;
typedef Eigen::Matrix<float, 4, Eigen::Dynamic> Matrix4Xf;

//datatypes for cartesian calculations
typedef Eigen::Matrix<float, 3, 3> Matrix3f;
typedef Eigen::Matrix<float, 3, 1> Vector3f;
typedef Eigen::Matrix<float, 3, Eigen::Dynamic> Matrix3Xf;

#endif
