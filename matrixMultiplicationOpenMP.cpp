#include <stdio.h>
#include <omp.h>

#define N 256
#define THREADS 8

double a[N][N], b[N][N], resultedMatrix[N][N]; // матрицы для перемножения и результирующая матрица

int main()
{
    omp_set_num_threads(THREADS);

    int i, j, k; // переменные для итерования
    double timeStart, timeEnd; // время начала выполнени перемножения и конца
    // инициализация матриц
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            a[i][j] = b[i][j] = i * j;
    timeStart = omp_get_wtime();

// основной вычислительный блок
#pragma omp parallel for shared(a, b, resultedMatrix) private(i, j, k)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            resultedMatrix[i][j] = 0.0;
            for (k = 0; k < N; k++)
                resultedMatrix[i][j] += a[i][k] * b[k][j];
        }
    }

    timeEnd = omp_get_wtime();
    printf("Time=%lf\n", timeEnd - timeStart);
}