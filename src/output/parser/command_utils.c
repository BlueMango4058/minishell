/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:49:06 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/16 20:28:13 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*create_command(t_hd *hd_lst)
{
	t_cmd	*cmd;
	t_hd	*last;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->file = NULL;
	cmd->next = NULL;
	last = hd_lst;
	if (last)
	{
		while (last->next)
			last = last->next;
		cmd->hd = last->fd;
	}
	else
		cmd->hd = -1;
	return (cmd);
}

static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

static void	free_file_list(t_file *file_head)
{
	t_file	*current;
	t_file	*next;

	current = file_head;
	while (current)
	{
		next = current->next;
		if (current->input_file)
		{
			if (current->input_file->filename)
				free(current->input_file->filename);
			free(current->input_file);
		}
		if (current->output_file)
		{
			if (current->output_file->filename)
				free(current->output_file->filename);
			free(current->output_file);
		}
		free(current);
		current = next;
	}
}

void	free_commands(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	while (current)
	{
		next = current->next;
		free_args(current->args);
		if (current->file)
			free_file_list(current->file);
		free(current);
		current = next;
	}
}
