/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:28:21 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/16 01:08:27 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGFT_H
# define SIGFT_H

# include "types.h"
# include <signal.h>

# define SIG_INTERACTIVE 1
# define SIG_NON_INTERACTIVE 0
# define SIG_CHILD 2

void	setup_signals_interactive(void);
void	setup_signals_noninteractive(void);
void	setup_signals_child(void);
void	signal_handler_interactive(int sig);
void	signal_handler_noninteractive(int sig);
void	ignore_sigquit(void);
int		check_child_signal_status(void);

#endif
