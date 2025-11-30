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
  new_matrix->data = (double complex *)calloc(rows * cols, sizeof(double complex)); //行列の面積はrow * cols, rows + colsじゃない．
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

void free_vector(ComplexVector *v) {
  if (v != NULL) {
    free(v->data);
  }
  free(v);
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
  if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
    printf("Value Error\n");
    exit(1);
  } 
  int k = row * m->cols + col;
  double complex seq = m->data[k];
  return seq;
}

void set_matrix_element(ComplexMatrix *m, int row, int col, double complex value) {
  if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
    printf("Value Error\n");
    exit(1);
  }
  int k = row * m->cols + col;
  m->data[k] = value;
}

void set_vector_element(ComplexVector *v, int index, double complex value) {
  if (index < 0 || index >= v->size) {
    printf("Value Error\n");
    exit(1);
  }
  v->data[index] = value;
}

// 行列ベクトル積(Matrix-Vector Multiplication)
ComplexVector *mat_vec_mult(const ComplexMatrix *A, const ComplexVector *x) {
  // y = Ax
  ComplexVector *y = create_vector(A->rows);
  
  if (A->cols != x->size) {
    printf("Value Error\n");
    exit(1);
  }

  for (int i = 0; i < (A->rows); i++) {
    for (int j = 0; j < (A->cols); j++) {
      y->data[i] += get_matrix_element(A, i, j) * x->data[j];
    }
  }
  return y;
}

// 線形演算関数の拡張
// ベクトルの足し算
ComplexVector *add_vectors(const ComplexVector *v1, const ComplexVector *v2) {
  if (v1->size != v2->size) {
    printf("Value Error\n");
    exit(1);
  }
  ComplexVector *new_vector = create_vector(v1->size);
  for (int index = 0; index < v1->size; index++) {
    new_vector->data[index] = v1->data[index] + v2->data[index];
  }
  return new_vector;
}

// ベクトルの全要素をスカラー倍
ComplexVector *scale_vector(double complex scalar, const ComplexVector *v) {
  ComplexVector *new_vector = create_vector(v->size);
  for (int index = 0; index < v->size; index++) {
    new_vector->data[index] = (scalar) * (v->data[index]);
  }
  return new_vector;
}

int main(void) {
  ComplexVector *x = create_vector(2);
  set_vector_element(x, 0, 0+1+I);
  set_vector_element(x, 1, 1+0*I);

  ComplexVector *y = create_vector(2);
  set_vector_element(y, 0, 0+1*I);
  set_vector_element(y, 1, 2+0*I);

  ComplexVector *ans1 = add_vectors(x, y);
  ComplexVector *ans2 = scale_vector(3, y);

  for (int i = 0; i < x->size; i++) {
    printf("ans1_%d: %.2f+%.2fi\n", i, creal(ans1->data[i]), cimag(ans1->data[i]));  }
  for (int j = 0; j < x->size; j++) {
    printf("ans2_%d: %.2f+%.2fi\n", j, creal(ans2->data[j]), cimag(ans2->data[j]));  }
  free_vector(x);
  free_vector(y);
  free_vector(ans1);
  free_vector(ans2);
  
  return 0;
}











