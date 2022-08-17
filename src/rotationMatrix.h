/* P. Palacios Alonso 2022. 
   A struct that encodes a rotation matrix and define the functions to rotate a vector
*/
#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H
#include "third_party/vector_algebra.h"

// 

struct RotationMatrix{
  /*                __            __
                    |v1.x v1.y v1.z|
    roationMatrix = |v2.x v2.y v2.z|
                    |v3.x v3.y v3.z|
                    --            --
  */
  
  real3 v1;
  real3 v2;
  real3 v3;
  RotationMatrix(real3 v, real ct, real st){
    real ct_1 = 1-ct;
    v1.x =  ct     + v.x*v.x*ct_1;
    v1.y = -v.z*st + v.x*v.y*ct_1;
    v1.z =  v.y*st + v.x*v.z*ct_1;

    v2.x =  v.z*st + v.x*v.y*ct_1;
    v2.y =  ct     + v.y*v.y*ct_1;
    v2.z = -v.x*st + v.y*v.z*ct_1;
    
    v3.x = -v.y*st + v.x*v.z*ct_1;
    v3.y =  v.x*st + v.y*v.z*ct_1;
    v3.z =  ct     + v.z*v.z*ct_1;
  }
  
RotationMatrix(real3 v, real theta):
  RotationMatrix(v, cos(theta), sin(theta)){}
  
};


real3 rotateVector(RotationMatrix R, real3 v){
  return make_real3(dot(R.v1,v), dot(R.v2,v), dot(R.v3,v));
}

real3 rotateVector(real3 vrot, real ctheta, real stheta, real3 v){
  RotationMatrix R(vrot, ctheta, stheta);
  return rotateVector(R,v);
}

real3 rotateVector(real3 vrot, real theta, real3 v){
  return rotateVector(vrot, cos(theta), sin(theta), v);
}
#endif
