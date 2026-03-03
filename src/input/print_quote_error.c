/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_quote_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:10:10 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/15 16:15:40 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"

void	print_quote_error(t_quote_state state)
{
	char	missing_quote;

	missing_quote = 0;
	if (state == STATE_GENERAL)
		return ;
	else
	{
		if (state == STATE_IN_DQUOTE)
			missing_quote = '"';
		else if (state == STATE_IN_SQUOTE)
			missing_quote = '\'';
		ft_putstr_fd("minishell: syntax error: unexpected EOF", 2);
		ft_putstr_fd("while looking for matching '", 2);
		ft_putchar_fd(missing_quote, 2);
		ft_putendl_fd("'", 2);
	}
}
