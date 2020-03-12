#include <iostream>
#include "mpi.h"
#include <chrono>
#include <ctime>
#include <unistd.h>

using namespace std;
//Implementing the Ring in mpi using blocking communication. 

int main(int argc, char *argv[]){

int rank, size, sum;
int startval, endval;


auto start = chrono::high_resolution_clock::now();
MPI::Init(argc, argv);

rank = MPI::COMM_WORLD.Get_rank();
size = MPI::COMM_WORLD.Get_size();

sum = 0;
startval = 1000*rank/size+1;
endval = 1000*(rank+1)/size;

for(int i= startval; i<=endval; i++){

       sum = sum + i;
    }

//Implementing Ring
  if(rank !=0){
  MPI::COMM_WORLD.Recv(&sum, 1, MPI::INT, rank-1, 0);
     cout<<"Processor "<<rank<<" received "<<sum<< " from "<< " processor " <<rank-1<<endl;

     }else{

sum = sum;
}

MPI::COMM_WORLD.Send(&sum, 1, MPI::INT, (rank+1)%size, 0);

if(rank==0){
     MPI::COMM_WORLD.Recv(&sum, 1, MPI::INT, size-1, 0);
   cout<<"Processor "<<rank<<" received "<<sum<<" from "<<" processor "<<size-1<<endl;
   }


         MPI::Finalize();

auto end = chrono::high_resolution_clock::now();

chrono::duration<double>timem = end - start;


cout<<"Execution time for each processor: "<<timem.count()<< " seconds.";
cout<<endl;
     return 0;

       }
