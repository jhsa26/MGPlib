// Copyright (C) 2016 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


//! \addtogroup fn_index_min
//! @{


template<typename T1>
arma_warn_unused
arma_inline
const mtOp<uword, T1, op_index_min>
index_min
  (
  const T1& X,
  const uword dim = 0,
  const typename enable_if< is_arma_type<T1>::value       == true  >::result* junk1 = 0,
  const typename enable_if< resolves_to_vector<T1>::value == false >::result* junk2 = 0
  )
  {
  arma_extra_debug_sigprint();
  arma_ignore(junk1);
  arma_ignore(junk2);
  
  return mtOp<uword, T1, op_index_min>(X, dim, 0);
  }



template<typename T1>
arma_warn_unused
arma_inline
const mtOp<uword, T1, op_index_min>
index_min
  (
  const T1& X,
  const uword dim,
  const typename enable_if<resolves_to_vector<T1>::value == true>::result* junk = 0
  )
  {
  arma_extra_debug_sigprint();
  arma_ignore(junk);
  
  return mtOp<uword, T1, op_index_min>(X, dim, 0);
  }



template<typename T1>
arma_warn_unused
inline
uword
index_min
  (
  const T1& X,
  const arma_empty_class junk1 = arma_empty_class(),
  const typename enable_if<resolves_to_vector<T1>::value == true>::result* junk2 = 0
  )
  {
  arma_extra_debug_sigprint();
  arma_ignore(junk1);
  arma_ignore(junk2);
  
  return X.index_min();
  }



template<typename T1>
arma_warn_unused
inline
typename
enable_if2
  <
  (is_arma_sparse_type<T1>::value == true) && (resolves_to_sparse_vector<T1>::value == true),
  typename T1::elem_type
  >::result
index_min(const T1& x)
  {
  arma_extra_debug_sigprint();
  
  return x.index_min();
  }



template<typename T1>
arma_warn_unused
inline
typename
enable_if2
  <
  (is_arma_sparse_type<T1>::value == true) && (resolves_to_sparse_vector<T1>::value == false),
  Mat<uword>
  >::result
index_min(const T1& X, const uword dim = 0)
  {
  arma_extra_debug_sigprint();
  
  Mat<uword> out;
  
  op_index_min::apply(out, X, dim);
  
  return out;
  }



arma_warn_unused
inline
uword
index_min(const SizeMat& s)
  {
  return (s.n_rows <= s.n_cols) ? uword(0) : uword(1);
  }



arma_warn_unused
inline
uword
index_min(const SizeCube& s)
  {
  const uword tmp_val   = (s.n_rows <= s.n_cols) ? s.n_rows : s.n_cols;
  const uword tmp_index = (s.n_rows <= s.n_cols) ? uword(0) : uword(1);
  
  return (tmp_val <= s.n_slices) ? tmp_index : uword(2);
  }



//! @}
