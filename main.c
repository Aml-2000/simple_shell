#include "shell.h"
/**
 * main -simple shell main function 
 * @ac: count of argumnents
 * @av: arguments
 * return: 0 always (success)
 */
int main(int ac, char **argv)
{
	char *line = NULL;
	char **command = NULL;
	int status;
	(void) ac;

	while (1)
	{
		line = read_line();
		if (line == NULL) 
			return (status);

		command = tokenizer(line);

		status = _execute(command, argv);
	}
}
