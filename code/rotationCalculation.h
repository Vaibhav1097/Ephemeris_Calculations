#pragma once

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <SpiceUsr.h>

extern "C" {
#include "ephemerisCalculation.h"
}

typedef Eigen::Matrix<double, 3, 1> Vector3;
typedef Eigen::Matrix<double, 3, 3> Rotation3;