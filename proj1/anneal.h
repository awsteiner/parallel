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
#ifndef O2SCL_ANNEAL_H
#define O2SCL_ANNEAL_H

/** \file anneal.h
    \brief File defining \ref o2scl::anneal_base
*/

#include <iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "multi_funct.h"
#include "rng.h"

namespace o2scl {

  template<class func_t=multi_funct, class dfunc_t=func_t,
    class vec_t=boost::numeric::ublas::vector<double> > class mmin_base {

#ifndef DOXYGEN_INTERNAL

  protected:
    
    /// Stream for verbose output
    std::ostream *outs;
    
    /// Stream for verbose input
    std::istream *ins;
    
#endif
    
  public:
    
    mmin_base() {
      verbose=0;
      ntrial=100;
      tol_rel=1.0e-4;
      tol_abs=1.0e-4;
      last_ntrial=0;
      err_nonconv=true;
      outs=&std::cout;
      ins=&std::cin;
    }
    
    virtual ~mmin_base() {}
    
    /// Output control
    int verbose;
    
    /// Maximum number of iterations
    int ntrial;
    
    /// Function value tolerance
    double tol_rel;
    
    /// The independent variable tolerance
    double tol_abs;
    
    /// The number of iterations for in the most recent minimization
    int last_ntrial;
    
    /// If true, call the error handler if the routine does not "converge"
    bool err_nonconv;
    
    /** \brief Set streams for verbose I/O
        
        Note that this function stores pointers to the user-specified
        output streams, and these pointers are not copied in child copy
        constructors.
    */
    int set_verbose_stream(std::ostream &out, std::istream &in) {
      outs=&out;
      ins=&in;
      return 0;
    }
    
    /** \brief Calculate the minimum \c min of \c func w.r.t. the
        array \c x of size \c nvar.
    */
    virtual int mmin(size_t nvar, vec_t &x, double &fmin, 
                     func_t &func)=0;
    
    /** \brief Calculate the minimum \c min of \c func
        w.r.t. the array \c x of size \c nvar with gradient
        \c dfunc
    */
    virtual int mmin_de(size_t nvar, vec_t &x, double &fmin, 
                        func_t &func, dfunc_t &dfunc)
    {
      return mmin(nvar,x,fmin,func);
    }

  };
  
  /** \brief Simulated annealing base
      
      The seed of the generator is not fixed initially by calls to
      mmin(), so if successive calls should reproduce the same
      results, then the random seed should be set by the user before
      each call.
      
      For the algorithms here, it is important that all of the inputs
      <tt>x[i]</tt> to the function are scaled similarly relative to
      the temperature. For example, if the inputs <tt>x[i]</tt> are
      all of order 1, one might consider a temperature schedule which
      begins with \f$ T=1 \f$ .

      The number of iterations at each temperature is controlled by
      \ref o2scl::mmin_base::ntrial which defaults to 100.
  */
    template<class func_t=multi_funct,
    class vec_t=boost::numeric::ublas::vector<double>,
           class rng_t=o2scl::rng<> > class anneal_base :
    public mmin_base<func_t,func_t,vec_t> {
    
#ifdef O2SCL_NEVER_DEFINED
    }
  {
#endif
    
  public:
    
    anneal_base() {
      this->ntrial=100;
    }
      
    virtual ~anneal_base() {}
      
    /** \brief Calculate the minimum \c fmin of \c func w.r.t the 
        array \c x of size \c nvar.
    */
    virtual int mmin(size_t nvar, vec_t &x, double &fmin, 
                     func_t &func)=0;
    
    /** \brief Print out iteration information.

        Depending on the value of the variable verbose, this prints out
        the iteration information. If verbose=0, then no information is
        printed, while if verbose>1, then after each iteration, the
        present values of x and y are output to std::cout along with the
        iteration number. If verbose>=2 then each iteration waits for a
        character.  
    */
    virtual int print_iter(size_t nv, vec_t &x, double y, int iter,
                           double tptr, std::string comment) 
    {
      if (this->verbose<=0) return 0;
        
      size_t i;
      char ch;
      
      (*this->outs) << comment << " Iteration: " << iter << std::endl;
      std::cout << "x: ";
      for(i=0;i<nv;i++) std::cout << x[i] << " ";
      std::cout << std::endl;
      (*this->outs) << "y: " << y << " Tptr: " << tptr << std::endl;
      if (this->verbose>1) {
        (*this->outs) << "Press a key and type enter to continue. ";
        (*this->ins) >> ch;
      }
        
      return 0;
    }

    /// The default random number generator
    rng_t local_rng;

    /// Return string denoting type, \c "anneal_base".
    virtual const char *type() { return "anneal_base"; }

    /** \brief Copy constructor
     */
    anneal_base<func_t,vec_t,rng_t>
      (const anneal_base<func_t,vec_t,rng_t> &ab) : 
    mmin_base<func_t,func_t,vec_t>() {
      
      this->local_rng=ab.local_rng;
      
    }
    
    /** \brief Copy constructor from operator=
     */
    anneal_base<func_t,vec_t,rng_t>& operator=
      (const anneal_base<func_t,vec_t,rng_t> &ab) {

      if (this != &ab) {
        mmin_base<func_t,func_t,vec_t>::operator=(ab);
        this->local_rng=ab.local_rng;
      }
      return *this;
    }
    
  };

}

#endif

