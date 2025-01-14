// Copyright (C) 2016 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


//! \addtogroup op_index_max
//! @{



template<typename T1>
inline
void
op_index_max::apply(Mat<uword>& out, const mtOp<uword,T1,op_index_max>& in)
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const uword dim = in.aux_uword_a;
  arma_debug_check( (dim > 1), "index_max(): parameter 'dim' must be 0 or 1");
  
  const quasi_unwrap<T1> U(in.m);
  const Mat<eT>& X = U.M;
  
  if(U.is_alias(out) == false)
    {
    op_index_max::apply_noalias(out, X, dim);
    }
  else
    {
    Mat<uword> tmp;
    
    op_index_max::apply_noalias(tmp, X, dim);
    
    out.steal_mem(tmp);
    }
  }



template<typename eT>
inline
void
op_index_max::apply_noalias(Mat<uword>& out, const Mat<eT>& X, const uword dim)
  {
  arma_extra_debug_sigprint();
  
  const uword X_n_rows = X.n_rows;
  const uword X_n_cols = X.n_cols;
  
  if(dim == 0)
    {
    arma_extra_debug_print("op_index_max::apply(): dim = 0");
    
    out.set_size((X_n_rows > 0) ? 1 : 0, X_n_cols);
    
    if(X_n_rows == 0)  { return; }
    
    uword* out_mem = out.memptr();
    
    for(uword col=0; col < X_n_cols; ++col)
      {
      op_max::direct_max( X.colptr(col), X_n_rows, out_mem[col] );
      }
    }
  else
  if(dim == 1)
    {
    arma_extra_debug_print("op_index_max::apply(): dim = 1");
    
    out.set_size(X_n_rows, (X_n_cols > 0) ? 1 : 0);
    
    if(X_n_cols == 0)  { return; }
    
    uword* out_mem = out.memptr();
    
    for(uword row=0; row<X_n_rows; ++row)
      {
      out_mem[row] = X.row(row).index_max();
      }
    }
  }



template<typename T1>
inline
void
op_index_max::apply(Mat<uword>& out, const SpBase<typename T1::elem_type,T1>& expr, const uword dim)
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  arma_debug_check( (dim > 1), "index_max(): parameter 'dim' must be 0 or 1" );
  
  const unwrap_spmat<T1> U(expr.get_ref());
  const SpMat<eT>& X   = U.M;
  
  const uword X_n_rows = X.n_rows;
  const uword X_n_cols = X.n_cols;
  
  if(dim == 0)
    {
    arma_extra_debug_print("op_index_max::apply(): dim = 0");
    
    out.set_size((X_n_rows > 0) ? 1 : 0, X_n_cols);
    
    if(X_n_rows == 0)  { return; }
    
    uword* out_mem = out.memptr();
    
    for(uword col=0; col < X_n_cols; ++col)
      {
      out_mem[col] = X.col(col).index_max();
      }
    }
  else
  if(dim == 1)
    {
    arma_extra_debug_print("op_index_max::apply(): dim = 1");
    
    out.set_size(X_n_rows, (X_n_cols > 0) ? 1 : 0);
    
    if(X_n_cols == 0)  { return; }
    
    uword* out_mem = out.memptr();
    
    for(uword row=0; row<X_n_rows; ++row)
      {
      out_mem[row] = X.row(row).index_max();
      }
    }
  }



//! @}
