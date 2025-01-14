// Copyright (C) 2015-2016 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au



//! \addtogroup op_nonzeros
//! @{



template<typename T1>
inline
void
op_nonzeros::apply_noalias(Mat<typename T1::elem_type>& out, const Proxy<T1>& P)
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const uword N_max = P.get_n_elem();
  
  Mat<eT> tmp(N_max, 1);
  
  eT* tmp_mem = tmp.memptr();
  
  uword N_nz = 0;
  
  if(Proxy<T1>::use_at == false)
    {
    typename Proxy<T1>::ea_type Pea = P.get_ea();
    
    for(uword i=0; i<N_max; ++i)
      {
      const eT val = Pea[i];
      
      if(val != eT(0))  { tmp_mem[N_nz] = val; ++N_nz; }
      }
    }
  else
    {
    const uword n_rows = P.get_n_rows();
    const uword n_cols = P.get_n_cols();
    
    for(uword col=0; col < n_cols; ++col)
    for(uword row=0; row < n_rows; ++row)
      {
      const eT val = P.at(row,col);
      
      if(val != eT(0))  { tmp_mem[N_nz] = val; ++N_nz; }
      }
    }
  
  out.steal_mem_col(tmp, N_nz);
  }



template<typename T1>
inline
void
op_nonzeros::apply(Mat<typename T1::elem_type>& out, const Op<T1, op_nonzeros>& X)
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const Proxy<T1> P(X.m);
  
  if(P.get_n_elem() == 0)  { out.set_size(0,1); return; }
  
  if(P.is_alias(out))
    {
    Mat<eT> out2;
    
    op_nonzeros::apply_noalias(out2, P);
    
    out.steal_mem(out2);
    }
  else
    {
    op_nonzeros::apply_noalias(out, P);
    }
  }



template<typename T1>
inline
void
op_nonzeros::apply_noalias(Mat<typename T1::elem_type>& out, const SpBase<typename T1::elem_type,T1>& X)
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const SpProxy<T1> P(X.get_ref());
  
  const uword N = P.get_n_nonzero();
  
  out.set_size(N,1);
  
  if(N > 0)
    {
    if(is_SpMat<typename SpProxy<T1>::stored_type>::value)
      {
      const unwrap_spmat<typename SpProxy<T1>::stored_type> U(P.Q);
      
      arrayops::copy(out.memptr(), U.M.values, N);
      }
    else
      {
      eT* out_mem = out.memptr();
      
      typename SpProxy<T1>::const_iterator_type it = P.begin();
      
      for(uword i=0; i<N; ++i)  { out_mem[i] = (*it); ++it; }
      }
    }
  }
  
  
  
  
//! @}
