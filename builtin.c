#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure that contains arguments
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int _myexit(info_t *info)
{
	int a;

	if (info->argv[1])
	{
		a = _erratoi(info->argv[1]);
		if (a == -1)
		{
			info->status = 2;
			print_error(info, "Wrong number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		else
		{
			info->err_num = a;
		}
	}
	else
	{
		info->err_num = -1;
	}
	return (-2);
}

/**
 * _mycd -  Changes the current directory
 * @info: the parameter and return info struct
 * Return: 0 always
 */
int _mycd(info_t *info)
{
	char *dir;
	char buffer[1024];
	int chdir_ret;
	char *s = getcwd(buffer, 1024);

	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 *  _myhelp - Prints a help message
 *  @info: the parameter and return info struct and the arg_ array
 *  Return: if true the output it's 0
 */
int _myhelp(info_t *info)
{
	char **arg_array = info->argv;

	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* Temporary unused workaround */

	return (0);
}


