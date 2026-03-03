/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:16:57 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/15 16:19:03 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERDOC_H
# define HERDOC_H
# include "types.h"

typedef struct s_delim_info
{
	char	*cooked_delim;
	int		quoted_flag;
}	t_delim_info;

t_delim_info	make_delim(char *raw);
int				heredoc_process(t_prompt *prompt);

#endif
