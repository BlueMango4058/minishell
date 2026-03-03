/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_part.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:03:04 by dsagong           #+#    #+#             */
/*   Updated: 2026/03/03 15:42:01 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_token_type	decide_op_type(char *input)
{
	if (*input == '|')
		return (T_PIPE);
	if (*input == '<')
	{
		input++;
		if (*input && *input == '<')
			return (T_HEREDOC);
		else
			return (T_REDIR_IN);
	}
	if (*input == '>')
	{
		input++;
		if (*input && *input == '>')
			return (T_APPEND);
		else
			return (T_REDIR_OUT);
	}
	return (T_ERROR);
}

static int	get_op_length(t_token_type type)
{
	if (type == T_PIPE || type == T_REDIR_IN || type == T_REDIR_OUT)
		return (1);
	else if (type == T_HEREDOC || type == T_APPEND)
		return (2);
	else
		return (0);
}

/**
 * [Operator Identification]
 * 파이프(|) 및 리다이렉션(<, >, <<, >>) 기호를 식별하고 타입을 부여
 * - 연속된 동일 기호(<<, >>)를 감지하여 단일 리다이렉션과 구분된 타입을 할당
 * - 결정된 타입에 따라 토큰의 길이(1 또는 2)를 반환하여 메인 루프의 인덱스를 갱신
 */
int	handle_operator(t_token **token_lst, char *input)
{
	int				len;
	char			*value;
	t_token_type	type;

	type = decide_op_type(input);
	len = get_op_length(type);
	if (len == 0)
		return (-1);
	value = ft_my_strndup(input, len);
	if (!value)
		return (-1);
	if (add_new_token(token_lst, value, type))
		return (len);
	return (-1);
}
