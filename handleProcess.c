#include "shell.h"

/**
 * create_process - system execution with fork
 * @command: The command to be executed
 * @arrayStr: Array of strings gotten from the command line
 * @argv: Argument vector
 * @env: Environment variable from parent
 * Return: void
*/

void create_process(char *command, char **arrayStr, char **argv, char *env[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(command, arrayStr, env) == -1)
		{
			free(command);
			free(arrayStr);
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(child_pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}


/**
 * accessCommand - Accesses and executes a command.
 * @arrayStr: An array of strings representing the command and its arguments.
 * @argv: An array of strings containing command-line arguments.
 * @env: An array of strings containing environment variables.
 * Return: None.
*/

int accessCommand(char **arrayStr, char **argv, char *env[])
{
	int p;


/*	if (is_builtin_command(arrayStr[0]))
	{
		free(command);
		execute_builtin_command(arrayStr[0], arrayStr,argv, env);
	}
*/
	if (access(arrayStr[0], F_OK) == 0)
	{
		create_process(arrayStr[0], arrayStr, argv, env);
		return (0);
	}

	p = handle_path(arrayStr, argv, env);

	return (p);
}

int handle_path(char **arrayStr, char **argv, char **env)
{
	char *command;
	char *shell_path, *path;

	path = get_path();
	if (path == NULL)
	{
		command_not_found(arrayStr, argv);
		free(path);
		return (127);
	}

	shell_path = _strtok(path, ":");
	if (shell_path != NULL)
	{
		while (shell_path != NULL)
		{
			command = malloc(strlen(shell_path) +
				strlen(arrayStr[0]) + 2);
			if (!command)
			{
				write(2, "Unable to allocate memory\n", 26);
				free(path), free(shell_path);
				exit(EXIT_FAILURE);
			}
			_strcpy(command, shell_path);
			/* shell_path does not end with '/' */
			_strcat(command, "/");
			_strcat(command, arrayStr[0]);
			if (access(command, F_OK) == 0)
			{
				free(path);
				create_process(command, arrayStr, argv, env);
				free(command);
				return (0);
			}
			shell_path = _strtok(NULL, ":");
			free(command);
		}
		free(shell_path);
	}
	command_not_found(arrayStr, argv);
	free(path), free(shell_path);
	return (127);
}
