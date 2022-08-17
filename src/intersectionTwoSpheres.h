/* P. Palacios Alonso 2022. 
   Generates a random point in the intersection between two spheres.
*/

#ifndef INTERSECTIONTWOSPHERES_H
#define INTERSECTIONTWOSPHERES_H
#include "rotationMatrix.h"
#include "third_party/saruprung.h"
#include "third_party/vector_algebra.h"

/*Checks if there is an intersection between the two spheres*/
void checkExistingSolution(real3 c1, real3 c2, real r1, real r2){
  real dist2 = dot(c1-c2,c1-c2);
  real maxDistance2 = (r1+r2)*(r1+r2);
  if (dist2>maxDistance2){
    std::cerr<<"[ERROR] THERE IS NO INTERSECTION BETWEEN THE TWO SPHERES. THE SPHERES ARE TOO FAR APART.\n"<<std::endl;
    exit(1);
  }
  real minDistance2 = (r1-r2)*(r1-r2);
  if (dist2<minDistance2){
    std::cerr<<"[ERROR] THERE IS NO INTERSECTION BETWEEN THE TWO SPHERES. THE CENTERS OF THE SPHERES ARE TOO CLOSE\n"<<std::endl;
    exit(1);
  }
}

real3 generateRandomPointInIntersection(Saru rng, real3 c1, real3 c2, real r1, real r2){
  checkExistingSolution(c1,c2,r1,r2);
  /* Change to a reference frame, S', where c1 is in (0,0,0) and c2 in the z axis*/
  c2-=c1;
  real3 rotationAxis = make_real3(c2.y,-c2.x,0);
  real normRotationAxis2 = dot(rotationAxis,rotationAxis);
  if (normRotationAxis2!= 0)
    rotationAxis/=sqrt(dot(rotationAxis,rotationAxis));
  real newc2center2 = dot(c2,c2);
  real normc2 = sqrt(newc2center2);
  /* Compute the angle of the rotation from the frame S to S'*/
  real ct = c2.z/normc2;
  real st = sqrt(ct<1?1-ct*ct:0.0);
  /* Compute the value of z' where is the circumference of the intersection between the two spheres*/
  real z = (r1*r1-r2*r2+newc2center2)/(2*normc2);
  /* Compute the radius of the circumference of the intersection*/
  real circumferenceRadius = sqrt(r1*r1-z*z);
  /* Generates a random point in the circumference.*/
  real randNumber  = rng.f();
  real phi = 2*M_PI*randNumber;
  real x = circumferenceRadius*cos(phi);
  real y = circumferenceRadius*sin(phi);
  /* Move the generated point to the laboratory frame. */
  real3 pointLabFrame = rotateVector(rotationAxis, ct,-st, make_real3(x,y,z))+c1;
  real3 c22 = rotateVector(rotationAxis, ct,-st, make_real3(0,0,normc2));
  return pointLabFrame;  
}
#endif
