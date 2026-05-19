#include "../../includes/minishell.h"

int wait_exit_code(int status) //"W Exit Status" — what was the exit code?
{
	int exit_code;

	exit_code = ((status >> 8) & 0xff);
	return (exit_code);
}

int wait_exit_state(int status) //if killed by signal return the signal if not return 0
{
	if ((status & 0x7f) == 0)
		return (0);
	else
		return (status & 0x7f);
}
