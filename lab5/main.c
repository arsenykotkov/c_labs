#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main()
{
	system("chcp 1251"); // Кириллица в консоли
	system("cls"); // Очистить консоль, чтобы убрать надпись "Active code page: 1251"
	
	int i, j, N;
	char mode; // Выбор режима: "+", "-" или "*"
	double **matrix1, **matrix2, **result;
	
	printf("Укажите размерность для двух квадратных матриц: ");
	scanf("%i", &N);
	
	// Выделяем память под матрицы, учитывая указанную размерность
	
	matrix1 = (double**)malloc(N * sizeof(double*));
	matrix2 = (double**)malloc(N * sizeof(double*));
	result = (double**)malloc(N * sizeof(double*));
	
	for(i = 0; i < N; i++)
	{
		matrix1[i] = (double*)malloc(N * sizeof(double));
		matrix2[i] = (double*)malloc(N * sizeof(double));
		result[i] = (double*)malloc(N * sizeof(double));
	}
	
	// Вводим с консоли значения элементов матриц
	
	printf("Введите значения элементов первой матрицы: ");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			scanf("%lf", &matrix1[i][j]);
		}
	}
	printf("Введите значения элементов второй матрицы: ");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			scanf("%lf", &matrix2[i][j]);
		}
	}
	
	// Предпросмотр введённых данных
	
	printf("\nПервая матрица: \n");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			printf("%lf ", matrix1[i][j]);
		}
		puts("");
	}
	printf("\nВторая матрица: \n");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			printf("%lf ", matrix2[i][j]);
		}
		puts("");
	}
	printf("\n");
	
	printf("Укажите действие, которое необходимо произвести над этими матрицами (\"+\", \"-\" или \"*\"): ");
	scanf(" %c", &mode);
	
	if(mode == '+')
	{
		result = sum(N, matrix1, matrix2);
	}
	else if(mode == '-')
	{
		result = difference(N, matrix1, matrix2);
	}
	else if(mode == '*')
	{
		result = multiplication(N, matrix1, matrix2);
	}
	
	printf("\nПолучившаяся матрица:\n");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			printf("%lf ", result[i][j]);
		}
		puts("");
	}
	
	return 0;
}
