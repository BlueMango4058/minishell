/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:21:27 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/18 20:46:13 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigft.h"
#include "global.h"
#include <termios.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

void	signal_handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_noninteractive(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sig == SIGQUIT)
		write(STDOUT_FILENO, "Quit(core dumped)\n", 19);
}

void	ignore_sigquit(void)
{
	struct sigaction	act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

int	check_child_signal_status(void)
{
	int		status;
	int		sig;
	pid_t	result;

	result = waitpid(-1, &status, WNOHANG);
	if (result > 0)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				return (g_exit_status = 130, 130);
			else if (sig == SIGQUIT)
				return (g_exit_status = 131, 131);
			g_exit_status = 128 + sig;
			return (128 + sig);
		}
		else if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
			return (WEXITSTATUS(status));
		}
	}
	return (0);
}
