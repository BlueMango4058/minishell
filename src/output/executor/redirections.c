/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:00:39 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/19 10:45:39 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	dup_input_fd(int fd, const char *msg)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		if (msg)
			perror(msg);
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

static int	handle_single_input(t_filename *input_file)
{
	int	fd_in;

	if (input_file->hd && input_file->hd != -1)
		return (dup_input_fd(input_file->hd, "dup2 heredoc"));
	else if (input_file->filename)
	{
		if (ft_strlen(input_file->filename) == 0)
		{
			print_error(input_file->filename, "No such file or directory");
			return (FAILURE);
		}
		if (input_file->flag == 1)
			return (print_error(input_file->filename, "ambiguous redirect"), \
				FAILURE);
		fd_in = open_input_file(input_file->filename);
		if (fd_in == -1)
			return (FAILURE);
		return (dup_input_fd(fd_in, NULL));
	}
	return (SUCCESS);
}

int	input_file_process(t_file *file)
{
	t_filename	*input_file;

	if (!file || !file->input_file)
		return (FAILURE);
	input_file = file->input_file;
	if (!input_file->filename)
		return (FAILURE);
	return (handle_single_input(file->input_file));
}

static int	output_file_process(t_file *file)
{
	int			fd_out;
	t_filename	*output_file;

	if (!file || !file->output_file)
		return (FAILURE);
	output_file = file->output_file;
	if (!output_file->filename)
		return (FAILURE);
	if (output_file->flag == 1)
		return (print_error(output_file->filename, "ambiguous redirect"), \
				FAILURE);
	fd_out = open_output_file(output_file->filename, output_file->append_mode);
	if (fd_out == -1)
		return (FAILURE);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close(fd_out);
		return (FAILURE);
	}
	close(fd_out);
	return (SUCCESS);
}

int	setup_redirections(t_cmd *cmd)
{
	t_file	*current;

	if (!cmd)
		return (FAILURE);
	if (!cmd->file)
		return (SUCCESS);
	current = cmd->file;
	while (current)
	{
		if (current->input_file && current->input_file->filename)
		{
			if (input_file_process(current) == FAILURE)
				return (FAILURE);
		}
		if (current->output_file && current->output_file->filename)
		{
			if (output_file_process(current) == FAILURE)
				return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}
