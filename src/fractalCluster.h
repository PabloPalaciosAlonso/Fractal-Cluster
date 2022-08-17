/* P. Palacios Alonso. 2022
   Generates a random cluster that veryfies N = kf*(Rg/radius)^Df with:
   a = radius of the monomers
   Rg = Gyration radius of the cluster
   Df = Fractal dimension of the cluster
   kf = Prefactor

   The algorithm followed to build the clusters is described in [1].

   [1] https://doi.org/10.1006/jcis.2000.7027
*/

#include <vector>
#include "initialize.h"
#include "intersectionTwoSpheres.h"
#include "third_party/saruprung.h"
#include "third_party/vector_algebra.h"
#include <chrono>
/* Computes the radius of the sphere where we must put the
   new monomer to keep constant the fractal dimension.
   Ni = number of particles that the claser will have
   when we add the new particle.
*/

using namespace std;
real computeRadiusValidPos(real Df, real kf, real radius, int Ni){
  real t1 = Ni*radius*radius/(Ni-1);
  real t2 = Ni*pow(Ni/kf,2./Df);
  real t3 = -(Ni-1)*pow(real(Ni-1)/kf,2./Df)-1;
  return sqrt(t1*(t2+t3));
}

/* 
   Checks if the particle i is valid for adding a particle j keeping constant Df. 
   There is a intersection between two spheres when the distance between the centers
   is in the range(|r1-r2|,|r1+r2|)
*/
bool isValidParticle(real3 c1, real3 c2, real r1, real r2){
  real dist2 = dot(c1-c2,c1-c2);
  real maxDistance2 = (r1+r2)*(r1+r2);
  if (dist2>maxDistance2) return false;
  real minDistance2 = (r1-r2)*(r1-r2);
  return dist2>minDistance2;
}

/* Checks if the new particle is overlaping with any other of the cluster*/
bool areParticlesOverlaping(std::vector<real3> pos, real3 newpos, real sigma2, int Ni){
  for (int i = 0; i<Ni-1; i++){
    real3 rij = pos[i]-newpos;
    real dist2 = dot(rij,rij);
    if (dist2<sigma2){
      return true;
    }
  }
  return false;
}      

/* Find all the particles where we can link a new particle keeping constant Df*/
std::vector<int> findValidParticles(std::vector<real3> &pos, real3 cm,
				    real rValid, real rParticle, int Ni){
  std::vector<int> validParticles;
  for (int i = 0; i<Ni-1; i++){
    real3 posi  = pos[i];
    if (isValidParticle(cm,posi, rValid, rParticle))
      validParticles.push_back(i);
  }
  return validParticles;
}

/* Computes the position of the next particle in the cluster*/
real3 computeNewPosition(std::vector<real3> &pos, Saru &rng, real3 cm, real Df, real kf, real radius, int Ni){
  real rValid = computeRadiusValidPos(Df, kf, radius, Ni);
  real sqrt3 = 1.7320508075688772;
  if (rValid<sqrt3*radius and Ni == 3){ // The center of the third particle is overlaping with the others.
    std::cerr<<"[ERROR] It is not possible to build a cluster with:\n";
      std::cerr<<"radius = "+std::to_string(radius)+"\n";
      std::cerr<<"Df = "+std::to_string(Df)+"\n";
      std::cerr<<"kf = "+std::to_string(kf)+"\n";
      throw 1;
  }
  std::vector<int> validParticles = findValidParticles(pos, cm, rValid, 2*radius, Ni);
  int nValidParticles = validParticles.size();
  if (nValidParticles==0){
    if (Ni == 3){ /* The center of the cird particle is too far apart from the others.*/
      std::cerr<<"[ERROR] It is not possible to build a cluster with:\n";
      std::cerr<<"radius = "+std::to_string(radius)+"\n";
      std::cerr<<"Df = "+std::to_string(Df)+"\n";
      std::cerr<<"kf = "+std::to_string(kf)+"\n";
      throw 1;
    } else { /* With this configuration we can't keep adding particles to the cluster, we have to try a new configuration.*/
      throw 0;
    }
  }

  /* Pick a random particle to link the new particle.*/
  int randNumber = rng.u32()%nValidParticles;
  int particleToBond = validParticles[randNumber];
  /* Generates the position of the new particle*/
  real3 positionNewParticle = generateRandomPointInIntersection(rng, cm, pos[particleToBond], rValid, 2*radius);
  int count = 1;
  /* Repeat until finding a valid position.*/
  while(areParticlesOverlaping(pos,positionNewParticle,4*radius*radius, Ni)){
    randNumber = rng.u32()%nValidParticles;
    particleToBond = validParticles[randNumber];
    positionNewParticle = generateRandomPointInIntersection(rng, cm, pos[particleToBond], rValid, 2*radius);
    count++;
    if (count == 2*Ni){ /* There is probably no valid position where to put the new particle. */
      throw 0;
    }
  }
  return positionNewParticle;
}


/* Generates a fractal cluster such that N = kf*(Rg/radius)^Df*/
std::vector<real3> generateFractalCluster(Parameters params, uint seed){
  Saru rng(seed, params.nParticles);
  std::vector<real3> pos(params.nParticles);
  pos[0] = {0, 0, -params.radius};
  pos[1] = {0, 0,  params.radius};
  real3 cm = real3();
  for (int id = 2; id<params.nParticles; id++){
    try {
      real3 newPos = computeNewPosition(pos, rng, cm, params.Df, params.kf, params.radius, id+1);
      pos[id] = newPos;
      cm = (newPos+cm*id)/(id+1);
    } catch (int error){
      if (error == 0) {
	id = 1;
	cm = real3();
      } else if (error == 1){
	exit(1);	
      }
    }
  }
  return pos;
}

/* 
   Generates a fractal cluster with a fractal dimension equals to Df
   If no seed provided, takes a seed from the date.
*/
std::vector<real3> generateFractalCluster(Parameters params){
  uint seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  return generateFractalCluster(params, seed);
}

