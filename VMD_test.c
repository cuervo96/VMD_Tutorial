#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "visualizacion.h"

double set_box(double *X, int N, double L);
int PBC_pos(double *X, double L,int N);

int main()
{
int L = 10, i, j, n = 6, N = n*n*n, N_pasos = 5000, N_frames = 500, N_skip = (int) N_pasos / N_frames;  
double *x, *v;
x = (double*) malloc(3 * N * sizeof(double));
v = (double*) malloc(3 * N * sizeof(double));

char filename[255];
sprintf(filename, "test_movimiento.lammpstrj");
set_box(x, N, L);
srand(time(NULL));
for(j = 0; j < N_pasos; j++)
{
    for(i = 0; i < 3 * N; i++)
    {
        *(v + i) =  (double)rand() / RAND_MAX * 2 - 1;
        //printf("Velocidad = %lf \n", *(v + i));
    }
    for(i = 0; i < 3 * N; i++)
    {
        *(x + i) = *(x + i) + *(v + i) * 0.05;
    } 
    PBC_pos(x, L, N);
    if(j % N_skip == 0)
    save_lammpstrj(filename, x, v, N, L, (int) j / N_skip);
}
return 0;
}
double set_box(double *X, int N, double L)
{ // Ordena las partículas en una red cúbica. Coición inicial.
int n=cbrt(N),i=0;
double dl=L/n;
for(int x = 0; x < n; x++)
	{
	for(int y = 0; y < n; y++)
		{
		for(int z = 0; z < n; z++)
			{
			*(X+3*i) = (x+0.5)*dl;
			*(X+3*i+1) = (y+0.5)*dl;
			*(X+3*i+2) = (z+0.5)*dl;
			i++;
			}
		}
	}
return dl;
}
int PBC_pos(double *X, double L,int N)
{
for(int i = 0; i < 3 * N; i++)
	{
	if(*( X + i) > L)
		{
		*(X + i) -= L;
		}
	else if(*(X + i) < 0) 
		{
		*(X + i) += L;
		}
	}
return 0;
}
#include "visualizacion.c"