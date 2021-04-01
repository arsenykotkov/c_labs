#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person
{
	char *first;
	char *last;
	int date;
} PERSON;

PERSON **persons;
PERSON **sorted;
int stored = 0;

int main(int argc, char *argv[])
{
	system("chcp 1251"); // Кириллица в консоли
	system("cls"); // Очистить консоль, чтобы убрать надпись "Active code page: 1251"
	
	int i, j, N;
	
	// Три переменные ниже являются буферами соответственно для
	// имени, фамилии и года рождения человека, которого мы записываем
	// (или сортируем) на данном шаге цикла
	char first[32];
	char last[32];
	int date;
	
	printf("Введите количество людей, которое вы хотите записать: ");
	scanf("%i", &N);
	
	// Выделяю память под двухмерный массив структур типа PERSON
	persons = (PERSON**)malloc(N * sizeof(PERSON*));
	
	// Вынес подсказку для пользователя из цикла, чтобы не повторялась
	printf("Введите <имя> <фамилию> <год рождения> для человека c ID\n");
	
	// Цикл выполняется до тех пор, пока я не обработаю инфомацию
	// о всех людях (количество людей — N)
	for(i = 0; i < N; i++)
	{
		// Подсказываем номер текущего человека в массиве
		printf("%i: ", i);
		
		// Читаем имя, фамилию и год рождения с консоли и записываем в буфер
		scanf("%s%s%i", first, last, &date);
		
		// Выделяю память под текущий элемент массива PERSON
		persons[i] = (PERSON*)malloc(sizeof(PERSON));
		
		// Выделяю память под имя текущего человека
		persons[stored]->first = (char*)malloc(strlen(first) * sizeof(char));
		
		// Копирую имя из буфера в свежевыделенное место в структуре
		strcpy(persons[stored]->first, first);
		
		// Выделяю память под фамилию текущего человека
		persons[stored]->last = (char*)malloc(strlen(last) * sizeof(char));
		
		// Копирую фамилию из буфера в свежевыделенное место в структуре
		strcpy(persons[stored]->last, last);
		
		// Тип int по умолчанию резервирует место в памяти размером в 4 байта,
		// чего с головой хватит для хранения четырёхзначной даты
		persons[stored]->date = date;
		
		// Увеличиваем счётчик хранящихся в массиве людей на единичку
		stored++;
	}
	
	// Копирую массив persons в массив sorted
	memcpy(&sorted, &persons, sizeof(persons));
	
	// Освобождаем память динамического массива persons, он нам больше не нужен,
	// так как его копия хранитя в массиве sorted
	free(persons);
	for(i = 0; i < N; i++)
		free(persons[i]);

	// Сортирую пузырьком массив sorted по году рождения (от младшего к старшему)
	for(i = 0; i < N - 1; i++)
	{
		for(j = 0; j < N - 1 - i; j++)
		{
			// Если текущий элемент "старше" следующего — меняем местами
			// параметры этих структур
			if(sorted[j]->date < sorted[j + 1]->date)
			{
				// Меняем местами имена двух соседних элементов
				strcpy(first, sorted[j + 1]->first);
				strcpy(sorted[j + 1]->first, sorted[j]->first);
				strcpy(sorted[j]->first, first);
				
				// Меняем местами фамилии двух соседних элементов
				strcpy(last, sorted[j + 1]->last);
				strcpy(sorted[j + 1]->last, sorted[j]->last);
				strcpy(sorted[j]->last, last);
				
				// Меняем местами годы рождения двух соседних элементов
				date = sorted[j + 1]->date;
				sorted[j + 1]->date = sorted[j]->date;
				sorted[j]->date = date;
			}
		}
	}
	
	// Вывожу на консоль отсортированный массив людей sorted
	printf("Новый отсортированный массив людей (от младшего к старшему): \n");
	for(i = 0; i < N; i++)
		printf("%i: %s %s %i\n", i, sorted[i]->first, sorted[i]->last, sorted[i]->date);

	// Освобождаем память динамического массива sorted, теперь и он нам больше не нужен
	free(sorted);
	for(i = 0; i < N; i++)
		free(sorted[i]);
	
	return 0;
}
