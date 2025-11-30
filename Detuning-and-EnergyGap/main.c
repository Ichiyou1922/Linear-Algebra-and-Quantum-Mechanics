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

// シュレーディンガー方程式の右辺(その瞬間の速度)を計算
ComplexVector *func(const ComplexMatrix *H, const ComplexVector *psi) {
  ComplexVector *tmp = mat_vec_mult(H, psi);
  ComplexVector *res = scale_vector(-I, tmp);
  free_vector(tmp);
  return res;
}

// RK4の実装
ComplexVector *rk4_step(const ComplexMatrix *H, const ComplexVector *psi, double dt) {
  ComplexVector *k1 = func(H, psi);
  
  // mallocで受け取らないとアドレスがわからなくなりfree出来なくなるので注意
  ComplexVector *tmp_k1 = scale_vector(dt * 0.5, k1); //次の状態にdt * 0.5
  ComplexVector *tmp_psi2 = add_vectors(psi, tmp_k1); // さらにpsiを足す
  ComplexVector *k2 = func(H, tmp_psi2);
  free_vector(tmp_k1);
  free_vector(tmp_psi2);

  ComplexVector *tmp_k2 = scale_vector(dt * 0.5, k2);
  ComplexVector *tmp_psi3 = add_vectors(psi, tmp_k2);
  ComplexVector *k3 = func(H, tmp_psi3);
  free_vector(tmp_k2);
  free_vector(tmp_psi3);

  ComplexVector *tmp_k3 = scale_vector(dt, k3);
  ComplexVector *tmp_psi4 = add_vectors(psi, tmp_k3);
  ComplexVector *k4 = func(H, tmp_psi4);
  free_vector(tmp_k3);
  free_vector(tmp_psi4);
  
  // 足し合わせ
  ComplexVector *k2_2 = scale_vector(2, k2);
  ComplexVector *k3_2 = scale_vector(2, k3);
  
  ComplexVector *k1_2 = add_vectors(k1, k2_2);
  ComplexVector *k3_4 = add_vectors(k3_2, k4);
  ComplexVector *k12_34 = add_vectors(k1_2, k3_4);

  ComplexVector *tmp = scale_vector((dt / 6),k12_34);
  
  ComplexVector *psi_new = add_vectors(psi, tmp);
  
  free_vector(k2_2);
  free_vector(k3_2);
  free_vector(k1_2);
  free_vector(k3_4);
  free_vector(k12_34);
  free_vector(tmp);
  
  free_vector(k1);
  free_vector(k2);
  free_vector(k3);
  free_vector(k4);

  return psi_new;
}

/*
double norm_square(const ComplexVector *v) {
  double norm_sq = 0.0;
  for (int i = 0; i < v->size; i++) {
    norm_sq += creal(v->data[i] * conj(v->data[i]));
  }
  return norm_sq;
}
*/

int main(void) {
  double t = 0.0;
  double dt = 0.01;
  int steps = 1000;
  double omega = 1.0;
  double delta = 2.0;
  printf("time, prob_0\n");

  ComplexVector *current_psi = create_vector(2);
  set_vector_element(current_psi, 0, 1);
  set_vector_element(current_psi, 1, 0);

  ComplexMatrix *H = create_matrix(2, 2);
  set_matrix_element(H, 0, 0, -0.5 * delta);
  set_matrix_element(H, 0, 1, 0.5 * omega);
  set_matrix_element(H, 1, 0, 0.5 * omega);
  set_matrix_element(H, 1, 1, +0.5 * delta);

  for (int i = 0; i< steps; i++) {
    printf("%f,%f\n", t, creal(current_psi->data[0] * conj(current_psi->data[0])));
    ComplexVector *next_psi = rk4_step(H, current_psi, dt);
    free_vector(current_psi);
    current_psi = next_psi;
    t += dt;
  }

  return 0;
}











