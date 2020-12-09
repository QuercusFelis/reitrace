# Reitrace

## How to Build
In the top level directory of this project, simply run 'cmake ./;make'

Note: To build previous assignments, edit CMakeLists.txt, find hw\<number>.cpp and change number to the number of the assignment. Don't forget to update the tarball target as well!

## How to Run
HW1: './render \<driverfile>'

HW2 & HW3: './render \<driverfile> <output.ppm>'

## The Output
HW1:
Outputted .obj files will be as defined in the driver file.
Outputted transform_new.txt files will be in the format '\<model>_transform_new0<order model was loaded>', where the order it was loaded will be either an integer, starting from 1.

HW2 - HW4:
Outputted .ppm files will be of the resolution defined in the driver, with the name passed at runtime (if a grader is reading this, I suggest this parameter passing be moved to the driver file for consistency).

HW4:
Does not perform Phong Shading. Sorry. Only sphere refraction was implemented.
