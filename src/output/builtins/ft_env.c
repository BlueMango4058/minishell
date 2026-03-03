/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:10:59 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/16 19:24:14 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_cmd *cmd, t_shell *shell)
{
	t_envp	*current;

	if (!cmd || !shell || !shell->envp_list)
		return (FAILURE);
	if (!cmd->args[1])
	{
		current = shell->envp_list;
		while (current)
		{
			if (current->key && current->value)
				printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
	}
	return (SUCCESS);
}
