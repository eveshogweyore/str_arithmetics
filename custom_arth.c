#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * _putchar - prints a character to standard output
 * @c: The character to be printed.
 *
 * Return: On success, 1. On error, -1.
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * _strlen - calculates the length of a string
 * @str: The given string.
 *
 * Return: On success, length of given string.
 */
int _strlen(char *str)
{
	int len = 0;

	for (; *str != '\0'; str++)
		len++;

	return (len);
}

/**
 * _putstr - prints string to standard output
 * @str: The string to be printed.
 *
 * Return: On success, length of string printed.
 */
int _putstr(char *str)
{
	return (write(STDOUT_FILENO, str, _strlen(str)));
}

/**
 * _putstr - prints string in reverse to standard output
 * @str: The string to be printed.
 *
 * Return: Length of string printed.
 */
int _putstr_rev(char *str)
{
	int i, last_idx = _strlen(str) - 1;

	for (i = last_idx; i >= 0; i--)
		_putchar(str[i]);

	return (last_idx + 1);
}

/**
 * _addstr - adds two numbers in string format
 * @f_str: The first number.
 * @s_str: The second Number.
 *
 * Return: Nothing
 */
void _addstr(char *f_str, char *s_str)
{
	int last_idx, add, j = 0, carry = 0, unit;
	int f_idx, s_idx;
	char buff[1024];

	f_idx = _strlen(f_str) - 1;
	s_idx = _strlen(s_str) - 1;
	last_idx = f_idx > s_idx ? f_idx : s_idx;

	for (; last_idx >= 0; last_idx--, f_idx--, s_idx--, j++)
	{
		if (f_idx >= 0 && s_idx >= 0)
			add = (f_str[f_idx] - '0') + (s_str[s_idx] - '0') + carry;
		else if (f_idx < 0)
			add = (s_str[s_idx] - '0') + carry;
		else if (s_idx < 0)
			add = (f_str[f_idx] - '0') + carry;
		carry = add / 10;
		unit = add % 10;

		buff[j] = unit + '0';

		if (last_idx == 0)
		{
			if (carry)
			{
				j += 1;
				buff[j] = carry + '0';
			}
		}
	}
	buff[j] = '\0';

	_putstr_rev(buff);
}

/**
 * _str_to_num - Converts a string to a number.
 * @str: Sting to be converted.
 *
 * Return: On success, the converted string.
 */
int _str_to_num(char *str)
{
	int i = 0, num, curr = 0;

	for (i = 0; str[i]; i++)
	{
		num = curr * 10 + (str[i] - '0');
		curr = num;
	}

	return (num);
}

/**
 * _strdiv - Divides two stringed integers.
 * @f_num: The Dividend.
 * @s_num: The divisor.
 *
 * Return: On success, the result of the division. On failure, NULL.
 */
char *_strdiv(char *f_num, char *s_num)
{
	int idx, i, divi, mod = 0;
	int num, denom, buff_idx = 0;
	static char buff[1024];

	idx = _strlen(f_num) - 1;
	denom = _str_to_num(s_num);

	for (i = 0; i <= idx; i++)
	{
		num = mod * 10 + (f_num[i] - '0');
		if (num < denom)
		{
			mod = num;
			continue;
		}

		divi = num / denom;
		mod = num % denom;

		buff[buff_idx] = divi + '0';
		buff_idx++;
	}
	buff[buff_idx] = '\0';

	if (mod)
		return (NULL);
	else
		return (buff);
}

/**
 * _rm_newline - Removes the newline character at end of string.
 * @str: The string to be operated on.
 *
 * Return: Nothing.
 */
void _rm_newline(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

/**
 * main - Attempts to read from a file in the command line,
 * and find factors of number.
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	FILE *fp;
	char buff[1024];
	int i, len;
	char *prime[] = { "2", "3", "5", "7", "15485773"};

	len = sizeof(prime) / sizeof(prime[0]);
	if (argc == 2)
	{
		fp = fopen(argv[1], "r");
		if (!fp)
		{
			fprintf(stderr, "ERROR: Check if file <%s> is valid.\n", argv[1]);
			exit(EXIT_FAILURE);
		}

		while (fgets(buff, sizeof(buff), fp))
		{
			_rm_newline(buff);
			for (i = 0; i < len; i++)
				if (_strdiv(buff, prime[i]))
					break;
			printf("%s=%s*%s\n", buff, _strdiv(buff, prime[i]), prime[i]);
		}
	}
	else
	{
		fprintf(stderr, "USAGE: factor <file>\n");
		exit(EXIT_FAILURE);
	}

	return (0);
}
