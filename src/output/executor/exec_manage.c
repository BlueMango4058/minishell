/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:00:08 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/19 10:45:00 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <unistd.h>

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

int	wait_for_children(pid_t *pids, int count)
{
	int	status;
	int	exit_status;
	int	i;

	exit_status = 0;
	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
		{
			if (waitpid(pids[i], &status, 0) == -1)
			{
				perror("waitpid");
				i++;
				continue ;
			}
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	print_signal(exit_status);
	return (exit_status);
}

void	setup_child_process(t_cmd *cmd, int *pipe_fds, \
		int cmd_index, int cmd_count)
{
	if (!(cmd->hd && cmd->hd != -1) && cmd_index > 0)
	{
		if (dup2(pipe_fds[(cmd_index - 1) * 2 + READ_END], STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			exit(1);
		}
	}
	if (cmd_index < cmd_count - 1)
	{
		if (dup2(pipe_fds[cmd_index * 2 + WRITE_END], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(1);
		}
	}
	close_all_pipes(pipe_fds, cmd_count - 1);
}

void	setup_parent_process(int *pipe_fds, int cmd_index, int cmd_count)
{
	if (!pipe_fds)
		return ;
	if (cmd_index > 0 && pipe_fds[(cmd_index - 1) * 2 + READ_END] >= 0)
	{
		close(pipe_fds[(cmd_index - 1) * 2 + READ_END]);
		pipe_fds[(cmd_index - 1) * 2 + READ_END] = -1;
	}
	if (cmd_index < cmd_count - 1 && pipe_fds[cmd_index * 2 + WRITE_END] >= 0)
	{
		close(pipe_fds[cmd_index * 2 + WRITE_END]);
		pipe_fds[cmd_index * 2 + WRITE_END] = -1;
	}
}

void	close_all_pipes(int *pipe_fds, int pipe_count)
{
	int	i;

	if (!pipe_fds || pipe_count <= 0)
		return ;
	i = 0;
	while (i < pipe_count * 2)
	{
		if (pipe_fds[i] >= 0)
		{
			close(pipe_fds[i]);
			pipe_fds[i] = -1;
		}
		i++;
	}
}
