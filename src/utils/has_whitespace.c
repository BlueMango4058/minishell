/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_whitespace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:12:08 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/17 14:25:28 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_quote_state	state_machine(char c, t_quote_state state);

int	has_whitespace(const char *s)
{
	t_quote_state	state;
	size_t			i;

	if (!s)
		return (0);
	state = STATE_GENERAL;
	i = 0;
	while (s[i])
	{
		if (state == STATE_GENERAL && is_space((unsigned char)s[i]))
			return (1);
		if (s[i] == '\'' || s[i] == '"')
			state = state_machine(s[i], state);
		i++;
	}
	return (0);
}
