/*
    nbody-c
    Copyright (C) 2020 Victor De la Luz
                       vdelaluz@enesmorelia.unam.mx

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argn, char **args){
  int miproc;
  int numproc;
  int value,oldvalue,step;
  MPI_Status status;
  int dummy;
  
  MPI_Init (&argn, &args); /* Inicializar MPI */
  MPI_Comm_rank(MPI_COMM_WORLD,&miproc); /* Determinar el rango
 del proceso invocado*/
  MPI_Comm_size(MPI_COMM_WORLD,&numproc); /* Determinar el nume
ro de procesos */
  MPI_Barrier (MPI_COMM_WORLD);
  step=0;
  //oldvalue=value=(miproc+1)*10; 
  oldvalue=value=0;
  for(step=0;step<8;step++){
    if((step==0) && (miproc==numproc-1)){//trick to sweep ring
      dummy = 0;//(miproc+1)*10;
      MPI_Send(&dummy, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
    }
    if (miproc==0){
      if(step <numproc){//starting ring
	oldvalue = (step+1)*10;
      }

      MPI_Recv(&value, 1, MPI_INT, numproc-1, 99, MPI_COMM_WORLD, &status);
    printf("%i\t%i\t%i\n",step,miproc,oldvalue);
    MPI_Send(&oldvalue, 1, MPI_INT, 1, 99, MPI_COMM_WORLD); //pass to next proc
    MPI_Barrier (MPI_COMM_WORLD);
    oldvalue=value;
    }else{
      MPI_Recv(&value, 1, MPI_INT, miproc-1, 99, MPI_COMM_WORLD, &status);
      printf("%i\t%i\t%i\n",step,miproc,oldvalue);
      if(miproc==numproc-1){
	MPI_Send(&value, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
      }else{
	MPI_Send(&oldvalue, 1, MPI_INT, miproc+1, 99, MPI_COMM_WORLD); //pass to next proc
      }
      MPI_Barrier (MPI_COMM_WORLD);
      oldvalue=value;
    } 
  }
  MPI_Finalize();
  return 0;
}
