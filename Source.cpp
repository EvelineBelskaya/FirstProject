#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
const int n = 20;
const int size =100;
const int amountWords = 100;

void readDataFile(char *file1name, char words[n][size], int & amountStrings)//считываем файл1 и файл2 в символьный массив
{
	char strData[n];
	FILE *file;
	file = fopen(file1name, "r");
	if (!file) {
		printf("error file, name=%s\n", file1name);
		return;
	}

	int i = 0;
	int amountWords1 = 0;
	while (fgets(words[i], 255, file)) {
		puts(words[i]);
		i++;
	}
	fclose(file);
	amountStrings = i;
}
void strCopy(char * str, char *str2) 
{
	int i = 0;
	while (*str2) {
		str[i] = *str2;
		str2++;
		i++;
	}
	str[i] = '\0';
}

int getWordsFromText(char wordsFile1[amountWords][size],char  textFile1[n][size], int amountStrings)// вычленяем слова из текста
{
	int amount = 0;
	char sep[10] = "  .\""; // разделитель
    char *istr;
	for (int i = 0; i < amountStrings; i++) { // Выделение первой части строки
		istr = strtok(textFile1[i], sep);
 // Выделение последующих частей
		while (istr != NULL)
		{
			// Вывод очередной выделенной части
			strCopy(wordsFile1[amount], istr);
			// Выделение очередной части строки
			istr = strtok(NULL, sep);
			amount++;
		}
	}
	return amount;
}

int strcmpWithoutRegister(char * str1, char * str2) {
	//Приводим первую строку к нижнему регистру
	int i = 0;
	while (str1[i]) {
		str1[i] = tolower(str1[i]);
		i++;
	}
	//Приводим вторую строку к нижнему регистру
	i = 0;
	while (str2[i]) {
		str2[i] = tolower(str2[i]);
		i++;
	}
	return (strcmp(str1, str2) == 0) ? 0 : 1;
}

void createDataForFile4(char *file4name, int amountWords1, int amountWords2, int amountWords3, char wordsFile1[amountWords][size], char wordsFile2[amountWords][size], char wordsFile3[amountWords][size]) {
	printf("PERPLACEMENT\n");
	FILE *file4;
	file4 = fopen(file4name, "w");
	if (!file4) {
		puts("Net prav for creating file4\n");
		return;
	}
	for (int i = 0; i < amountWords2; i++) {
		for (int j = 0; j < amountWords1; j++) {
			if (strcmpWithoutRegister(wordsFile1[j], wordsFile2[i]) == 0) { //если строки равны, то нужно заменить слово 1 соответ из массива 3
				strcpy(wordsFile1[j], wordsFile3[i]);
				printf("replace %s -> %s \n", wordsFile1[j], wordsFile3[i]);
			}
		}
	}

	for (int j = 0; j < amountWords1; j++) {
		fputs(wordsFile1[j], file4);
		printf("%s\n", wordsFile1[j]);
		fputs("\n", file4);
	}
	
	fclose(file4);
}
void createDataForFile3(char * file3name, int amountWords1, int amountWords2, char wordsFile1[amountWords][size], char wordsFile2[amountWords][size])//записываем в  файл3 слова без указанных в файле 2
{
		//Открываем файл 3 на запись
		FILE *file3;
		file3 = fopen(file3name, "w");
		int flag = 1;
		for (int i = 0; i < amountWords1; i++) {
			for (int j = 0; j < amountWords2; j++) {
				if (strcmpWithoutRegister(wordsFile1[i], wordsFile2[j]) == 0) {
					flag = 0;
				}
			}
			if (flag) {
				fputs(wordsFile1[i], file3);
				printf("%s\n", wordsFile1[i]);
				fputs("\n", file3);
			}
			flag = 1;
			
		}
		fclose(file3);
}
int isExistFile(char * fileName) {
	FILE *file;
	file = fopen(fileName, "r");
	if (!file) {
		return 0;
	}
	else {
		fclose(file);
		return 1;//все ок
	}
}
int menu() {
    printf("Dear polzovatel, Input 1 or 2:");
	int result;
	while (scanf("%d", &result) != 1) { //пока не будет введено целое число, потворять запрос ввода
		while (getchar() != '\n')
			;//очищаем строку
		printf("Try more:");
	}
	printf("Thanks! Your choice  %d.\n", result);
	return result;
}


int main() {
	char file1[20];
	char file2[20];
	char file3[20];
	char file4[20];


	int result = menu();//выбор задачи
	getchar();
	//Массивы с предложениями из файлов
	char textFile1[n][size];
	char textFile2[n][size];
	char textFile3[n][size];

	//Количествро строк в каждом файле
	int amountStrings3 = 0;
	int amountStrings2 = 0;
	int amountStrings1 = 0;

	// Массивы со словами из файлов
	char wordsFile1[amountWords][size];
	char wordsFile2[amountWords][size];
	char wordsFile3[amountWords][size];

	//Количесто слов в каждом файле
	int words1, words2, words3;
	switch (result) {
	case 1:
		while (1) {
			puts("file name 1:");
			gets_s(file1);
			if (isExistFile(file1)) break;
			puts("Input name of file more:");
		}
		while (1) {
			puts("file name 2");
			gets_s(file2);
			if (isExistFile(file2)) break;
			puts("Input name of file more:");
		}
		puts("file name 3");
		gets_s(file3);
		readDataFile(file1, textFile1, amountStrings1);
		readDataFile(file2, textFile2, amountStrings2);

		words1 = getWordsFromText(wordsFile1, textFile1, amountStrings1);
	    words2 = getWordsFromText(wordsFile2, textFile2, amountStrings2);

		createDataForFile3(file3, words1, words2, wordsFile1, wordsFile2);
		break;
	case 2:
		while (1) {
			puts("file name 1:");
			gets_s(file1);
			if (isExistFile(file1)) break;
			puts("Input name of file more:");
		}
		while (1) {
			puts("file name 2");
			gets_s(file2);
			if (isExistFile(file2)) break;
			puts("Input name of file more:");
		}
		while (1) {
			puts("file name 3");
			gets_s(file3);
			if (isExistFile(file3)) break;
			puts("Input name of file more:");
		}
		
		puts("file name 4");
		gets_s(file4);
		
		readDataFile(file1, textFile1, amountStrings1);
		readDataFile(file2, textFile2, amountStrings2);
		readDataFile(file3, textFile3, amountStrings3);

		words1 = getWordsFromText(wordsFile1, textFile1, amountStrings1);
		words2 = getWordsFromText(wordsFile2, textFile2, amountStrings2);
		words3 = getWordsFromText(wordsFile3, textFile3, amountStrings3);
		if (words2 != words3) {
			printf("Wrong amount words in files 2=%d and 3=%d\n", words2, words3);
			getchar(); 
		}
		createDataForFile4(file4, words1, words2, words3, wordsFile1, wordsFile2, wordsFile3);
		break;
	default:
		printf("Wrong input!");
		break;
	}

	_getch();
	return 0;
}