#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

typedef struct {
  int rows;
  int cols;
  double complex *data;
} ComplexMatrix;

typedef struct {
  int size;
  double complex *data;
} ComplexVector;

ComplexMatrix *create_matrix(int rows, int cols) {
  ComplexMatrix *new_matrix = (ComplexMatrix *)malloc(sizeof(ComplexMatrix));
  if (new_matrix == NULL) {
    printf("Failed to allocate structure memory\n");
    exit(1);
  }
  new_matrix->rows = rows;
  new_matrix->cols = cols;
  new_matrix->data = (double complex *)calloc(rows + cols, sizeof(double complex));
  if (new_matrix->data == NULL) {
    printf("Failed to allocate data memory\n");
    free(new_matrix);
    exit(1);
  }
  return new_matrix;
}

void free_matrix(ComplexMatrix *m) {
  if (m != NULL) {
    free(m->data);
  }
  free(m);
}

ComplexVector *create_vector(int size) {
  ComplexVector *new_vector = (ComplexVector *)malloc(sizeof(ComplexVector));
  if (new_vector == NULL) {
    printf("Failed to allocate structure memory\n");
    exit(1);
  }
  new_vector->size = size;
  new_vector->data = (double complex *)calloc(size, sizeof(double complex));
  if (new_vector->data == NULL) {
    printf("Failed to allocate data memory\n");
    exit(1);
  }
  return new_vector;
}

double complex get_matrix_element(const ComplexMatrix *m, int row, int col) {
  if (row < 0 || row > m->rows || col < 0 || col > m->cols) {
    printf("Value Error");
    exit(1);
  } 
  int k = row * m->cols + col;
  double complex ret = m->data[k];
  return ret;
}

void set_matrix_element(ComplexMatrix *m, int row, int col, double complex value) {
  if (row < 0 || row > m->rows || col < 0 || col > m->cols) {
    printf("Value Error");
    exit(1);
  }
  int k = row * m->cols + col;
  m->data[k] = value;
}

// 行列ベクトル積(Matrix-Vector Multiplication)
ComplexVector *mat_vec_mult(const ComplexMatrix *A, const ComplexVector *x) {
  // y = Ax
  ComplexVector *y = 0;
  y->size = A->rows;
  if (A->cols != x->size) {
    printf("Value Error\n");
    exit(1);
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; i++) {
      y->data[i] = get_matrix_element(A, i, j) * x->data[j];
    }
  }
  return y;
}

int main(void) {
  ComplexMatrix *sigma = create_matrix(2, 2);
  set_matrix_element(sigma, 0, 0, 0);
  set_matrix_element(sigma, 0, 1, 1);
  set_matrix_element(sigma, 1, 0, 1);
  set_matrix_element(sigma, 1, 1, 0);

  ComplexVector *y = 0;
  ComplexVector *ans = mat_vec_mult(sigma, y);
  printf("%f+%fi, %f+%fi", creal(ans->data[0]), cimag(ans->data[0]), creal(ans->data[1]), cimag(ans->data[1]));
  free(y);
  free_matrix(sigma);
  return 0;

}











