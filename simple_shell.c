#include "main.h"

/**
 * main - Simple shell program.
 * @ac: argument count.
 * @av: Argument vector array.
 * @env: Environmental variable.
 * Return: 0.
 */

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **env)
{
	size_t len = 0;
	ssize_t bytes_read, return_value;
	char *buff = NULL, **tokens, *argv[2];
	pid_t pid;
	int status, i;

	printf("$ ");
	while ((bytes_read = getline(&buff, &len, stdin)) != EOF)
	{
		if (bytes_read == -1)
		{
			return (1);
		}
		if (buff[bytes_read - 1] == '\n')
			buff[bytes_read - 1] = '\0';

		tokens = split_string(buff);
		if (tokens == NULL)
			return (1);

		argv[0] = tokens[0];
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
			return (1);

		if (pid == 0)
		{
			(return_value = execve(argv[0], argv, env));
			if (return_value == -1)
			{
				perror("No executable found");
				return (1);
			}
		}
		else
		{
			wait(&status);
			printf("$ ");
		}
		for (i = 0; tokens[i] != NULL; i++)
		{
			free(tokens[i]);
		}
		free(tokens);
	}
	free(buff);
	return (0);
}
