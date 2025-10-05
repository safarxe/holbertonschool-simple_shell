#include "main.h"
#include <string.h>
#include <stdlib.h>

/**
 * fill_args - Tokenizes a string into an array of arguments.
 * @input_buffer: The string to tokenize.
 * Return: A NULL-terminated array of pointers to tokens.
 */
char **fill_args(char *input_buffer)
{
	char *token;
	char **argv;
	int count = 0;
	int i;

	/* Count tokens first */
	token = strtok(input_buffer, " \t");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t");
	}

	/* Allocate memory for argv (count + 1 for NULL) */
	argv = malloc((count + 1) * sizeof(char *));
	if (!argv)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	/* Fill argv */
	i = 0;
	token = strtok(input_buffer, " \t");
	while (token)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (argv);
}
