#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define lp 1000

#define PI 3.142857

double c_od, c_do;

static double f3(double x) {
    return x * x + 2 * x;
}
static double f4(double x) {
    return 7 * pow(x, 3) - 5 * sqrt(x);
}


static double prostokaty(double( *f)(double))
{
       double krok, p, suma=0;
       krok = (c_do-c_od) / lp;
       for(p = c_od; p < c_do; p += krok)
               suma+=(*f)(p)*krok;
       return suma;
}

static double trapezy(double (*f)(double))
{
    int i;
    double krok, p, s;
    krok = (c_do - c_od) / lp;
  for(i = 1; i < lp; i++) {
       s += f(c_od + i * krok);
  }
  s = (s + (f(c_od) + f(c_do)) / 2) * krok;
  return s;
}
       
static double mc(double(*f)(double))
{
    int i;
    double krok, p, s;
    srand(time(NULL));
    s = 0;
    krok = c_do - c_od;
    for(i = 1; i <= lp; i++) {
        s += f(c_od + ((double)rand()/(double)(RAND_MAX+1) * krok));
    }
    s = krok * s / lp;
    return s;
}
