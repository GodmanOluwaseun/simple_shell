#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * tokenize - tokenizes & Splits copied string using strtok.
 * @str_cpy: Pointer to copied string to be tokenized.
 * @delim: Array of delimiters.
 * @arr_size: Size of array.
 * @str_token: Pointer to array of pointers to tokens.
 * Return: Void.
 */

void tokenize(char *str_cpy, char delim[], int *arr_size, char **str_token)
{
	int i;
	char *token;

	token = strtok(str_cpy, delim);
	for (i = 0; token != NULL; i++, token = strtok(NULL, delim))
	{
		if (i >= *arr_size)
		{
		(*arr_size) += 2;
		str_token = realloc(str_token, sizeof(char *) * (*arr_size));
			if (str_token == NULL)
			{
				perror("Realloc error");
				free(str_token);
				free(str_cpy);
				exit(98);
			}
		}
		str_token[i] = strdup(token);
		if (str_token[i] == NULL)
		{
			perror("Strdup error");
			free(str_token);
			free(str_cpy);
			exit(98);
		}
	}
	str_token[i] = NULL;
}

/**
 * split_string - Tokenizes and returns array of tokenized a string.
 * @str: String to be tokenized.
 * Return: Pointer to array.
 */

char **split_string(char *str)
{
	char *str_cpy, **str_token, delim[] = {' ', '.', ',', ';', ':'};
	int arr_size = 15;

	str_token = malloc(sizeof(char *) * arr_size);
	if (str_token == NULL)
	{
		perror("Malloc error");
		exit(98);
	}

	str_cpy = strdup(str);
	if (str_cpy == NULL)
	{
		perror("Strdup error");
		free(str_token);
		exit(98);
	}

	tokenize(str_cpy, delim, &arr_size, str_token);

	free(str_cpy);
	return (str_token);
}
