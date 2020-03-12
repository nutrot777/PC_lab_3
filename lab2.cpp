#include <iostream>
#include "mpi.h"
#include <chrono>
#include <ctime>
#include <unistd.h>

using namespace std;
//Implementing the Ring in mpi using blocking communication. 
//10682923

int main(int argc, char *argv[]){

int rank, size, sum ,accum;
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
if(rank!=0){


     MPI::COMM_WORLD.Send(&sum, 1,MPI::INT, 0,1);


}else{
   for(int j=1;j<size;j=j+1){
        MPI::COMM_WORLD.Recv(&accum, 1, MPI::INT, j, 1);
sum = sum + accum;

    }

   }

if(rank==0){
  cout<<"The sum from 1 to 1000 is: "<< sum<<endl;
 }


         MPI::Finalize();

auto end = chrono::high_resolution_clock::now();

chrono::duration<double>timem = end - start;


cout<<"Execution time for each processor: "<<timem.count()<< " seconds.";
cout<<endl;
     return 0;

       }
