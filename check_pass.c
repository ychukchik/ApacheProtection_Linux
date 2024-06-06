#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 127

typedef enum ERROR
{
	NOT_SIZE = 0b00000001,
	NO_S_REG = 0b00000010,
	NO_B_REG = 0b00000100,
	NO_SYM   = 0b00001000,
	NO_DIGIT = 0b00010000
}ERROR;

char* enter_pass(char*);
int check_password(char*);
int print_errors(int errors);

int main()
{
	while (1)
	{
		int errors = 0;
		char* pass = NULL;
		pass = enter_pass(pass);
		printf("%s\n", pass);
		errors = check_password(pass);
		free(pass);
		if (!print_errors(errors))
		{
			printf("Password is correct!");
			return 0;
		}
	}
	return 0;
}

char* enter_pass(char*pass)
{
	pass = (char*)calloc(MAX_SIZE + 1, sizeof(char));
	printf("Enter password: ");
	(void)scanf("%s", pass);
	return pass;
}

int check_password(char*pass)
{
	int errors = 0;
	//размер
	int count = strlen(pass);
	if (count < 10) errors |= NOT_SIZE;

	//регистры и символы
	int flag = 0;

	for (int i = 0; i < count; i++)
	{
		if (pass[i] >= 'a' && pass[i] <= 'z') flag = 1;
	}
	if (flag == 0) errors |= NO_S_REG;
	flag = 0;

	for (int i = 0; i < count; i++)
	{
		if (pass[i] >= 'A' && pass[i] <= 'Z') flag = 1;
	}
	if (flag == 0) errors |= NO_B_REG;
	flag = 0;

	for (int i = 0; i < count; i++)
	{
		if ((pass[i] >= 32 && pass[i] <= 47)||(pass[i] >= 58 && pass[i] <= 64)||(pass[i] >= 91 && pass[i] <= 96) || (pass[i] >= 123 && pass[i] <= 127)) flag = 1;
	}
	if (flag == 0) errors |= NO_SYM;
	flag = 0;

	for (int i = 0; i < count; i++)
	{
		if (pass[i] >= '0' && pass[i] <= '9') flag = 1;
	}
	if (flag == 0) errors |= NO_DIGIT;
	flag = 0;

	return errors;
}

int print_errors(int errors)
{
	if (errors & NOT_SIZE) printf("Error: size of password < 10!\n");
	if (errors & NO_S_REG) printf("Error: no symbols in small register!\n");
	if (errors & NO_B_REG) printf("Error: no symbols in big register!\n");
	if (errors & NO_SYM)   printf("Error: no special symbols!\n");
	if (errors & NO_DIGIT) printf("Error: no digits!\n");
	if (errors != 0)
	{
		printf("Enter new password!\n\n");
	}
	else return 0;

	return 1;
}