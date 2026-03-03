/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:29:54 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/18 21:45:00 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

char	*get_path_env(t_shell *shell)
{
	t_envp	*current;

	if (!shell || !shell->envp_list)
		return (NULL);
	current = shell->envp_list;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, "PATH") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	util_create_pipes(int **pipe_fds, int cmd_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(&(*pipe_fds)[i * 2]) == -1)
		{
			perror("pipe");
			j = 0;
			while (j < i)
			{
				if ((*pipe_fds)[j * 2] >= 0)
					close((*pipe_fds)[j * 2]);
				if ((*pipe_fds)[j * 2 + 1] >= 0)
					close((*pipe_fds)[j * 2 + 1]);
				j++;
			}
			free(*pipe_fds);
			*pipe_fds = NULL;
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	create_pipes(int **pipe_fds, int cmd_count)
{
	int	i;

	if (cmd_count <= 1)
	{
		*pipe_fds = NULL;
		return (SUCCESS);
	}
	*pipe_fds = malloc(sizeof(int) * 2 * (cmd_count - 1));
	if (!*pipe_fds)
		return (FAILURE);
	i = 0;
	while (i < (cmd_count - 1) * 2)
	{
		(*pipe_fds)[i] = -1;
		i++;
	}
	i = 0;
	if (util_create_pipes(pipe_fds, cmd_count) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	print_signal(int exit_status)
{
	if (exit_status == 130)
		write(STDOUT_FILENO, "\n", 1);
	else if (exit_status == 131)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}
