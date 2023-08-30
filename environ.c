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

char *get_path(void)
{
	char *path, *path_cpy;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);

	path_cpy = strdup(path);

	return (path_cpy);
}
