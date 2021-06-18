# Reitrace

A school project to build a working raytracing library from scratch over the course of the semester. Included are several demo programs which make use of the capabilites implemened in each assignment, numbered HW1-HW4. Scenes are defined using text based 'driver' files and allow importing and transforming of .obj models, sphere primatives, and colored lights. Custom materials are also supported and defined within driver files which allow full control over diffusive, specular, and reflective properties of the objects they are applied to, as well as basic texturing of .objs.

## How to Build
In the top level directory of this project, simply run 'cmake ./;make'

Note: To build previous assignments, edit CMakeLists.txt, find hw\<number>.cpp and change number to the number of the assignment. Don't forget to update the tarball target as well!

## How to Run
~HW1: './render \<driverfile>'~

HW2+: './render \<driverfile> <output.ppm>'

## The Output
~HW1:~
~Outputted .obj files will be as defined in the driver file.~
~Outputted transform_new.txt files will be in the format '\<model>_transform_new0<order model was loaded>', where the order it was loaded will be either an integer, starting from 1.~

HW2 - HW4:
Outputted .ppm files will be of the resolution defined in the driver, with the name passed at runtime (if a grader is reading this, I suggest this parameter passing be moved to the driver file for consistency).

HW4:
Does not perform Phong Shading. Sorry. Only sphere refraction was implemented.

HW5:
Adds Phong Shading not present in HW4 as well as texture mapping to models. Unfortunately, the changes required to implement this means HW1 cannot be compiled from this version of the library, as the data-structures it reads from to output transformed .obj files no longer exist. Other HWs are untested.
