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

// 内積の計算
double complex inner_product(const ComplexVector *v1, const ComplexVector *v2) {
  if (v1->size != v2->size) {
    printf("vector size is not match\n");
    exit(1);
  }
  double complex in_product = 0;
  for (int i = 0; i < v1->size; i++) {
    in_product += conj(v1->data[i]) * v2->data[i];
  }
  return in_product;
}

int main(void) {
  ComplexVector *v1 = create_vector(3);
  ComplexVector *v2 = create_vector(3);
  set_element(v1, 0, 1 + I);
  set_element(v1, 1, 1);
  set_element(v1, 2, 0);
  set_element(v2, 0, 1);
  set_element(v2, 1, I);
  set_element(v2, 2, 0);
  double complex in_pro = inner_product(v1, v2);
  printf("inner_product: %.2f+%.2fi\n", creal(in_pro), cimag(in_pro));
  free_vector(v1);
  free_vector(v2);
  return 0;
}





