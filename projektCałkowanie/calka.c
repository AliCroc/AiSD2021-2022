#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include "calki.c"

double f1(double x)
{
 return 6.23*x*x*x-3.5*x*x-28;          
}     
double f2(double x)
{
double y;
y=sin(2*x)*sin(3*x)+cos(5*x)+12;
return y;       
}

int main(int argc, char *argv[])
{  
    printf("od=");
    scanf("%lf",&c_od);
    printf("do=");
    scanf("%lf",&c_do); 
    printf ("\n\nFunkcja 1 \n");
    printf( "wynik prostokaty - %lf\n" ,prostokaty(f1));
    printf( "wynik trapezy    - %lf\n" ,trapezy(f1));
    printf( "wynik MC   - %lf\n", mc(f1));
    printf("\n\nFunkcja 2 \n");
    printf( "wynik prostokaty - %lf\n" ,prostokaty(f2));
    printf( "wynik trapezy    - %lf\n" ,trapezy(f2));
    printf("wynik MC   - %lf\n", mc(f2));
    printf ("\n\nFunkcja 3 \n");
	printf( "wynik prostokaty - %lf\n" ,prostokaty(f3));
    printf( "wynik trapezy    - %lf\n" ,trapezy(f3));
    printf( "wynik MC   - %lf\n", mc(f3));
    printf("\n\nFunkcja 4 \n");
	printf( "wynik prostokaty - %lf\n" ,prostokaty(f4));
    printf( "wynik trapezy    - %lf\n" ,trapezy(f4));
    printf( "wynik MC   - %lf\n", mc(f4));
    
    return 0;
}