#include<iostream>
#include<string>
#include<fstream>
#include"initialize.h"
#include"fractalCluster.h"
#include"third_party/vector_algebra.h"
#include"third_party/saruprung.h"
#include<vector>

void writePositions(std::vector<real3> &pos, Parameters params){
  if (params.filename.length()>0){
    std::ofstream file(params.filename);
    fori(0,params.nParticles){
      file<<pos[i].x<<" "<<pos[i].y<<" "<<pos[i].z<<"\n";
    }
  }else {
    fori(0,params.nParticles){
      std::cout<<pos[i].x<<" "<<pos[i].y<<" "<<pos[i].z<<"\n";
    }
  }
}

int main(int argc, char* argv[]){
  Parameters params;
  processCommandLineArguments(argc, argv, params);
  auto posParticles = generateFractalCluster(params);
  writePositions(posParticles, params);
  return 0;
}
