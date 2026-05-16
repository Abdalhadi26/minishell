#include "../../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;

	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_interactive_signals()
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_execution_signals()
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

//While a child is running:

//Ctrl-C → signal reaches child naturally (same process group), child dies, 
//parent gets exit status 130
//Ctrl-\ → child dies with 131, parent picks it up via waitpid
//Parent itself ignores both during wait