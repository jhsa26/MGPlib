// Copyright (C) 2008-2016 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


//! \addtogroup fn_diagvec
//! @{


//! extract a diagonal from a matrix
template<typename T1>
arma_warn_unused
arma_inline
const Op<T1, op_diagvec>
diagvec(const Base<typename T1::elem_type,T1>& X, const sword diag_id = 0)
  {
  arma_extra_debug_sigprint();
  
  return Op<T1, op_diagvec>(X.get_ref(), ((diag_id < 0) ? -diag_id : diag_id), ((diag_id < 0) ? 1 : 0) );
  }



//! @}
