#include "holberton.h"
/**
 * main - runs the shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *fullpathbuffer = NULL, *copy = NULL, *buffer = NULL;
	char *PATH = NULL;
	char **av;

	PATH = _getenv("PATH");
	if (PATH == NULL)
		return (-1);
	while (1)
	{
		av = NULL;
		prompt();
		buffer = _read();
		if (*buffer != '\0')
		{
			av = tokenize(buffer);
			if (av == NULL)
			{
				free(buffer);
				continue;
			}
			fullpathbuffer = _fullpathbuffer(av, PATH, copy);
			if (checkbuiltins(av, buffer) == 1)
				continue;
			_forkprocess(av, buffer, fullpathbuffer);
		}
		else
			free(buffer);
	}
	return (0);
}
