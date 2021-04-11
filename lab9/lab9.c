/*
 * Программа-калькулятор с возможностью выполнения 
 * арифметических действий (+, -), унарный и бинарный варианты.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
	char problem[1024], *token;
	double sol = 0.0;
	bool waiting_for_sum = 1; // Первый токен всегда прибавляем
	bool waiting_for_dif = 0;

	// Записываем строку с задачей
	printf("Enter problem: ");
	gets(problem);
	
	token = strtok(problem, " ");
	
	while(token != NULL)
	{
		// Если запланирована арифметическая операция
		// — осуществляем её
		if(1 == waiting_for_sum)
		{
			// Складываем
			sol += atof(token);
			// Обнуляем ожидание
			waiting_for_sum = 0;
		}
		else if (1 == waiting_for_dif)
		{
			// Вычитаем
			sol -= atof(token);
			// Обнуляем ожидание
			waiting_for_dif = 0;
		}
		
		// Планируем операцию, которую хотим
		// осуществить над следующим токеном
		if(*token == '+')
			waiting_for_sum = 1;
		else if(*token == '-')
			waiting_for_dif = 1;
			
		token = strtok(NULL, " ");
	}
	
	// Выводим результат вычислений на консоль
	printf("\nSolution: %lf\n", sol);
	
	return 0;
}

