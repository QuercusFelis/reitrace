//A. Groeling - 9/20/20
#ifndef LINALG_H
#define LINALG_H

#include "lib/Eigen/Core"
#include "lib/Eigen/Geometry"

//data types for homogeneous calculations
typedef Eigen::Matrix<double, 4, 4> Matrix4d;
typedef Eigen::Matrix<double, 4, 1> Vector4d;

//data types for cartesian calculations
typedef Eigen::Matrix<double, 3, 3> Matrix3d;
typedef Eigen::Matrix<double, 3, 1> Vector3d;

//flexible matrix
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
#endif
