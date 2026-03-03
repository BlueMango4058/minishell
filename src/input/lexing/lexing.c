/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:48:39 by dsagong           #+#    #+#             */
/*   Updated: 2026/03/03 15:41:37 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "utils.h"

static int	partiotion_token(t_token **token_lst, char *input)
{
	if (is_operator(*input))
		return (handle_operator(token_lst, input));
	else
		return (handle_word(token_lst, input));
}

static int	lexing_loop(t_token **token_lst, char *input)
{
	int	len;

	while (*input)
	{
		if (is_space(*input))
		{
			input++;
			continue ;
		}
		len = partiotion_token(token_lst, input);
		if (len == -1)
			return (0);
		input += len;
	}
	return (1);
}

static int	add_endnode(t_token **token_lst)
{
	char			*end_node_value;

	end_node_value = ft_strdup("newline");
	if (!end_node_value)
		return (0);
	return (add_new_token(token_lst, end_node_value, T_END));
}

/**
 * [Lexical Analysis: Tokenization]
 * 사용자 입력 문자열을 연산자(|, <, >, <<, >>)와 일반 단어(Word) 단위로 분리하여 
 * 연결 리스트(t_token)를 생성
 * - 공백(Whitespace)을 기준으로 토큰의 경계를 인식
 * - add_end_node 옵션이 활성화된 경우, 리스트의 끝에 T_END(newline) 노드를 추가하여 
 * 이후 문법 검증 단계에서 EOF 처리
 */
t_token	*input_lexing(char *input, int add_end_node)
{
	t_token	*token_lst;

	token_lst = NULL;
	if (!input || !*input)
		return (NULL);
	if (lexing_loop(&token_lst, input) == 0)
	{
		clear_token_list(&token_lst);
		return (NULL);
	}
	if (add_end_node)
	{
		if (add_endnode(&token_lst) == 0)
		{
			clear_token_list(&token_lst);
			return (NULL);
		}
	}
	return (token_lst);
}
