#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct person
{
	char *first;
	char *last;
	int year;
	int sex;
	double height;
} PERSON;

PERSON **persons;
PERSON *buffer;
int lines = 0;

// Меняет местами два элемента массива структур типа PERSON
void swap(j)
{
	buffer = persons[j];
	persons[j] = persons[j + 1]; 
	persons[j + 1] = buffer;
}

// Сортирует по имении
void by_first()
{
	int i, j;
	for(i = 0; i < lines - 1; i++)
		for(j = 0; j < lines - i - 1; j++)
			if(strcmp(persons[j]->first, persons[j + 1]->first) == 1)
				swap(j);
}

// Сортирует по фамилии
void by_last()
{
	int i, j;
	for(i = 0; i < lines - 1; i++)
		for(j = 0; j < lines - i - 1; j++)
			if(strcmp(persons[j]->last, persons[j + 1]->last) == 1)
				swap(j);
}

// Сортирует по году рождения
void by_year()
{
	int i, j;
	for(i = 0; i < lines - 1; i++)
		for(j = 0; j < lines - i - 1; j++)
			if(persons[j]->year > persons[j + 1]->year)
				swap(j);
}

// Сортирует по полу
void by_sex()
{
	int i, j;
	for(i = 0; i < lines - 1; i++)
		for(j = 0; j < lines - i - 1; j++)
			if(persons[j]->sex > persons[j + 1]->sex)
				swap(j);
}

// Сортирует по росту
void by_height()
{
	int i, j;
	for(i = 0; i < lines - 1; i++)
		for(j = 0; j < lines - i - 1; j++)
			if(persons[j]->height > persons[j + 1]->height)
				swap(j);
}

int main(int argc, char **argv)
{
	
	system("chcp 1251"); // Кириллица в консоли
	system("cls"); // Очистить консоль, чтобы убрать надпись "Active code page: 1251"
	
	FILE *in, *out;
	
	char query[6]; // Строка с настройками сортировки
	
	int i;
	
	char first[32];   //
	char last[32];    //
	int year;         // Буфер
	int sex;          //
	double height;    //
	
	out = fopen("output.txt", "w");
	while(--argc)
	{
		in = fopen(argv[argc], "r");
		if(in == NULL)
		{
			printf("Не удалось прочитать файл: %s\n", argv[argc]);
			exit(0);
		}
		
		printf("Обрабатывается файл: %s\n", argv[argc]);
		while(fscanf(in, "%*[^\n]%*c") != EOF)
			lines++;
			
		// Закрываем и открываем файл заново, чтобы переместить файловый указатель
		// на начало файла. Сейчас fscanf(in, "%*[^\n]%*c") сдвинул его в самый конец
		fclose(in);
		in = fopen(argv[argc], "r");		
		
		// Выделяем память под динамический массив структур типа PERSON
		persons = (PERSON**)malloc(lines * sizeof(PERSON*));
		
		for(i = 0; i < lines; i++)
		{
			persons[i] = (PERSON*)malloc(sizeof(PERSON));
			
			fscanf(in, "%s%s%i%i%lf", first, last, &year, &sex, &height);
			
			persons[i]->first = (char*)malloc(strlen(first) * sizeof(char));
			strcpy(persons[i]->first, first);
			
			persons[i]->last = (char*)malloc(strlen(last) * sizeof(char));
			strcpy(persons[i]->last, last);
			
			persons[i]->year = year;
			persons[i]->sex = sex;
			persons[i]->height = height;
		}
		
		// Выбор критериев сортировки
		printf("Укажите критерии сортировки без пробелов\n<и> по имени\n<ф> по фамилии\n<г> по году рождения\n<п> по полу\n<р> по росту:\n > ");
		
		// Записываем в строчку настройки сортировки
		scanf("%s", query);
		
		// Читаем по одному символу из настроек
		for(i = 0; i < strlen(query); i++)
		{
			// и вызываем соответствующую функцию
			switch(query[i])
			{
				case 'и': printf("Сортировка по имени\n"); by_first(); break;
				case 'ф': printf("Сортировка по фамилии\n"); by_last(); break;
				case 'г': printf("Сортировка по году рождения\n"); by_year(); break;
				case 'п': printf("Сортировка по полу\n"); by_sex(); break;
				case 'р': printf("Сортировка по росту\n"); by_height(); break;
			}
		}
		
		// Записываем строчки в файл
		for(i = 0; i < lines; i++)
			fprintf(out, "%s %s %i %i %lf\n", persons[i]->first, persons[i]->last, persons[i]->year, persons[i]->sex, persons[i]->height);
	}
	getch();
	return 0;
}
