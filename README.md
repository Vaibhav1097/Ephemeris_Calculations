# Ephemeris_Calculations

## Installation Instructions:
Download SPICE Toolkit from https://naif.jpl.nasa.gov/naif/toolkit_C_PC_Linux_GCC_64bit.html

Install Toolkit using following commands (https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/07_installing_toolkit.pdf): 
```
chmod u+x importSpice.csh
./importSpice.csh 
```

## Running Code:
Clone repo inside SPICE toolkit

Build and run rotationCalculation
```
g++ rotationCalculation.cpp -I../../include ../../lib/cspice.a -lm -o rotationCalculation
./rotationCalculation
```
