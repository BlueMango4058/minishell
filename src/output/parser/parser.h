/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:55:26 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 14:26:23 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include "libft.h"
# include "utils.h"
# include "stdio.h"
# include "global.h"

t_cmd		*create_command(t_hd *hd_lst);
void		add_argument(t_cmd *cmd, char *arg);
int			is_redirect_token(t_token_type type);
t_cmd		*parse_tokens(t_prompt *prompt);
t_cmd		*parse_pipeline(t_token **current, t_prompt *prompt);
t_cmd		*parse_simple_command(t_token **current, t_prompt *prompt);
int			parse_redirections(t_token **current, t_cmd *cmd, t_prompt *prompt);
void		set_input_file(t_cmd *cmd, t_token *current, \
							t_prompt *prompt, t_token_type redir_type);
void		set_output_file(t_cmd *cmd, t_token *current, int append, \
							t_token_type redir);
void		free_commands(t_cmd *cmd);
t_filename	*create_filename(void);

#endif
