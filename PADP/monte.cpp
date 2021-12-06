#include <math.h>
#include <string.h>
#include <omp.h>
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <time.h> //to seed the random number generator
#define PI 3.14159265359
int main ()
{
int total, count, i, l;
float x, y, calculatedPi, difference;
printf ("Enter the number of samples:");
scanf ("%d", &total);
for(l=1;l<=8;l=l<<1){
//seed the random number generator
srand(time(NULL));
count = 0;
double start = omp_get_wtime();
omp_set_num_threads(l);
#pragma omp parallel for private(i) reduction(+:count)
for (i=0;i<total;i++){
x = (float)rand()/RAND_MAX;
y = (float)rand()/RAND_MAX;
if (x*x + y*y < 1.0f)
count++;
}
calculatedPi = 4.0f*count/total;
double end = omp_get_wtime();
difference = calculatedPi - PI;
printf ("\nCalculated PI: %f", calculatedPi);
printf ("\nError: %f", difference);
printf("\nTime taken for %d thread(s) for size %d: %lf\n",l,total,end-start);
}
return 0;
}
