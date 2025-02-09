// Copyright (C) 2008-2015 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


//! \addtogroup fn_randn
//! @{


arma_warn_unused
inline
double
randn()
  {
  return double(arma_rng::randn<double>());
  }


template<typename eT>
arma_warn_unused
inline
typename arma_scalar_only<eT>::result
randn()
  {
  return eT(arma_rng::randn<eT>());
  }



//! Generate a vector with all elements set to random values with a gaussian distribution (zero mean, unit variance)
arma_warn_unused
arma_inline
const Gen<vec, gen_randn>
randn(const uword n_elem)
  {
  arma_extra_debug_sigprint();
  
  return Gen<vec, gen_randn>(n_elem, 1);
  }



template<typename obj_type>
arma_warn_unused
arma_inline
const Gen<obj_type, gen_randn>
randn(const uword n_elem, const arma_empty_class junk1 = arma_empty_class(), const typename arma_Mat_Col_Row_only<obj_type>::result* junk2 = 0)
  {
  arma_extra_debug_sigprint();
  arma_ignore(junk1);
  arma_ignore(junk2);
  
  if(is_Row<obj_type>::value == true)
    {
    return Gen<obj_type, gen_randn>(1, n_elem);
    }
  else
    {
    return Gen<obj_type, gen_randn>(n_elem, 1);
    }
  }



//! Generate a dense matrix with all elements set to random values with a gaussian distribution (zero mean, unit variance)
arma_warn_unused
arma_inline
const Gen<mat, gen_randn>
randn(const uword n_rows, const uword n_cols)
  {
  arma_extra_debug_sigprint();
  
  return Gen<mat, gen_randn>(n_rows, n_cols);
  }



arma_warn_unused
arma_inline
const Gen<mat, gen_randn>
randn(const SizeMat& s)
  {
  arma_extra_debug_sigprint();
  
  return Gen<mat, gen_randn>(s.n_rows, s.n_cols);
  }



template<typename obj_type>
arma_warn_unused
arma_inline
const Gen<obj_type, gen_randn>
randn(const uword n_rows, const uword n_cols, const typename arma_Mat_Col_Row_only<obj_type>::result* junk = 0)
  {
  arma_extra_debug_sigprint();
  arma_ignore(junk);
  
  if(is_Col<obj_type>::value == true)
    {
    arma_debug_check( (n_cols != 1), "randn(): incompatible size" );
    }
  else
  if(is_Row<obj_type>::value == true)
    {
    arma_debug_check( (n_rows != 1), "randn(): incompatible size" );
    }
  
  return Gen<obj_type, gen_randn>(n_rows, n_cols);
  }



template<typename obj_type>
arma_warn_unused
arma_inline
const Gen<obj_type, gen_randn>
randn(const SizeMat& s, const typename arma_Mat_Col_Row_only<obj_type>::result* junk = 0)
  {
  arma_extra_debug_sigprint();
  arma_ignore(junk);
  
  return randn<obj_type>(s.n_rows, s.n_cols);
  }



arma_warn_unused
arma_inline
const GenCube<cube::elem_type, gen_randn>
randn(const uword n_rows, const uword n_cols, const uword n_slices)
  {
  arma_extra_debug_sigprint();
  
  return GenCube<cube::elem_type, gen_randn>(n_rows, n_cols, n_slices);
  }



arma_warn_unused
arma_inline
const GenCube<cube::elem_type, gen_randn>
randn(const SizeCube& s)
  {
  arma_extra_debug_sigprint();
  
  return GenCube<cube::elem_type, gen_randn>(s.n_rows, s.n_cols, s.n_slices);
  }



template<typename cube_type>
arma_warn_unused
arma_inline
const GenCube<typename cube_type::elem_type, gen_randn>
randn(const uword n_rows, const uword n_cols, const uword n_slices, const typename arma_Cube_only<cube_type>::result* junk = 0)
  {
  arma_extra_debug_sigprint();  
  arma_ignore(junk);
  
  return GenCube<typename cube_type::elem_type, gen_randn>(n_rows, n_cols, n_slices);
  }



template<typename cube_type>
arma_warn_unused
arma_inline
const GenCube<typename cube_type::elem_type, gen_randn>
randn(const SizeCube& s, const typename arma_Cube_only<cube_type>::result* junk = 0)
  {
  arma_extra_debug_sigprint();  
  arma_ignore(junk);
  
  return GenCube<typename cube_type::elem_type, gen_randn>(s.n_rows, s.n_cols, s.n_slices);
  }



//! @}
