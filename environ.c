#include "shell.h"

/**
 * env_variable - reads envrionment varibles of the system and searches for the
 *		  PATH varialbe
 *
 * @env: array containing the environment variables
 *
 * Return: return the PATH environment variable if found
 *	   return NULL if PATH variable is empty or not found
*/

char *get_path(char **env)
{
	int i;
	char *path;
	char **split_var;

	if (env == NULL)
		return (NULL);

	for (i = 0; env[i] != NULL; i++)
	{
		path = strdup(env[i]);
		split_var = parse(path, "=");
		if (_strcmp(split_var[0], "PATH") == 0)
		{
			if (split_var[1] == NULL)
				return (NULL);
			return (split_var[1]);
		}
	}
	return (NULL);
}
