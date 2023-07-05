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
#ifndef O2SCL_MULTI_FUNCT_H
#define O2SCL_MULTI_FUNCT_H

/** \file multi_funct.h
    \brief Function object classes for a multi-dimensional function
*/

#include <string>
#include <functional>
#include <vector>

#include <boost/numeric/ublas/vector.hpp>

#include "err_hnd.h"

namespace o2scl {

  /// Multi-dimensional function typedef in src/base/multi_funct.h
  typedef std::function<
    double(size_t,const boost::numeric::ublas::vector<double> &)>
  multi_funct;
  
}

#endif
