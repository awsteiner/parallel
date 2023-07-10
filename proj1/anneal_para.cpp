/*
  ───────────────────────────────────────────────────────────────────
  
  Copyright (C) 2006-2023, Andrew W. Steiner
  
  This file is part of O2scl.
  
  O2scl is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.
  
  O2scl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with O2scl. If not, see <http://www.gnu.org/licenses/>.

  ───────────────────────────────────────────────────────────────────
*/
  
#include <cmath>
#include <fstream>
#include <cstdlib>

#ifndef NO_PARA
#include <omp.h>
#include <mpi.h>
#endif

#include "multi_funct.h"
#include "anneal_para.h"

using namespace std;
using namespace o2scl;

typedef boost::numeric::ublas::vector<double> ubvector;

double funx(size_t nv, const ubvector &x) {
  double ret, a;
  a=x[0]-2.0;
  ret=-exp(-a*a);
  return ret;
}

int main(int argc, char *argv[]) {

  cout.setf(ios::scientific);

  int mpi_rank=0, mpi_size=1;
  
#ifndef NO_PARA
  MPI_Init(&argc,&argv);
  // Get MPI rank and size
  MPI_Comm_rank(MPI_COMM_WORLD,&mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&mpi_size);
#endif
  
  anneal_para<multi_funct,ubvector> ga;

#ifndef NO_PARA
  ga.n_threads=2;
  //omp_get_max_threads();
#endif
  
  double result;
  ubvector init(1);
  multi_funct fx=funx;
    
  init[0]=0.1;
  ga.verbose=1;
  ga.tol_abs=1.0e-6;
  ga.mmin(1,init,result,fx);
  
  if (mpi_rank==0) {
    cout << init[0] << " " << result << endl;
  }

  std::string fn;
#ifndef NO_PARA
  fn="anneal_para_";
  fn+=std::to_string(mpi_rank)+".txt";
#else
  fn="anneal_nopara.txt";
#endif
  
  ofstream fout(fn.c_str());
  fout.setf(ios::scientific);
  for(size_t i=0;i<ga.E_store.size();i++) {
    fout << ga.x_store[i] << " " << ga.E_store[i] << endl;
  }
  fout.close();
  
#ifndef NO_PARA
  MPI_Finalize();
#endif
  
  return 0;
}

