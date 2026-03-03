/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:57:14 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/19 10:45:20 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "sigft.h"

static int	fork_and_execute(t_cmd *cmd, t_shell *shell, int *pipe_fds,	\
		t_exec_info *info)
{
	pid_t	pid;

	pid = fork_process();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_signals_child();
		setup_child_process(cmd, pipe_fds, info->cmd_index, info->cmd_count);
		if (setup_redirections(cmd) == FAILURE)
			exit (FAILURE);
		if ((!cmd || !cmd->args || !cmd->args[0]) && cmd->hd == -1)
			exit (FAILURE);
		if (cmd->args == NULL && cmd->hd > 0)
			g_exit_status = 0;
		else if (isbc(cmd->args[0]))
			g_exit_status = execute_builtin(cmd, shell);
		else
			g_exit_status = execute_external(cmd, shell);
		exit (g_exit_status);
	}
	else
		setup_parent_process(pipe_fds, info->cmd_index, info->cmd_count);
	return (pid);
}

static void	cleanup_resources(int *pipe_fds, pid_t *pids, int cmd_count)
{
	if (pipe_fds)
	{
		close_all_pipes(pipe_fds, cmd_count - 1);
		free(pipe_fds);
	}
	if (pids)
		free(pids);
}

static pid_t	*allocate_pids(int **pipe_fds, int cmd_count)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
	{
		if (*pipe_fds)
		{
			close_all_pipes(*pipe_fds, cmd_count - 1);
			free(*pipe_fds);
		}
		return (NULL);
	}
	return (pids);
}

static int	execute_all_commands(t_cmd *commands, t_shell *shell, \
								int *pipe_fds, pid_t *pids)
{
	t_cmd		*current;
	t_exec_info	info;
	int			i;

	info.cmd_count = count_commands(commands);
	current = commands;
	i = -1;
	while (current && ++i < info.cmd_count)
	{
		info.cmd_index = i;
		pids[i] = fork_and_execute(current, shell, pipe_fds, &info);
		if (pids[i] == -1)
		{
			while (--i >= 0)
				kill(pids[i], SIGTERM);
			cleanup_resources(pipe_fds, pids, info.cmd_count);
			return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		*pipe_fds;
	pid_t	*pids;
	int		cmd_count;

	if (!cmd || !shell)
		return (FAILURE);
	cmd_count = count_commands(cmd);
	if (cmd_count == 1 && ((cmd->args && isbc(cmd->args[0])) || !cmd->args))
		return (single_cmd(cmd, shell));
	if (create_pipes(&pipe_fds, cmd_count) == FAILURE)
		return (FAILURE);
	pids = allocate_pids(&pipe_fds, cmd_count);
	if (!pids)
		return (FAILURE);
	if (execute_all_commands(cmd, shell, pipe_fds, pids) == FAILURE)
		return (FAILURE);
	close_all_pipes(pipe_fds, cmd_count - 1);
	g_exit_status = wait_for_children(pids, cmd_count);
	cleanup_resources(pipe_fds, pids, cmd_count);
	return (SUCCESS);
}
