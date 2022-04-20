#include <stdio.h>
#include <math.h>
#include "SpiceUsr.h"
#include "SpiceZfc.h"

int main(){
    SpiceDouble   et;
    SpiceDouble   sunPosition[6];
    SpiceDouble   landingPosition[3];
    SpiceDouble   lt;

    printf("Executing SPK Code \n");
    
    /*
        load kernels: LSK and MGS and DE SPKs
    */
    furnsh_c ( "../kernals/naif0008.tls" );
    furnsh_c ( "../kernals/moon_080317.tf" );
    furnsh_c ( "../kernals/moon_assoc_me.tf" );
    furnsh_c ( "../kernals/de421.bsp" );
    furnsh_c ( "../kernals/moon_pa_de421_1900-2050.bpc" );

    printf("Loaded Kernels \n");

    /*
        landing site data
    */
    SpiceDouble moonRadius = 1737400;                // m
    SpiceDouble elevation = 1831;                    // m
    SpiceDouble latitude = -86.79815;
    SpiceDouble longitude = -21.15030;
    SpiceDouble radius = moonRadius + elevation;     // m
    
    latrec_c(radius, longitude * rpd_c(), latitude * rpd_c(), landingPosition);

    printf("Landing Site Position \n");
    printf("X:%f Y:%f Z:%f \n", landingPosition[0], landingPosition[1], landingPosition[2]);
    
    /*
        convert UTC to ET
    */
    str2et_c ( "2022 DEC 07 00:00", &et );

    printf("Converted UTC to ET \n");

    /*
        compute geometric sunPosition of Sun relative to Moon
    */
    spkezr_c ( "SUN", et, "MOON_ME", "LT+S", "MOON", sunPosition,
                &lt );

    printf("Sun Position relative to Moon \n");
    printf("X:%f Y:%f Z:%f \n", sunPosition[0], sunPosition[1], sunPosition[2]);

    /*
    */
    double sunPosition_Lander[3];
    for(int i = 0; i < 3; i++)
        sunPosition_Lander[i] = (sunPosition[i] * 1000) - landingPosition[i];

    double distance = sqrt((sunPosition_Lander[0] * sunPosition_Lander[0]) + 
                           (sunPosition_Lander[1] * sunPosition_Lander[1]) + 
                           (sunPosition_Lander[2] * sunPosition_Lander[2]));

    for(int i = 0; i < 3; i++)
        sunPosition_Lander[i] /= distance;

    printf("Sun Position (Unit Vector) relative to Lander \n");
    printf("X:%f Y:%f Z:%f \n", sunPosition_Lander[0], sunPosition_Lander[1], sunPosition_Lander[2]);

    return 0;
}