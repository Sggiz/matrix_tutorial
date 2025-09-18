#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "matrix.h"

#define PRINT_PRECISION "6"
#define PRINT_DECIMAL_PRECISION "2"

matrix matrix_create(unsigned n1, unsigned n2, scalar v)
{
  matrix m={n1,n2,true,NULL};
  if(n1==0 || n2==0)
    return m;
  else if(SIZE_MAX / n1 <= n2)
    m.ok = false;
  else if (!(m.data=calloc(((size_t) n1)*n2, sizeof(scalar))))
    m.ok = false;
  else {
    for(unsigned i=0; i<n1; ++i)
      for(unsigned j=0; j<n2; ++j)
        *matrix_get(m,i,j) = v;
  }
 
  return m;
}

matrix matrix_identity(unsigned n)
{
  matrix m = matrix_create(n, n, 0.);
  if(!m.ok)
    return m;

  for(unsigned i=0; i<n; ++i)
    *matrix_get(m, i, i) = 1.;
  return m;
}

void matrix_destroy(matrix m)
{
  if(m.ok) {
    m.ok = false;
    free(m.data);
  }
}

scalar *matrix_get(matrix m, unsigned i, unsigned j)
{
  if(!m.ok || i>m.n1 || i>m.n2)
    return NULL;

  return &m.data[i*m.n2+j];
}

matrix matrix_add(matrix m, matrix n)
{
  matrix res={0,0,false,NULL};

  if(m.n1!=n.n1 || m.n2!=n.n2 || !m.ok || !n.ok)
    return res;

  res=matrix_create(m.n1, m.n2, 0.);
  for(unsigned i=0; i<m.n1; ++i)
    for(unsigned j=0; j<m.n2; ++j)
      *matrix_get(res, i, j) = *matrix_get(m, i, j) + *matrix_get(n, i, j);

  return res;
}

void matrix_print(FILE *f, matrix m)
{
  if(!m.ok)
    fprintf(f, "Invalid matrix\n");
  else {
    for(unsigned i=0; i<m.n1; ++i) {
      for(unsigned j=0; j<m.n2; ++j)
        fprintf(
            f, 
            "%"PRINT_PRECISION"."PRINT_DECIMAL_PRECISION"f ",
            *matrix_get(m, i, j));
      fprintf(f, "\n");
    }
  }
}

matrix matrix_product(matrix m1, matrix m2){
  matrix m = matrix_create(m1.n1,m2.n2,0.);
  if(m1.n2 <> m2.n1){
    m.ok = false;
    return m;
  }
  for(int i = 0; i<m1.n1; i++){
    for(int j = 0; j<m2.n2; j++){
      for(int k = 0; k<m1.n2; k++){
        *matrix_get(m,i,j) += *matrix_get(m1,i,k)*(*matrix_get(m2,k,j));
      }
    }
  }
  return m;
}

matrix matrix_exponant(matrix m, int b){
  matrix res;
  if(m.n1 <> m.n2){
    res.ok = false;
  } else if(b == 0){
    res = matrix_identity(m.n1);
  } else if(b%2 == 0){
    matrix n_m = matrix_product(m,m);
    res = matrix_exponant(n_m,b/2);
    matrix_destroy(n_m);
    return res;
  } else {
    matrix n_m = matrix_product(m,m);
    matrix n_n_m = matrix_product(n_m,m);
    res = matrix_exponant(n_n_m,(b-1)/2);
    matrix_destroy(n_m);
    matrix_destroy(n_n_m);
  }
  return res;
}