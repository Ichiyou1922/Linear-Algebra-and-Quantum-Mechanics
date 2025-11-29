#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

typedef struct {
  int size;
  double complex* data;
} ComplexVector;

ComplexVector *create_vector(int size) {
  ComplexVector *v = (ComplexVector*)malloc(sizeof(ComplexVector));
  if (v == NULL) {printf("Failed to allocate structure memory\n"); exit(1);}
  v->size = size;
  v->data = (double complex *)calloc(size, sizeof(double complex));
  if (v->data == NULL) {
    printf("Failed to allocate data memory\n");
    free(v);
    exit(1);
  }
  return v;
}

void free_vector(ComplexVector *v) {
  if (v != NULL) {
    free(v->data); // 中身->外側で捨てる．
  }
  free(v);
}

void set_element(ComplexVector *v, int index, double complex value) {
  if (index < 0 || index >= v->size) {
    printf("Index Error\n");
    exit(1);
  }
  else {
    v->data[index] = value;
  }
}

double complex get_element(const ComplexVector *v, int index) {
  if (index < 0 || index >= v->size) {
    printf("Index Error\n");
    exit(1);
  }
  else {
    return v->data[index];
  }
}

double norm_square(const ComplexVector *v) {
  double norm_sq = 0.0;
  for (int i = 0; i < v->size; i++) {
    norm_sq += creal((v->data[i] * conj(v->data[i]))); // creal()で実部を取り出す．明示的なもの．
  }
  return norm_sq;
}

int main(void) {
  ComplexVector *v = create_vector(5);
  set_element(v, 0, I);
  set_element(v, 1, 2*I);
  set_element(v, 2, 3*I);
  set_element(v, 3, 4*I);
  set_element(v, 4, 5*I);
  
  for (int i = 0; i < 5 ; i++) {
    double complex idx_data = get_element(v, i);
    printf("z = %.2f + %.2fi\n", creal(idx_data), cimag(idx_data));
  }
  printf("norm: %f\n", norm_square(v));
  free_vector(v);
  return 0;
}





