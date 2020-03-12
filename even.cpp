//ID: 10682923

#include <iostream>
#include "mpi.h"
using namespace std;

int main(int argc, char *argv[]){

  int rank, size;

  MPI::Init(argc, argv);
rank = MPI::COMM_WORLD.Get_rank();
size = MPI::COMM_WORLD.Get_size();

   if(rank%2 ==0){
    cout<<" I am even process "<<rank<< " of size "<<size<<endl;
     }
else{
   cout<<" I am odd process "<<rank<< "of size " <<size<<endl;

   }


       MPI::Finalize();

     return 0;

}
