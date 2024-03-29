#include "main.h"

/**
 * exec_child - Executes child process to run execve.
 * @argv: Pointer to executable path from user.
 * @av: Pointer to array of pointer to arguments.
 * @env: Pointer to array of environment variables.
 * Return: 0.
 */

int exec_child(char *argv, char **av, char **env)
{
	ssize_t return_value;

	(return_value = execve(argv, av, env));
	if (return_value == -1)
	{
		perror("No such file or directory");
		exit(98);
	}
	return (0);
}


/**
 * main - Simple shell program.
 * @ac: argument count.
 * @av: Argument vector array.
 * @env: Environmental variable.
 * Return: 0.
 */

int main(__attribute__((unused)) int ac, char **av, char **env)
{
	size_t len = 0;
	ssize_t bytes_read;
	char *buff = NULL, **tokens, *argv[2];
	pid_t pid;
	int status, i, faccess;

	while (1)
	{
		printf("$ ");
		bytes_read = getline(&buff, &len, stdin);
		if (bytes_read == -1)
		{
			perror("getline error");
			return (1);
		}
		if (bytes_read == EOF)
		{
			break;
		}

		if (buff[bytes_read - 1] == '\n')
			buff[bytes_read - 1] = '\0';

		tokens = split_string(buff);
		if (tokens == NULL)
		{
			perror("tokenize error");
			return (1);
		}

		argv[0] = tokens[0];
		argv[1] = NULL;

		faccess = access(argv[0], X_OK);

		if (faccess == 0)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("Fork error");
				return (1);
			}
			if (pid == 0)
			{
				exec_child(argv[0], av, env);
				exit(0);
			}
			else
			wait(&status);
		}
		else
		{
			perror("File error");
		}
		for (i = 0; tokens[i] != NULL; i++)
		{
			free(tokens[i]);
		}
		free(buff);
	}
	return (0);
}
