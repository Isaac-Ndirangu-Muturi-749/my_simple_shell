#include "main.h"

/**
 * _getline - Reads a line of text from a file descriptor and stores it in a
 *            dynamically allocated buffer.
 *
 * @lineptr: A pointer to a pointer to the buffer where the line is stored.
 * @n: A pointer to the size of the buffer.
 * @fd: The file descriptor to read from.
 *
 * Return: The number of bytes read, including the newline character, or -1 on
 *         error or when the end of file (EOF) is reached.
 *
 * Note: The function allocates memory for the lineptr if it's NULL or not
 * large enough to hold the line. It's the caller's responsibility to free
 * the memory when it's no longer needed.
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	ssize_t bytesRead = 0;
	ssize_t totalBytesRead = 0;
	char *line = *lineptr;

	if (line == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	while (1)
	{
		if ((size_t)totalBytesRead >= *n)
		{
			if (resize_buffer(lineptr, n) == -1)
				return (-1);
			line = *lineptr + totalBytesRead;
		}

		bytesRead = read(fd, line, 1);

		if (bytesRead == -1)
			return (-1);

		if (bytesRead == 0)
		{
			if (totalBytesRead == 0)
				return (-1);
			break;
		}

		line += bytesRead;
		totalBytesRead += bytesRead;

		if (*(line - 1) == '\n')
			break;
	}
	*line = '\0';
	return (totalBytesRead);
}


/**
 * resize_buffer - Resize the buffer pointed to by lineptr.
 *
 * @lineptr: A pointer to a pointer to the buffer.
 * @n: A pointer to the size of the buffer.
 *
 * Return: 0 on success, -1 on failure.
 */
int resize_buffer(char **lineptr, size_t *n)
{
	size_t new_size = (*n == 0) ? 128 : *n * 2;
	char *new_line = malloc(new_size);

	if (new_line == NULL)
		return (-1);

	if (*lineptr != NULL)
	{
		_memcpy(new_line, *lineptr, *n); /* Use your custom _memcpy function */
		free(*lineptr);
	}

	*lineptr = new_line;
	*n = new_size;

	return (0);
}

/**
 * _memcpy - Copy memory area from src to dest.
 *
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source buffer.
 * @n: Number of bytes to copy.
 *
 * Return: Pointer to the destination buffer.
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;

	while (n--)
	{
		*d++ = *s++;
	}

	return (dest);
}
