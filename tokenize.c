#include "main.h"

char **split_string(char *str)
{
	char *token;
	char *str_cpy;
	char delim[] = {' ', ',', ';', ':'};
	int arr_size = 15, i = 0;
	char **str_token;

	str_token = malloc(sizeof(char *) * arr_size);
	if (str_token == NULL)
	{
		exit(98);
	}

	str_cpy = strdup(str);
	if (str_cpy == NULL)
	{
		free(str_token);
		exit(98);
	}

	token = strtok(str_cpy, delim);

	while (token != NULL)
	{
		if (i >= arr_size)
		{
			arr_size += 2;
			str_token = realloc(str_token, sizeof(char *) * arr_size);
			if (str_token == NULL)
			{
				free(str_token);
				free(str_cpy);
				exit(98);
			}
		}
		str_token[i] = strdup(token);
		if (str_token[i] == NULL)
		{
			free(str_token);
			free(str_cpy);
			exit(98);
		}
		token = strtok(NULL, delim);
		i++;
	}
	str_token[i] = NULL;
	free(str_cpy);
	return (str_token);
}
