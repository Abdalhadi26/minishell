/*
** echo.c
**
** Implements the echo builtin command.
** echo prints its arguments to standard output.
**
** Why is echo a builtin?
**   Because the subject requires it. In real bash, echo is both
**   a builtin AND an external program (/bin/echo). We only need
**   to implement the builtin version.
**
** The -n flag:
**   By default echo prints a newline at the end of its output.
**   The -n flag suppresses that newline.
**   Example: echo hello      prints: hello\n
**   Example: echo -n hello   prints: hello  (no newline, prompt follows)
**
** The tricky part about -n:
**   Multiple -n flags are all valid: echo -n -n -n hello
**   A flag like -nnn is also valid (all n's after the dash)
**   But -nnnb is NOT a valid -n flag (contains a non-n character)
**   So echo -nnnb hello  prints: -nnnb hello  (with newline)
**   The rule: strip leading -n flags as long as every character
**   after the dash is the letter n. Stop at the first non-n character.
**
** Think of echo as the simplest possible builtin - it just prints
** what you give it. The complexity is entirely in the -n flag logic.
*/
#include "../../includes/minishell.h"

static int	is_a_flag(char	*arg)
{
	int	i;

	i = 0;
	if (!arg)
    	return (0);
	if (arg[i] == '-')
		i++;
	else
		return (0);
	if (!arg[i])
		return (0);
	while (arg[i] == 'n')
		i++;
	if (!arg[i])
		return (1);
	return (0);
}

int	builtin_echo(t_single_command cmd)
{
	int	i;
	int	flag_status;

	flag_status = 0;
	i = 1;
	while (is_a_flag(cmd.args[i]))
	{
		flag_status = 1;
		i++;
	}
	while (cmd.args[i])
	{
		ft_putstr_fd(cmd.args[i], 1);
		if (cmd.args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag_status)
		write(1, "\n", 1);
	return (0);
}
