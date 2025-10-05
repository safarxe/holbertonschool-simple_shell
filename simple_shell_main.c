#include "main.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * process_line - Process a single line of input
 * @buffer: The line to process
 * @last_status: Pointer to store the last command status
 * Return: 0 to exit, 1 to continue
 */
int process_line(char *buffer, int *last_status)
{
	char *argv[64];
	int argc = 0;
	char *tok;

	/* Tokenize input into argv */
	tok = strtok(buffer, " \t");
	while (tok && argc < 63)
	{
		argv[argc++] = tok;
		tok = strtok(NULL, " \t");
	}
	argv[argc] = NULL;

	if (argv[0] == NULL)
		return (1);

	/* Handle 'env' command */
	if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		*last_status = 0;
		return (1);
	}

	/* Handle 'exit' command */
	if (strcmp(argv[0], "exit") == 0)
		return (0);

	*last_status = execute_command(argv);
	return (1);
}

/**
 * main - Entry point of the simple shell.
 * Return: 0 on success, >0 on failure.
 */
int main(void)
{
	char buffer[1024];
	ssize_t nread;
	int interactive;
	int i, line_start;
	int last_status = 0;

	/* Ignore Ctrl+C */
	signal(SIGINT, SIG_IGN);
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(1, "$ ", 2);

		nread = read(STDIN_FILENO, buffer, 1023);
		if (nread <= 0)
		{
			if (interactive)
				write(1, "\n", 1);
			break; /* Ctrl+D or EOF */
		}

		buffer[nread] = '\0';

		/* Process each line separately */
		line_start = 0;
		for (i = 0; i <= nread; i++)
		{
			if (buffer[i] == '\n' || buffer[i] == '\0')
			{
				if (i > line_start)
				{
					buffer[i] = '\0';
					if (!process_line(&buffer[line_start], &last_status))
						return (last_status);
				}
				line_start = i + 1;
			}
		}
	}

	return (last_status);
}