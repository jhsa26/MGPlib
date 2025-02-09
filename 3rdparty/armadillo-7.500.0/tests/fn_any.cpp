// Copyright (C) 2015 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


#include <armadillo>
#include "catch.hpp"

using namespace arma;


TEST_CASE("fn_any_1")
  {
  vec a(5, fill::zeros);
  vec b(5, fill::zeros);  b(0) = 1.0;
  vec c(5, fill::ones );
  
  REQUIRE( any(a) == false);
  REQUIRE( any(b) == true );
  REQUIRE( any(c) == true );
  
  REQUIRE( any(a(span::all)) == false);
  REQUIRE( any(b(span::all)) == true );
  REQUIRE( any(c(span::all)) == true );
  
  REQUIRE( any(  c -  c) == false);
  REQUIRE( any(2*c -2*c) == false);
  
  REQUIRE( any(c < 0.5) == false);
  REQUIRE( any(c > 0.5) == true );
  }



TEST_CASE("fn_any_2")
  {
  mat A(5, 6, fill::zeros);
  mat B(5, 6, fill::zeros);  B(0,0) = 1.0;
  mat C(5, 6, fill::ones );
  
  REQUIRE( any(vectorise(A)) == false);
  REQUIRE( any(vectorise(B)) == true );
  REQUIRE( any(vectorise(C)) == true );
  
  REQUIRE( any(vectorise(A(span::all,span::all))) == false);
  REQUIRE( any(vectorise(B(span::all,span::all))) == true );
  REQUIRE( any(vectorise(C(span::all,span::all))) == true );


  REQUIRE( any(vectorise(  C -  C)) == false);
  REQUIRE( any(vectorise(2*C -2*C)) == false);
  
  REQUIRE( any(vectorise(C) < 0.5) == false);
  REQUIRE( any(vectorise(C) > 0.5) == true );
  }



TEST_CASE("fn_any_3")
  {
  mat A(5, 6, fill::zeros);
  mat B(5, 6, fill::zeros);  B(0,0) = 1.0;
  mat C(5, 6, fill::ones );
  mat D(5, 6, fill::ones );  D(0,0) = 0.0;
  
  REQUIRE( accu( any(A)   == urowvec({0, 0, 0, 0, 0, 0}) ) == 6 );
  REQUIRE( accu( any(A,0) == urowvec({0, 0, 0, 0, 0, 0}) ) == 6 );
  REQUIRE( accu( any(A,1) == uvec   ({0, 0, 0, 0, 0}   ) ) == 5 );

  REQUIRE( accu( any(B)   == urowvec({1, 0, 0, 0, 0, 0}) ) == 6 );
  REQUIRE( accu( any(B,0) == urowvec({1, 0, 0, 0, 0, 0}) ) == 6 );
  REQUIRE( accu( any(B,1) == uvec   ({1, 0, 0, 0, 0}   ) ) == 5 );
  
  REQUIRE( accu( any(C)   == urowvec({1, 1, 1, 1, 1, 1}) ) == 6 );
  REQUIRE( accu( any(C,0) == urowvec({1, 1, 1, 1, 1, 1}) ) == 6 );
  REQUIRE( accu( any(C,1) == uvec   ({1, 1, 1, 1, 1}   ) ) == 5 );
  
  REQUIRE( accu( any(D)   == urowvec({1, 1, 1, 1, 1, 1}) ) == 6 );
  REQUIRE( accu( any(D,0) == urowvec({1, 1, 1, 1, 1, 1}) ) == 6 );
  REQUIRE( accu( any(D,1) == uvec   ({1, 1, 1, 1, 1}   ) ) == 5 );
  }


