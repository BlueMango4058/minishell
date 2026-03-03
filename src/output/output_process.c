/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:34:42 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 18:07:50 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "parser.h"

int	output_process(t_shell *shell, t_prompt *prompt)
{
	t_cmd	*cmd;

	cmd = parse_tokens(prompt);
	if (!cmd)
		return (FAILURE);
	if (execute_pipeline(cmd, shell) == FAILURE)
	{
		free_commands(cmd);
		return (FAILURE);
	}
	free_commands(cmd);
	return (g_exit_status);
}
