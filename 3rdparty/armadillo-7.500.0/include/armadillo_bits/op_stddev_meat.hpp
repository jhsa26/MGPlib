// Copyright (C) 2009-2015 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


//! \addtogroup op_stddev
//! @{


//! \brief
//! For each row or for each column, find the standard deviation.
//! The result is stored in a dense matrix that has either one column or one row.
//! The dimension for which the standard deviations are found is set via the stddev() function.
template<typename T1>
inline
void
op_stddev::apply(Mat<typename T1::pod_type>& out, const mtOp<typename T1::pod_type, T1, op_stddev>& in)
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::elem_type  in_eT;
  typedef typename T1::pod_type  out_eT;
  
  const unwrap_check_mixed<T1> tmp(in.m, out);
  const Mat<in_eT>&        X = tmp.M;
  
  const uword norm_type = in.aux_uword_a;
  const uword dim       = in.aux_uword_b;
  
  arma_debug_check( (norm_type > 1), "stddev(): parameter 'norm_type' must be 0 or 1" );
  arma_debug_check( (dim > 1),       "stddev(): parameter 'dim' must be 0 or 1"       );
  
  const uword X_n_rows = X.n_rows;
  const uword X_n_cols = X.n_cols;
  
  if(dim == 0)
    {
    arma_extra_debug_print("op_stddev::apply(): dim = 0");
    
    out.set_size((X_n_rows > 0) ? 1 : 0, X_n_cols);
    
    if(X_n_rows > 0)
      {
      out_eT* out_mem = out.memptr();
      
      for(uword col=0; col<X_n_cols; ++col)
        {
        out_mem[col] = std::sqrt( op_var::direct_var( X.colptr(col), X_n_rows, norm_type ) );
        }
      }
    }
  else
  if(dim == 1)
    {
    arma_extra_debug_print("op_stddev::apply(): dim = 1");
    
    out.set_size(X_n_rows, (X_n_cols > 0) ? 1 : 0);
    
    if(X_n_cols > 0)
      {
      podarray<in_eT> dat(X_n_cols);
      
      in_eT*  dat_mem = dat.memptr();
      out_eT* out_mem = out.memptr();
      
      for(uword row=0; row<X_n_rows; ++row)
        {
        dat.copy_row(X, row);
        
        out_mem[row] = std::sqrt( op_var::direct_var( dat_mem, X_n_cols, norm_type) );
        }
      }
    }
  }



//! @}

