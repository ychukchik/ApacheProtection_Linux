#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PAS_SIZE 4
#define CODE_SIZE 6
#define BYTE 8

void decode_base64(char*, char*);

int main()
{
	char encode[CODE_SIZE+1];
	char password[PAS_SIZE + 1] = { 0 };

	decode_base64(encode, password);

	return 0;
}

void decode_base64(char* encode, char* password)
{
	printf("Enter code: ");
	(void)scanf("%6s", encode); // 6 == CODE_SIZE
	int count = 0;
	while (encode[count] != '\0') count++;
	printf("Code size = %d\n", count);

	
	int size_bit_code = count * BYTE + 1;
	char* bit_code = (char*)calloc(size_bit_code, sizeof(char));
	if (bit_code == NULL)
	{
		printf("No memory in bit_code!");
		exit(-1);
	}

	//перевод символов в битовое представление и их запись в массив
	char tmp;
	int tmp_count;
	int bit_code_iterator = 0;
	for (int i = 0; i < count; i++)
	{
		//составление соответствия таблицы ascii с таблицей base64
		tmp = encode[i];
		if (tmp >= 'A' && tmp <= 'Z') tmp -= 65; //65==код 'A' в ASCII
		else if (tmp >= 'a' && tmp <= 'z') tmp = tmp - 97 + 26; //97==код 'a' в ASCII, 26==код 'a' в base64
		else if (tmp >= '0' && tmp <= '9') tmp = tmp - 48 + 52; //48==код '0' в ASCII, 52==код '0' в base64
		else if (tmp == '_') tmp = 62; //62==код '_' в base64
		else
		{
			printf("Encorrect value!\n");
			exit(-1);
		}

		tmp_count = 1;

		if (bit_code)
		{
			while (tmp_count <= 6 && bit_code_iterator < size_bit_code)
			{
				bit_code[bit_code_iterator] = tmp & 0x20 ? '1' : '0'; //0x20 это 6ой разряд
				bit_code_iterator++;
				tmp_count++;
				tmp = tmp << 1;
			}
		}
	}
	if(bit_code)bit_code[bit_code_iterator] = '\0';
	printf("bit_code = %s\n", bit_code);

	//перевод массива в исходные символы по 8 бит
	int pass_iterator = -1;
	int digit;
	for (int i = 0; i < bit_code_iterator;i++)
	{
		if (!(i % BYTE))
		{
			pass_iterator++;
			password[pass_iterator] = 0;
			digit = 0x80; // 0x80 это 8ой разряд
		}
		password[pass_iterator] += digit * (bit_code[i] - '0');
		digit >>= 1;
	}
	printf("password = %s\n", password);

	free(bit_code);
}