# matrix_tutorial
Simple implementation of matrices in C for educational purposes about C programming under Linux.


### Underlying structure

Matrices are represented by C structures, implemented as follows:

    typedef struct matrix {
        unsigned n1, n2;
        bool ok;
        scalar *data;
    } matrix;

The `ok` boolean attribute indicates whether the matrix is valid. `n1` and `n2` represent the matrix' size and `data` holds the matrix' scalars (implemented as doubles).


### Functions

Here are some functions implemented with their prototypes:

- Matrix initialization (`matrix matrix_create(unsigned n1, unsigned n2, scalar v)` and `matrix matrix_identity(unsigned n);`)
- Accessing matrix values (`scalar *matrix_get(matrix m, unsigned i, unsigned j)`)
- Matrix addition (`matrix matrix_add(matrix m, matrix n)`)
- Matrix multiplication (`matrix matrix_product(matrix m, matrix n)`)