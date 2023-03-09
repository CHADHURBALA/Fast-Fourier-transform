#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

double PI;
typedef float complex cplx;

void disp(cplx x[], int n) {

  for (int i = 0; i < n; i++)
    if (!cimag(x[i]))
      printf("%g \n", round(creal(x[i])));
    else if (cimag(x[i]) < 0)
      printf("%g %gi \n", round(creal(x[i])), round(cimag(x[i])));
    else
      printf("%g +%gi \n", round(creal(x[i])), round(cimag(x[i])));
}

cplx *fft(cplx out[], int n) {
  if (n <= 1) {
    return out;
  }
  int l = (int)(log2f(n / 2));
  cplx x_1[n / 2], x_2[n / 2];
  for (int i = 0; i < n; i += 2) {
    x_1[i / 2] = out[i];
    x_2[i / 2] = out[i + 1];
  }
  cplx *x_e = fft(x_1, n / 2);
  cplx *x_o = fft(x_2, n / 2);
  if (l != 0) {
    printf("\nButterfly stage: %d\n", l);
    disp(x_e, n / 2);
    disp(x_o, n / 2);
  }
  cplx *x = out;
  for (int a = 0; a < n / 2; a++) {
    x[a] = x_e[a] + cexp(-I * 2 * a * PI / n) * x_o[a];
    x[a + n / 2] = x_e[a] - cexp(-I * 2 * a * PI / n) * x_o[a];
  }
  return x;
}

int main() {
  clock_t s, total;

  PI = atan2(1, 1) * 4;

  int N = 0;
  float r, im;

  printf("Enter no of elemets: ");
  scanf("%d", &N);
  cplx x[N];
  printf("Enter the element in sequence as (real imginary): \n");
  for (int i = 0; i < N; i++) {
    r = 0;
    im = 0;
    scanf("%f %f", &r, &im);
    x[i] = r + im * I;
  }
  s = clock();

  cplx *o = fft(x, N);

  total = clock() - s;
  double time_taken = ((double)total) / CLOCKS_PER_SEC;

  int l = (int)(log2f(N));
  printf("\nButterfly stage: %d\n", l);
  disp(o, N);
  printf("\nTime taken to compute FFT : %f s\n", time_taken);
  return 0;
}