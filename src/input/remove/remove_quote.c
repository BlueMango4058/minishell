/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:02:32 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/15 16:20:51 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "list.h"
#include "lexing.h"
#include <stdio.h>
#include "state.h"

static char	*remove_quotes_from_str(const char *s)
{
	char			*result;
	size_t			i;
	t_quote_state	state;
	t_quote_state	next_state;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	state = STATE_GENERAL;
	i = 0;
	while (s[i])
	{
		next_state = state_machine(s[i], state);
		if (state == next_state)
			result = charjoin_and_free(result, s[i]);
		state = next_state;
		i++;
	}
	return (result);
}

int	remove_quotes_from_tokens(t_token *token_lst)
{
	t_token	*curr;
	char	*new_value;

	curr = token_lst;
	while (curr && curr->type != T_END)
	{
		new_value = remove_quotes_from_str(curr->value);
		if (!new_value)
			return (0);
		if (new_value)
		{
			free(curr->value);
			curr->value = new_value;
		}
		curr = curr->next;
	}
	return (1);
}

//남은 word 토큰들 quote 전부 다 때기
int	remove_quote(t_token **token_lst)
{
	if (!remove_quotes_from_tokens(*token_lst))
	{
		perror("malloc fail : remove_quotes_form_tokens");
		return (0);
	}
	return (1);
}
