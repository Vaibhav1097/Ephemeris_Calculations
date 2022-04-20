#include "rotationCalculation.h"

Rotation3 alignVectors(Vector3 v1, Vector3 v2){
    v1 /= v1.norm();
    v2 /= v2.norm();

    Vector3 axis = v1.cross(v2);
    double cos_theta = v1.dot(v2);
    double k = 1 / (1 + cos_theta);

    double R_11 = (k * axis[0] * axis[0]) + cos_theta;
    double R_12 = (k * axis[1] * axis[0]) - axis[2];
    double R_13 = (k * axis[2] * axis[0]) + axis[1];
    double R_21 = (k * axis[0] * axis[1]) + axis[2];
    double R_22 = (k * axis[1] * axis[1]) + cos_theta;
    double R_23 = (k * axis[2] * axis[1]) - axis[0];
    double R_31 = (k * axis[0] * axis[2]) - axis[1];
    double R_32 = (k * axis[1] * axis[2]) + axis[0];
    double R_33 = (k * axis[2] * axis[2]) + cos_theta;

    Rotation3 R;
    R << R_11, R_12, R_13, R_21, R_22, R_23, R_31, R_32, R_33;

    std::cout << "V1 " << std::endl;
    std::cout << v1 << std::endl;
    std::cout << "V2 " << std::endl;
    std::cout << v2 << std::endl;

    std::cout << "Rotated Vector (v2' = R x v1)" << std::endl;
    std::cout << (R * v1) << std::endl;

    return R;
}

int main(){
    double* sunPosition_Lander = new double(3);
    ephemerisCalculation(sunPosition_Lander);

    Vector3 v1;
    Vector3 v2;

    Rotation3 rotationMatrix(3, 3);

    v1 << sunPosition_Lander[0], sunPosition_Lander[1], sunPosition_Lander[2];
    v2 << 1, 1, 1;

    Rotation3 R = alignVectors(v1, v2);

    return 0;
}
