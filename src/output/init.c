/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 09:05:00 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 13:54:48 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "output.h"
#include "utils.h"

int	init_shell(t_shell *shell)
{
	if (!shell)
		return (FAILURE);
	shell->envp_list = NULL;
	shell->env_array = NULL;
	shell->last_exit_status = 0;
	shell->exit_flag = 0;
	shell->signal_mode = SIG_INTERACTIVE;
	return (SUCCESS);
}
