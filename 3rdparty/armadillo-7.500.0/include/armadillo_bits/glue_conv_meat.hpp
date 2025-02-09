// Copyright (C) 2010-2016 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


//! \addtogroup glue_conv
//! @{



template<typename eT>
inline
void
glue_conv::apply(Mat<eT>& out, const Mat<eT>& A, const Mat<eT>& B, const bool A_is_col)
  {
  arma_extra_debug_sigprint();
  
  const Mat<eT>& h = (A.n_elem <= B.n_elem) ? A : B;
  const Mat<eT>& x = (A.n_elem <= B.n_elem) ? B : A;
  
  const uword   h_n_elem    = h.n_elem;
  const uword   h_n_elem_m1 = h_n_elem - 1;
  const uword   x_n_elem    = x.n_elem;
  const uword out_n_elem    = ((h_n_elem + x_n_elem) > 0) ? (h_n_elem + x_n_elem - 1) : uword(0);
  
  (A_is_col) ? out.set_size(out_n_elem, 1) : out.set_size(1, out_n_elem);
  
  if( (h_n_elem == 0) || (x_n_elem == 0) )  { out.zeros(); return; }
  
  
  Col<eT> hh(h_n_elem);  // flipped version of h
  
  const eT*   h_mem =  h.memptr();
        eT*  hh_mem = hh.memptr();
  
  for(uword i=0; i < h_n_elem; ++i)
    {
    hh_mem[h_n_elem_m1-i] = h_mem[i];
    }
  
  
  Col<eT> xx( (x_n_elem + 2*h_n_elem_m1), fill::zeros );  // zero padded version of x
  
  const eT*  x_mem =  x.memptr();
        eT* xx_mem = xx.memptr();
  
  arrayops::copy( &(xx_mem[h_n_elem_m1]), x_mem, x_n_elem );
  
  
  eT* out_mem = out.memptr();
        
  for(uword i=0; i < out_n_elem; ++i)
    {
    // out_mem[i] = dot( hh, xx.subvec(i, (i + h_n_elem_m1)) );
    
    out_mem[i] = op_dot::direct_dot( h_n_elem, hh_mem, &(xx_mem[i]) );
    }
  }



template<typename T1, typename T2>
inline
void
glue_conv::apply(Mat<typename T1::elem_type>& out, const Glue<T1,T2,glue_conv>& expr)
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const quasi_unwrap<T1> UA(expr.A);
  const quasi_unwrap<T2> UB(expr.B);
  
  const Mat<eT>& A = UA.M;
  const Mat<eT>& B = UB.M;
  
  arma_debug_check
    (
    ( ((A.is_vec() == false) && (A.is_empty() == false)) || ((B.is_vec() == false) && (B.is_empty() == false)) ),
    "conv(): given object is not a vector"
    );
  
  const bool A_is_col = ((T1::is_col) || (A.n_cols == 1));
  
  const uword mode = expr.aux_uword;
  
  if(mode == 0)  // full convolution
    {
    glue_conv::apply(out, A, B, A_is_col);
    }
  else
  if(mode == 1)  // same size as A
    {
    Mat<eT> tmp;
    
    glue_conv::apply(tmp, A, B, A_is_col);
    
    if( (tmp.is_empty() == false) && (A.is_empty() == false) && (B.is_empty() == false) )
      {
      const uword start = uword( std::floor( double(B.n_elem) / double(2) ) );
      
      out = (A_is_col) ? tmp(start, 0, arma::size(A)) : tmp(0, start, arma::size(A));
      }
    else
      {
      out.zeros( arma::size(A) );
      }
    }
  }



///



template<typename eT>
inline
void
glue_conv2::apply(Mat<eT>& out, const Mat<eT>& A, const Mat<eT>& B)
  {
  arma_extra_debug_sigprint();
  
  const Mat<eT>& G = (A.n_elem <= B.n_elem) ? A : B;   // unflipped filter coefficients
  const Mat<eT>& W = (A.n_elem <= B.n_elem) ? B : A;   // original 2D image
  
  const uword out_n_rows = ((W.n_rows + G.n_rows) > 0) ? (W.n_rows + G.n_rows - 1) : uword(0);
  const uword out_n_cols = ((W.n_cols + G.n_cols) > 0) ? (W.n_cols + G.n_cols - 1) : uword(0);
  
  out.set_size( out_n_rows, out_n_cols );
  
  if(G.is_empty() || W.is_empty())  { out.zeros(); return; }
  
  Mat<eT> H(G.n_rows, G.n_cols);  // flipped filter coefficients
  
  const uword H_n_rows = H.n_rows;
  const uword H_n_cols = H.n_cols;
  
  const uword H_n_rows_m1 = H_n_rows - 1;
  const uword H_n_cols_m1 = H_n_cols - 1;
  
  for(uword col=0; col < H_n_cols; ++col)
    {
          eT* H_colptr = H.colptr(H_n_cols_m1 - col);
    const eT* G_colptr = G.colptr(col);
    
    for(uword row=0; row < H_n_rows; ++row)
      {
      H_colptr[H_n_rows_m1 - row] = G_colptr[row];
      }
    }
  
  Mat<eT> X( (W.n_rows + 2*H_n_rows_m1), (W.n_cols + 2*H_n_cols_m1), fill::zeros );
  
  X( H_n_rows_m1, H_n_cols_m1, arma::size(W) ) = W;  // zero padded version of 2D image
  
  for(uword col=0; col < out_n_cols; ++col)
    {
    eT* out_colptr = out.colptr(col);
    
    for(uword row=0; row < out_n_rows; ++row)
      {
      // out.at(row, col) = accu( H % X(row, col, size(H)) );
      
      eT acc = eT(0);
      
      for(uword H_col = 0; H_col < H_n_cols; ++H_col)
        {
        const eT* X_colptr = X.colptr(col + H_col);
        
        acc += op_dot::direct_dot( H_n_rows, H.colptr(H_col), &(X_colptr[row]) );
        }
      
      out_colptr[row] = acc;
      }
    }
  }



template<typename T1, typename T2>
inline
void
glue_conv2::apply(Mat<typename T1::elem_type>& out, const Glue<T1,T2,glue_conv2>& expr)
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::elem_type eT;
  
  const quasi_unwrap<T1> UA(expr.A);
  const quasi_unwrap<T2> UB(expr.B);
  
  const Mat<eT>& A = UA.M;
  const Mat<eT>& B = UB.M;
  
  const uword mode = expr.aux_uword;
  
  if(mode == 0)  // full convolution
    {
    glue_conv2::apply(out, A, B);
    }
  else
  if(mode == 1)  // same size as A
    {
    Mat<eT> tmp;
    
    glue_conv2::apply(tmp, A, B);
    
    if( (tmp.is_empty() == false) && (A.is_empty() == false) && (B.is_empty() == false) )
      {
      const uword start_row = uword( std::floor( double(B.n_rows) / double(2) ) );
      const uword start_col = uword( std::floor( double(B.n_cols) / double(2) ) );
      
      out = tmp(start_row, start_col, arma::size(A));
      }
    else
      {
      out.zeros( arma::size(A) );
      }
    }
  }



//! @}
