
#include "main.h"


/**
 * _write_str - Writes a string to standard output.
 *
 * @str: The string to be written.
 */
void _write_str(const char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * _write_int - Writes an integer to standard output.
 *
 * @num: The integer to be written.
 */
void _write_int(int num)
{
	char buffer[20]; /* Assuming a reasonable buffer size */
	int length = 0;
	int temp = num;

	/* Handle negative numbers */
	if (temp < 0)
	{
		_write_char('-');
		temp = -temp;
	}

	/* Convert the integer to a string in reverse order */
	do {
		buffer[length++] = temp % 10 + '0';
		temp /= 10;
	} while (temp > 0);

	/* Reverse the string to get the correct order */
	for (int i = 0, j = length - 1; i < j; i++, j--)
	{
		char tmp = buffer[i];

		buffer[i] = buffer[j];
		buffer[j] = tmp;
	}

	write(STDOUT_FILENO, buffer, length);
}


/**
 * _write_char - Writes a single character to standard output.
 *
 * @c: The character to be written.
 */
void _write_char(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

/**
 * _write_newline - Writes a newline character to standard output.
 */
void _write_newline(void)
{
	char newline = '\n';

	write(STDOUT_FILENO, &newline, 1);
}
