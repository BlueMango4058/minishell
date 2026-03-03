/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:58:34 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 13:10:34 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*command;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (FAILURE);
	command = cmd->args[0];
	if (ft_strcmp(command, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(command, "cd") == 0)
		return (ft_cd(cmd, shell));
	if (ft_strcmp(command, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(command, "export") == 0)
		return (ft_export(cmd, shell));
	if (ft_strcmp(command, "unset") == 0)
		return (ft_unset(cmd, shell));
	if (ft_strcmp(command, "env") == 0)
		return (ft_env(cmd, shell));
	if (ft_strcmp(command, "exit") == 0)
		return (ft_exit(cmd, shell));
	return (FAILURE);
}

static void	child_execve(char *path, t_cmd *cmd, t_shell *shell)
{
	if (execve(path, cmd->args, shell->env_array) == -1)
	{
		print_error(cmd->args[0], strerror(errno));
		free(path);
		exit(126);
	}
}

int	execute_external(t_cmd *cmd, t_shell *shell)
{
	char	*executable_path;
	int		child_pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (127);
	executable_path = find_executable(cmd->args[0], shell);
	if (!executable_path)
		return (g_exit_status);
	child_pid = fork();
	if (child_pid == -1)
		return (perror("fork"), free(executable_path), 1);
	if (child_pid == 0)
		child_execve(executable_path, cmd, shell);
	else
	{
		free(executable_path);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (0);
}
