#include "main.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * file_exists - Checks if a file exists
 * @file: The name of the file to check
 * Return: 0 if exists, 1 if not
 */
int file_exists(char *file)
{
	struct stat st;
	if (stat(file, &st) == 0)
		return (0);
	return (1);
}

/**
 * get_command_path - Finds full path of a command in PATH
 * @cmd: Command name
 * @work_buffer: Buffer to store full path
 * Return: 0 if found, 1 if not
 */
int get_command_path(char *cmd, char *work_buffer)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char *full_path;

	/* Check if it's an absolute or relative path */
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || 
		(cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	{
		if (file_exists(cmd) == 0)
		{
			strcpy(work_buffer, cmd);
			return (0);
		}
		return (1);
	}

	path_env = _getenv("PATH");
	if (!path_env || strlen(path_env) == 0)
		return (1);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (1);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (1);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (file_exists(full_path) == 0)
		{
			strcpy(work_buffer, full_path);
			free(full_path);
			free(path_copy);
			return (0);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (1);
}

/**
 * execute_command - Executes a command
 * @argv: Argument array
 * Return: Exit status
 */
int execute_command(char *argv[])
{
	pid_t pid;
	int status;
	char work_buffer[1024];

	if (get_command_path(argv[0], work_buffer))
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		return (127);
	}

	pid = fork();
	if (pid < 0)
		return (shell_error());

	if (pid == 0)
	{
		execve(work_buffer, argv, environ);
		/* If execve fails */
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		exit(127);
	}

	wait(&status);

	if (WIFEXITED(status))
		status = WEXITSTATUS(status);

	return (status);
}
