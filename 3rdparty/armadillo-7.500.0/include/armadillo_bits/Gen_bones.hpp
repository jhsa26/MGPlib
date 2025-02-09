// Copyright (C) 2011-2016 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


//! \addtogroup Gen
//! @{


//! support class for generator functions (eg. zeros, randu, randn, ...)
template<typename T1, typename gen_type>
class Gen
  : public Base<typename T1::elem_type, Gen<T1, gen_type> >
  , public GenSpecialiser<typename T1::elem_type, is_same_type<gen_type, gen_zeros>::yes, is_same_type<gen_type, gen_ones>::yes, is_same_type<gen_type, gen_randu>::yes, is_same_type<gen_type, gen_randn>::yes>
  {
  public:
  
  typedef typename T1::elem_type                   elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  
  static const bool use_at    = (is_same_type<gen_type, gen_eye>::value) ? true : false;
  static const bool is_simple = (is_same_type<gen_type, gen_ones>::value) || (is_same_type<gen_type, gen_zeros>::value); 
  
  static const bool is_row = T1::is_row;
  static const bool is_col = T1::is_col;
  
  arma_aligned const uword n_rows;
  arma_aligned const uword n_cols;
  
  arma_inline  Gen(const uword in_n_rows, const uword in_n_cols);
  arma_inline ~Gen();
  
  arma_inline elem_type operator[] (const uword ii)                   const;
  arma_inline elem_type at         (const uword row, const uword col) const;
  arma_inline elem_type at_alt     (const uword ii)                   const;
  
  inline void apply              (Mat<elem_type>& out) const;
  inline void apply_inplace_plus (Mat<elem_type>& out) const;
  inline void apply_inplace_minus(Mat<elem_type>& out) const;
  inline void apply_inplace_schur(Mat<elem_type>& out) const;
  inline void apply_inplace_div  (Mat<elem_type>& out) const;
  
  inline void apply(subview<elem_type>& out) const;
  };



//! @}
