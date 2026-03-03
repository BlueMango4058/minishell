/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:48:35 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/19 10:45:47 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <sys/wait.h>

static int	validate_redirections(t_cmd *cmd)
{
	t_file	*current;

	if (!cmd || !cmd->file)
		return (SUCCESS);
	current = cmd->file;
	while (current)
	{
		if (current->input_file && current->input_file->filename
			&& ft_strlen(current->input_file->filename) > 0)
		{
			if (current->input_file->flag == 1)
				return (print_error(current->input_file->filename, \
						"ambiguous redirect"), FAILURE);
			if (current->input_file->hd == -1)
				if (test_input_file(current->input_file->filename) == FAILURE)
					return (FAILURE);
		}
		if (current->output_file && current->output_file->filename
			&& ft_strlen(current->output_file->filename) > 0)
			if (current->output_file->flag == 1)
				return (print_error(current->output_file->filename, \
						"ambiguous redirect"), FAILURE);
		current = current->next;
	}
	return (SUCCESS);
}

static int	has_redirections(t_cmd *cmd)
{
	t_file	*current;

	if (!cmd || !cmd->file)
		return (FAILURE);
	current = cmd->file;
	while (current)
	{
		if (current->input_file
			&& current->input_file->filename
			&& ft_strcmp(current->input_file->filename, "NULL") != 0)
			return (SUCCESS);
		if (current->output_file
			&& current->output_file->filename
			&& ft_strcmp(current->output_file->filename, "NULL") != 0)
			return (SUCCESS);
		current = current->next;
	}
	return (FAILURE);
}

static void	restore_stdio(int *saved_stdin, int *saved_stdout)
{
	if (*saved_stdout != -1)
	{
		dup2(*saved_stdout, STDOUT_FILENO);
		close(*saved_stdout);
	}
	if (*saved_stdin != -1)
	{
		dup2(*saved_stdin, STDIN_FILENO);
		close(*saved_stdin);
	}
}

static int	apply_redirections(t_cmd *cmd, int *saved_stdin \
								, int *saved_stdout)
{
	*saved_stdin = -1;
	*saved_stdout = -1;
	if (validate_redirections(cmd) == FAILURE)
		return (FAILURE);
	if (has_redirections(cmd) == SUCCESS)
	{
		*saved_stdin = dup(STDIN_FILENO);
		*saved_stdout = dup(STDOUT_FILENO);
		if (*saved_stdin == -1 || *saved_stdout == -1)
		{
			if (*saved_stdin != -1)
				close(*saved_stdin);
			if (*saved_stdout != -1)
				close(*saved_stdout);
			return (FAILURE);
		}
		if (setup_redirections(cmd) == FAILURE)
		{
			restore_stdio(saved_stdin, saved_stdout);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	single_cmd(t_cmd *commands, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = -1;
	saved_stdout = -1;
	if (!commands->args || !commands->args[0])
	{
		if (apply_redirections(commands, &saved_stdin, &saved_stdout)
			== FAILURE)
			return (g_exit_status = 1, g_exit_status);
		g_exit_status = 0;
		restore_stdio(&saved_stdin, &saved_stdout);
		return (g_exit_status);
	}
	if (isbc(commands->args[0]))
	{
		if (apply_redirections(commands, &saved_stdin, &saved_stdout)
			== FAILURE)
			return (g_exit_status = 1, g_exit_status);
		g_exit_status = execute_builtin(commands, shell);
		restore_stdio(&saved_stdin, &saved_stdout);
		return (g_exit_status);
	}
	return (FAILURE);
}
