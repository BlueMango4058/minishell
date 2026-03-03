/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:01:35 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/16 20:17:18 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_filename	*create_filename(void)
{
	t_filename	*new;

	new = malloc(sizeof(t_filename));
	if (!new)
		return (NULL);
	new->filename = NULL;
	new->flag = 0;
	new->append_mode = -1;
	new->hd = -1;
	return (new);
}

static t_file	*create_file_node(t_filename *new_filename, t_token_type redir)
{
	t_file	*new_node;

	new_node = malloc(sizeof(t_file));
	if (!new_node)
		return (NULL);
	if (redir == T_REDIR_IN || redir == T_HEREDOC)
	{
		new_node->input_file = new_filename;
		new_node->output_file = NULL;
	}
	if (redir == T_REDIR_OUT || redir == T_APPEND)
	{
		new_node->input_file = NULL;
		new_node->output_file = new_filename;
	}
	new_node->next = NULL;
	return (new_node);
}

static void	add_file_to_list(t_file **head, t_filename *new_filename, \
		t_token_type redir)
{
	t_file	*new_node;
	t_file	*current;

	if (!head || !new_filename)
		return ;
	new_node = create_file_node(new_filename, redir);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		(*head) = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	set_input_file(t_cmd *cmd, t_token *current, \
	t_prompt *prompt, t_token_type	redir_type)
{
	t_filename	*new_file;
	t_hd		*hd_list;

	hd_list = prompt->hd_lst;
	if (!cmd || !current || !current->value)
		return ;
	new_file = create_filename();
	if (hd_list && hd_list->fd > 0 && redir_type == T_HEREDOC)
	{
		new_file->hd = hd_list->fd;
		prompt->hd_lst = prompt->hd_lst->next;
		free(hd_list);
	}
	else
		new_file->hd = -1;
	new_file->filename = ft_strdup(current->value);
	if (!new_file)
	{
		free(new_file);
		return ;
	}
	if (current->type == T_WRONG_FILNAME)
		new_file->flag = 1;
	new_file->append_mode = -1;
	add_file_to_list(&(cmd->file), new_file, redir_type);
}

void	set_output_file(t_cmd *cmd, t_token *current, \
	int append, t_token_type redir)
{
	t_filename	*new_file;

	if (!cmd || !current || !current->value)
		return ;
	new_file = create_filename();
	if (!new_file)
		return ;
	new_file->filename = ft_strdup(current->value);
	if (!new_file->filename)
	{
		free(new_file);
		return ;
	}
	if (current->type == T_WRONG_FILNAME)
		new_file->flag = 1;
	new_file->append_mode = append;
	new_file->hd = -1;
	add_file_to_list(&(cmd->file), new_file, redir);
}
