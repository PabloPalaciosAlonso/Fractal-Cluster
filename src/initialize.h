/* P. Palacios Alonso 2022. 
   Functions needed to initialize the program and a struct with the input parameters
*/

#ifndef INITIALIZE_H
#define INITIALIZE_H

#include"defines.h"
#include<cstring>
#include"third_party/vector_algebra.h"

struct Parameters{
  int nParticles = -1; // Number of particles in the cluster
  real radius = -1; //Radius of the particles
  real Df = -1; //Fractal dimension of the cluster
  real kf = -1; //Fractal prefactor of the cluster
  std::string filename = "";
  bool printHelp = false;
#ifdef SINGLE_PRECISION
  bool doublePrecision = false;
#else
  bool doublePrecision = true;
#endif
};

void print_help();

/* Read the parameters from the command line */
void processCommandLineArguments(int argc, char *argv[], Parameters &params){
  fori(0,argc){
    if(strcmp(argv[i], "-N")==0)
      params.nParticles = atoi(argv[i+1]);
    if(strcmp(argv[i], "-radius")==0)
      params.radius = strtod(argv[i+1], nullptr);
    if(strcmp(argv[i], "-Df")==0)
      params.Df = strtod(argv[i+1], nullptr);
    if(strcmp(argv[i], "-kf")==0)
      params.kf = strtod(argv[i+1], nullptr);
    if(strcmp(argv[i], "-filename")==0)
      params.filename = argv[i+1];
    if(strcmp(argv[i], "-h")==0)
      params.printHelp = true;
    
  }

  if (params.printHelp){
    print_help();
    exit(1);
  }
  if (params.nParticles<1){
    std::cerr<<"[ERROR] NO VALID NUMBER OF PARTICLES WAS GIVEN.\n"<<std::endl;
    print_help(); exit(1);
  }
  if (params.radius<0){
    std::cerr<<"[ERROR] NO VALID RADIUS WAS GIVEN.\n"<<std::endl;
    print_help(); exit(1);
  }
  if (params.Df<0){
    std::cerr<<"[ERROR] NO VALID FRACTAL DIMENSION WAS GIVEN.\n"<<std::endl;
    print_help(); exit(1);
  }
  if (params.kf<0){
    std::cerr<<"[ERROR] NO VALID FRACTAL PREFACTOR WAS GIVEN.\n"<<std::endl;
    print_help(); exit(1);
  }
}

void print_help(){
  printf("P. Palacios Alonso 2022.\n");
  printf("\n");
  printf("Generates a random set of positions of particles in a fractal cluster\n");
  printf("In a fractal cluster the number of particles in the cluster and its gyration radius verifies:\n");
  printf("N = kf * (Rg/radius)^Df\n");
  printf("Where:\n");
  printf(" N = Number of particles in the cluster.\n");
  printf(" Radius = Radius of the particles.\n");
  printf(" Df = Fractal dimension of the cluster.\n");
  printf(" kf = Fractal prefactor of the cluster.\n");
  printf(" Rg = Gyration radius of the cluster (Rg^2 = 1/N * sum (ri-cm)^2.\n");
  printf("\n");
  printf("Usage: fc [INPUTS]\n\n");
  printf("Required inputs:\n");
  printf(" -N \n");
  printf(" Number of the particles in the cluster.\n\n");
  printf(" -Radius \n");
  printf(" Radius of the particles.\n\n");
  printf(" -Df \n");
  printf(" Fractal dimension of the cluster.\n\n");
  printf(" -kf \n");
  printf(" Fractal prefactor of the cluster.\n\n");
  printf("Optional inputs:\n");
  printf(" -filename \n");
  printf(" Name of a file in which to store the positions of the particles.\n");
  printf(" If no filename is provided the positions are displayed in the comand line.\n\n");
  printf(" -h \n");
  printf(" Prints this help message.\n\n");  
}
#endif
