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
#ifndef O2SCL_ERR_HND_H
#define O2SCL_ERR_HND_H

/** \file err_hnd.h
    \brief Error handling classes, \ref o2scl::err_hnd_type and 
    \ref o2scl::err_hnd_gsl

    See also \ref exception.h .
*/

#include <iostream>
#include <string>

namespace o2scl {

  /** \brief The integer error definitions in src/base/err_hnd.h
      
      The errors associated with the integers between -2 and 32
      are based on GSL, the rest are specific to \o2 . 
  */
  enum {
    /// Success
    success=0,
    /// Failure
    gsl_failure=-1,
    /// iteration has not converged
    gsl_continue=-2,  
    /// input domain error, e.g sqrt(-1)
    exc_edom=1,   
    /// output range error, e.g. exp(1e100)
    exc_erange=2,   
    /// invalid pointer
    exc_efault=3,   
    /// invalid argument supplied by user
    exc_einval=4,   
    /// generic failure
    exc_efailed=5,   
    /// factorization failed
    exc_efactor=6,   
    /// sanity check failed - shouldn't happen 
    exc_esanity=7,   
    /// malloc failed
    exc_enomem=8,   
    /// problem with user-supplied function
    exc_ebadfunc=9,   
    /// iterative process is out of control
    exc_erunaway=10,  
    /// exceeded max number of iterations
    exc_emaxiter=11,  
    /// tried to divide by zero
    exc_ezerodiv=12,  
    /// user specified an invalid tolerance 
    exc_ebadtol=13,  
    /// failed to reach the specified tolerance 
    exc_etol=14,  
    /// underflow
    exc_eundrflw=15,  
    /// overflow
    exc_eovrflw=16,  
    /// loss of accuracy
    exc_eloss=17,  
    /// failed because of roundoff error 
    exc_eround=18,  
    /// matrix, vector lengths are not conformant 
    exc_ebadlen=19,  
    /// matrix not square
    exc_enotsqr=20,  
    /// apparent singularity detected
    exc_esing=21,  
    /// integral or series is divergent 
    exc_ediverge=22,  
    /// requested feature is not supported by the hardware 
    exc_eunsup=23,  
    /// requested feature not (yet) implemented 
    exc_eunimpl=24,  
    /// cache limit exceeded 
    exc_ecache=25,  
    /// \table limit exceeded 
    exc_etable=26,  
    /// iteration is not making progress toward solution 
    exc_enoprog=27,  
    /// \jacobian evaluations are not improving the solution 
    exc_enoprogj=28,  
    /// cannot reach the specified tolerance in f 
    exc_etolf=29,  
    /// cannot reach the specified tolerance in x 
    exc_etolx=30,  
    /// cannot reach the specified tolerance in \gradient 
    exc_etolg=31,  
    /// end of file 
    exc_eof=32,  
    /// Generic "not found" result
    exc_enotfound=33,
    /// Incorrect type for memory object
    exc_ememtype=34,
    /// File not found
    exc_efilenotfound=35,
    /// Invalid index for array or matrix
    exc_eindex=36,
    /// Outside constraint region
    exc_outsidecons=37
  };

  inline void set_err_fn(const char *desc, const char *file, int line,
			 int errnum) {
    std::cout << desc << std::endl;
    exit(-1);
    return;
  }

  /** \brief Set an error with message \c d and code \c n
   */
#define O2SCL_ERR(d,n) o2scl::set_err_fn(d,__FILE__,__LINE__,n);
  
  /** \brief Set a "convergence" error
   */
#define O2SCL_CONV(d,n,b) {if (b) o2scl::set_err_fn(d,__FILE__,__LINE__,n);}
  
  /** \brief Set an error, two-string version
   */
#define O2SCL_ERR2(d,d2,n) o2scl::set_err_fn((std::string(d)+d2).c_str(), \
					     __FILE__,__LINE__,n);
  
  /** \brief Set an error, three-string version
   */
#define O2SCL_ERR3(d,d2,d3,n) o2scl::set_err_fn(\
  (std::string(d)+d2+d3).c_str(),__FILE__,__LINE__,n);
  
  /** \brief Set a "convergence" error, two-string version
   */
#define O2SCL_CONV2(d,d2,n,b) {if (b)					\
      o2scl::set_err_fn((std::string(d)+d2).c_str(),			\
			__FILE__,__LINE__,n);}
  
  /** \brief Set a "convergence" error and return the error value
   */
#define O2SCL_CONV_RET(d,n,b)						\
  do { if (!b) { return n; } else {					\
      o2scl::set_err_fn(d,__FILE__,__LINE__,n); return n; } } while (0)
  
  /** \brief Set an error and return the error value, two-string version
   */
#define O2SCL_CONV2_RET(d,d2,n,b)					\
  do { if (!b) { return n; } else {					\
      o2scl::set_err_fn((std::string(d)+d2).c_str(),			\
			__FILE__,__LINE__,n); return n; } } while (0)
  
}

#endif
