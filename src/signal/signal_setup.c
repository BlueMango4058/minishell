/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:43:04 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/19 10:46:15 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigft.h"
#include <string.h>

void	setup_signals_interactive(void)
{
	struct sigaction	sa_int;

	ignore_sigquit();
	memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = signal_handler_interactive;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
}

void	setup_signals_noninteractive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = SIG_IGN;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	memset(&sa_quit, 0, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_signals_child(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_int, NULL);
	memset(&sa_quit, 0, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
